#include <SPI.h>
#include <MFRC522.h>

// Définir les broches du module RC522
#define SS_PIN 10  // Pin SS (Slave Select)
#define RST_PIN 9  // Pin RESET

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Créer un objet MFRC522

void setup() {
  Serial.begin(9600);  // Initialiser le moniteur série
  SPI.begin();         // Initialiser la communication SPI
  mfrc522.PCD_Init();  // Initialiser le module RC522
  
  // Serial.println("Approchez votre carte RFID...");
}

void loop() {
  // Vérifier si une carte est présente
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Vérifier si la carte peut être lue
    if (mfrc522.PICC_ReadCardSerial()) {
      
      // Afficher l'UID sous forme hexadécimale
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        Serial.print(" ");
      }
      
      Serial.println();  // Nouvelle ligne
      mfrc522.PICC_HaltA();  // Arrêter la lecture de la carte
      mfrc522.PCD_StopCrypto1();  // Arrêter la communication
    }
  }
}
/*
 *
UID de la carte : BC 8B A4 3D (Bleu)
UID de la carte : A 77 A4 3D (Noir)
UID de la carte : D DB A4 3D (Jaune)

 */

 // sudo apt-get install libqt5serialport5-dev
