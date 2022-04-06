#include "config.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

// Following along with this guide: https://tttapa.github.io/ESP8266/Chap07%20-%20Wi-Fi%20Connections.html

const char *printvar = "THIS BETTER WORK >:(";

const char *wifiName = WIFI_NAME;
const char *wifiPass = WIFI_PASS;
const char *otaName = OTA_NAME;
const char *otaPass = OTA_PASS;

void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  WiFi.begin(wifiName, wifiPass);
  Serial.print("Connecting to ");
  Serial.print(wifiName);
  Serial.println("....");

  int i = 1;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(i);
    Serial.print(" ");
    i++;
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  ArduinoOTA.setHostname(otaName);
  ArduinoOTA.setPassword(otaPass);

  ArduinoOTA.onStart([]()
                     { Serial.println("Start"); });
  ArduinoOTA.onEnd([]()
                   { Serial.println("\nEnd"); });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });

  ArduinoOTA.onError([](ota_error_t error)
                     {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

  ArduinoOTA.begin();
  Serial.println("OTA ready");

  // this NEEDS to be at the end of the setup for some reason, after OTA setup.
  if (!MDNS.begin("esp8266"))
  { // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
}

unsigned long prevMillis = millis();

void loop()
{
  unsigned long curMillis = millis();

  MDNS.update();
  ArduinoOTA.handle();

  if (curMillis - prevMillis > 2000)
  {
    Serial.println(printvar);
    prevMillis = curMillis;
  }
}
