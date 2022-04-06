#include "config.h"
#include <ESP8266WiFi.h>

// Following along with this guide: https://tttapa.github.io/ESP8266/Chap07%20-%20Wi-Fi%20Connections.html

const char *wifiName = WIFI_NAME;
const char *wifiPass = WIFI_PASS;

void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  WiFi.begin(wifiName, wifiPass);
  Serial.print("Connecting to ");
  Serial.print(wifiName);
  Serial.println("....");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop()
{
}