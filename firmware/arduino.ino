#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

// ========= WiFi =========
const char* ssid = "FabLab";
const char* password = "f3a4b1lab";

// ========= Google Script =========
String scriptURL = "https://script.google.com/macros/s/AKfycbzh63_CwPGEghkfUWHGJwKfm3qFMhJw4RgawZe82Q-i2FPysVpzIu99EYD9DImJxbqNuA/exec";

// ========= RC522 =========
#define SS_PIN 5
#define RST_PIN 22

MFRC522 mfrc522(SS_PIN, RST_PIN);

// ========= LED =========
#define LED_PIN 4

// ========= Anti-duplicate =========
String lastUID = "";
unsigned long lastScanTime = 0;
const unsigned long scanDelay = 3000;

// ========= RFID auto-reset =========
unsigned long lastRFIDReset = 0;

void setup() {

  Serial.begin(115200);
  delay(1000);

  // LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");

  // SPI + RFID
  SPI.begin(18, 19, 23, 21);

  mfrc522.PCD_Init();

  Serial.println("RFID Ready");
}

void loop() {

  // ===== Auto reset RFID every 30 sec =====
  if (millis() - lastRFIDReset > 30000) {

    mfrc522.PCD_Init();

    lastRFIDReset = millis();

    Serial.println("RFID reset");
  }

  // ===== Detect card =====
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // ===== Read UID =====
  String uid = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {

    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  uid.toUpperCase();

  Serial.println("UID: " + uid);

  // ===== Anti-duplicate =====
  unsigned long currentTime = millis();

  if (uid == lastUID &&
      (currentTime - lastScanTime < scanDelay)) {

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    return;
  }

  lastUID = uid;
  lastScanTime = currentTime;

  // ===== LED ON =====
  digitalWrite(LED_PIN, HIGH);

  // ===== Send to Google =====
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = scriptURL + "?uid=" + uid;

    http.begin(url);

    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    http.setTimeout(1500);

    int httpCode = http.GET();

    if (httpCode > 0) {

      String response = http.getString();

      Serial.println("Server: " + response);

    } else {

      Serial.println("HTTP Error");
    }

    http.end();

  } else {

    Serial.println("WiFi disconnected");
  }

  // ===== Proper RFID stop =====
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  // ===== LED OFF =====
  delay(200);

  digitalWrite(LED_PIN, LOW);
}
