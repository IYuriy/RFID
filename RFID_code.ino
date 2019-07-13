#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define ledPin 13

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println(F("Detecting ID  Number of RFID tag"));
    Serial.println(F("Move RFID tag close to RFID module..."));
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;
    
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

 
  // LED
  Serial.print("Tap card key: ");
  Serial.println(strID);

   if (strID.indexOf("1A:11:58:89") >= 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  rfid.PICC_HaltA();
}
