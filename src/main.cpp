#include <Arduino.h>
#include <OTA/OTA.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <Display/DisplayTask.h>
#include <Token/TokenTask.h>
#include <Coin/CoinAcceptorTask.h>

// WIFI CONF
#define SSID "cuybot"
const char* password = "cuybot123";

OTA ota("cuybot");

TokenTask tokenTask(10, 25, 26); // Countdown awal, relay mist maker di pin 25, relay UV di pin 26
DisplayTask displayTask(tokenTask);
CoinAcceptorTask coinAcceptor(tokenTask);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  displayTask.initDisplay();

  String macAddr = WiFi.macAddress();
  String lastFourCharMacAddr = macAddr.substring(macAddr.length() - 4);
  String ssid = String(SSID) + "-" + lastFourCharMacAddr;

  if (WiFi.softAP(ssid, password, 6)) {
        Serial.println("Wi-Fi AP started successfully");
        Serial.print("AP IP address: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.println("Failed to start Wi-Fi AP");
    }

    if (!MDNS.begin("cuybot")) {
        Serial.println("DNS Cannot be started!");
    }

    Serial.println("Setting up OTA service...");
    ota.begin();
    ota.startOTATask();

    tokenTask.startTask(); // Memulai task countdown di TokenTask
    displayTask.startDisplayTask(); // Memulai task tampilan
    coinAcceptor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}