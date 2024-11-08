#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OTA/OTA.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <IR/IR.h>
#include <Coin/Coin.h>
#include <CoinReading/CoinTask.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// COIN PIN
#define COIN_PIN 19

Coin coin(COIN_PIN);

// WIFI CONF
#define SSID "cuybot"
const char* password = "cuybot123";

// put function declarations here:
int myFunction(int, int);
OTA ota("cuybot");

CoinTask coinTask(coin);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Setting up WiFi");

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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sanitasi");
    lcd.setCursor(0, 1);
    lcd.print("Berhasil");

    coinTask.startTask();
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}