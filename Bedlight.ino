#include "PixelWrapper.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "Preset.h"
#include "FadingStars.h"
#include "Police.h"
#include "TwoLights.h"
#include "Lesen.h"
#include "LEDMouse.h"
#include "Disco.h"
#include "Rainbow.h"
#include "SunSet.h"
#include <Arduino_JSON.h>
#include <WebServer.h>
#include "Website.h"

#define PIN 26
#define NUMPIXELS 360
#define NUMSTRIPES 6
#define ACTIVE 2

#define LED_PIN_1 19
#define BUTTON_PIN_1 21

#define LED_PIN_2 18
#define BUTTON_PIN_2 4

const char *ssid = "<ssid>";
const char *pw = "<pw>";

bool power_on = false;
unsigned int preset_idx = 0;
const String presets[]={"simple_on","police","fadingstars", "lesen", "twolights", "mouse", "disco", "rainbow", "sunset"};
#define NUM_PRESETS 9

WebServer server(80);
PixelWrapper strip = PixelWrapper(NUMPIXELS, PIN, NUMSTRIPES, ACTIVE);
Preset *activePreset = NULL;

void setLEDs(JSONVar leds)
{

  for (int i = 0; i < NUMPIXELS; i++)
  {
    strip.setPixelColor(i,(int)leds[i][0], (int)leds[i][1], (int)leds[i][2]);
  }
  strip.show();
}

void returnOk()
{
  server.send(200, "text/plain", "");
}

void handleRoot()
{
  server.send(200, "text/html", LANDINGPAGE);
}

void returnFail(String msg)
{
  server.send(400, "text/plain", msg + "\r\n");
}

void handleNotFound()
{
  server.send(404, "text/plain", "Invalid URL");
}

void handleSetPreset()
{
  String preset = server.arg("preset");
  
  setPreset(preset);
}

void setPreset(String preset){
  strip.clear();
  strip.show();
  delete activePreset;
  if (preset == "simple_on"){
    strip.fill(255,255,255);
    strip.show();
    return;
  }
  if (preset == "police")
  {
    activePreset = new Police(&strip);
    returnOk();
    return;
  }
  if (preset == "fadingstars")
  {
    activePreset = new FadingStars(&strip);
    returnOk();
    return;
  }
  if (preset == "lesen")
  {
    activePreset = new Lesen(&strip);
    returnOk();
    return;
  }
  if (preset == "twolights")
  {
    activePreset = new TwoLights(&strip);
    returnOk();
    return;
  }
  if (preset == "mouse")
  {
    activePreset = new LEDMouse(&strip);
    returnOk();
    return;
  }
  if (preset == "disco")
  {
    activePreset = new Disco(&strip);
    returnOk();
    return;
  }
  if (preset == "rainbow")
  {
    activePreset = new Rainbow(&strip);
    returnOk();
    return;
  }
  if (preset == "sunset")
  {
    activePreset = new SunSet(&strip);
    returnOk();
    return;
  }
  returnFail("Unknown Preset");
}

void handleSetAllLEDs()
{
  activePreset = NULL;
  String jsonReq = server.arg("color");
  JSONVar color = JSON.parse(jsonReq);
  Serial.println(jsonReq);
  Serial.println(color);
  if (JSON.typeof(color) != "array")
  {
    Serial.println("Parsing input failed!");
    returnFail("Invalid Request Body");
    return;
  }
  strip.fill((int)color[0], (int)color[1], (int)color[2]);
  strip.show();
  returnOk();
}

void handleSetLEDs()
{
  activePreset = NULL;
  Serial.println("Setting LEDs!");
  String jsonReq = server.arg("plain");
  Serial.println(jsonReq);
  JSONVar leds = JSON.parse(jsonReq);
  if (JSON.typeof(leds) != "array")
  {
    Serial.println("Parsing input failed!");
    returnFail("Invalid Request Body");
    return;
  }

  if (leds.length() != NUMPIXELS)
  {
    Serial.println("Wrong number of LEDs");
    returnFail("Wrong number of leds requested");
    return;
  }
  setLEDs(leds);
  returnOk();
}

void setup()
{
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); 
  Serial.begin(115200);
  Serial.println("Started.");
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pw);
  int waits = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    waits++;
    if (waits > 5)
    {
      Serial.println("Restarting to fix WiFi");
      delay(200);
      ESP.restart();
    }
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/setleds", handleSetLEDs);
  server.on("/setallleds", handleSetAllLEDs);
  server.on("/setpreset", handleSetPreset);
  server.onNotFound(handleNotFound);

  server.begin();

  strip.begin();
  strip.fill(0,0,0);
  digitalWrite(LED_PIN_1,LOW);
  digitalWrite(LED_PIN_2,LOW);
  Serial.println("Setup complete");
}

void button1Pressed(){
  power_on = !power_on;
  digitalWrite(LED_PIN_1,power_on);
  digitalWrite(LED_PIN_2,power_on);
  if (power_on){
    preset_idx = 0;
    setPreset(presets[0]);  
  } else {
    strip.clear();
  strip.show();
  delete activePreset;
    strip.fill(0,0,0);
    strip.show();
  }
 
}

void button2Pressed(){
  if (!power_on){
    button1Pressed();
  }
  else{
    preset_idx = (preset_idx+1)%NUM_PRESETS;
    setPreset(presets[preset_idx]);
  }
}



int last_button1 = HIGH;
int last_button2 = HIGH;
unsigned long last_activation_1= millis();  // the last time the output pin was toggled
unsigned long last_activation_2= millis();  // the last time the output pin was toggled
unsigned long reactivation_ms = 100;    // the debounce time; increase if the output flickers
 
void handleButtons(){
  int button1 = digitalRead(BUTTON_PIN_1);
  int button2 = digitalRead(BUTTON_PIN_2);
  if (button1 == LOW && last_button1 == HIGH && (millis() - last_activation_1)>reactivation_ms){
    last_activation_1 = millis();
    button1Pressed();
  }
  last_button1 = button1;
  if (button2 == LOW && last_button2 == HIGH && (millis() - last_activation_2)>reactivation_ms){
    last_activation_2 = millis();
    button2Pressed();
  }
  last_button2 = button2;
}

void loop()
{
  handleButtons();
  server.handleClient();
  delay(2);
  if (activePreset)
  {
    activePreset->tick();
  }
}
