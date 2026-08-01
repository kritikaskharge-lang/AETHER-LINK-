#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- LoRa Pins ----------------
#define SS    5
#define RST   14
#define DIO0  26

// ---------------- Buzzer & LED ----------------
#define BUZZER 27
#define LED    25

String receivedMessage = "";

void setup() {

  Serial.begin(115200);

  // LED & Buzzer Setup
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);

  // LCD Start
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("AetherLink B");

  lcd.setCursor(0,1);
  lcd.print("Waiting Msg");

  delay(3000);
  lcd.clear();

  // LoRa Setup
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {

    lcd.setCursor(0,0);
    lcd.print("LoRa Failed");

    while (1);
  }

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("AetherLink B");

  lcd.setCursor(0,1);
  lcd.print("Waiting Msg");
}

void loop() {

  // -------- Check for Message --------
  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    receivedMessage = "";

    // Read incoming message
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    Serial.println(receivedMessage);

    // -------- MESSAGE RECEIVED --------
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("MESSAGE");

    lcd.setCursor(0,1);
    lcd.print("RECEIVED");

    delay(2000);

    // -------- DISPLAY RECEIVED MESSAGE --------
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("MSG:");

    lcd.setCursor(0,1);
    lcd.print(receivedMessage);

    // -------- ALERT 2 TIMES --------
    for(int i = 0; i < 2; i++) {

      // LED ON
      digitalWrite(LED, HIGH);

      unsigned long startTime = millis();

      // Buzzer Beep for 6 seconds
      while (millis() - startTime < 6000) {

        digitalWrite(BUZZER, HIGH);
        delay(300);

        digitalWrite(BUZZER, LOW);
        delay(300);
      }

      // LED OFF
      digitalWrite(LED, LOW);

      delay(1000);
    }

    // -------- RETURN TO HOME SCREEN --------
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("AetherLink B");

    lcd.setCursor(0,1);
    lcd.print("Waiting Msg");
  }
}