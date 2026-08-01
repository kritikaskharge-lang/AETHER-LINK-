// ==========================
// AETHER LINK - NODE A
// FINAL CORRECTED CODE
// ==========================

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// ================= LCD =================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= LORA =================
#define SS 5
#define RST 14
#define DIO0 26

// ================= KEYPAD =================
const byte ROWS = 4;
const byte COLS = 4;

// FINAL CORRECTED KEYPAD MAPPING
char keys[ROWS][COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};

// FINAL PIN CONFIGURATION
byte rowPins[ROWS] = {32, 33, 25, 13};
byte colPins[COLS] = {4, 15, 2, 27};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ================= VARIABLES =================
String msg;

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  // LCD START
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Aether Link");

  lcd.setCursor(0,1);
  lcd.print("Node A READY");

  delay(3000);

  // LORA START
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LoRa Failed");

    while (1);
  }

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Aether Link");
  lcd.setCursor(0,1);
  lcd.print("Press A/B/C/D");
}

// ================= LOOP =================
void loop() {

  char key = keypad.getKey();

  if (key) {

    Serial.print("Pressed: ");
    Serial.println(key);

    // ===== A =====
    if (key == 'A') {

      msg = "NEED HELP";
      sendMessage(msg);
    }

    // ===== B =====
    else if (key == 'B') {

      msg = "NEED FOOD";
      sendMessage(msg);
    }

    // ===== C =====
    else if (key == 'C') {

      msg = "MEDICAL EMERGENCY";
      sendMessage(msg);
    }

    // ===== D =====
    else if (key == 'D') {

      msg = "NEED WATER";
      sendMessage(msg);
    }

    // ===== 1 =====
    else if (key == '1') {

      msg = "FIRE ALERT";
      sendMessage(msg);
    }

    // ===== 2 =====
    else if (key == '2') {

      msg = "TRAPPED";
       sendMessage(msg);
    }

    // ===== 3 =====
    else if (key == '3') {

      msg = "SEND RESCUE";
      sendMessage(msg);
    }

    // ===== 4 =====
    else if (key == '4') {

      msg = "LOW BATTERY";
      sendMessage(msg);
    }
  }
}

// ================= SEND FUNCTION =================
void sendMessage(String outgoing) {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Sending...");

  lcd.setCursor(0,1);
  lcd.print(outgoing);

  // SEND THROUGH LORA
  LoRa.beginPacket();
  LoRa.print(outgoing);
  LoRa.endPacket();

  Serial.println("Sent: " + outgoing);

  delay(2000);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Message Sent");

  delay(1500);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press A/B/C/D");
}
