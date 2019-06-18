/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read new NUID from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>

#include <MFRC522_v2.h>

#define SS_PIN 10
#define RST_PIN 9
 

MIFARE_Key key; 

// Init array that will store new NUID 
Uid nuid;
unsigned char nuidPICC[4];

void setup() { 
  
  MFRC522(SS_PIN, RST_PIN); // Initialization of pins
    
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  PCD_Init(); // Init MFRC522 
  
  for (char i = 0; i < 6; i++) {
    key.keybyte[i] = 255;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  for (char i = 0; i < 6; i++) {
      Serial.print(key.keybyte[i],HEX);
      Serial.print("\t");
      }
}
 
void loop() {

  // Look for new cards
  if ( ! PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! PICC_ReadCardSerial(nuid))
    return;

  //Serial.print(F("PICC type: "));
  //PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  //if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
  //  piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
  //  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
  //  Serial.println(F("Your tag is not of type MIFARE Classic."));
  //  return;
  //}

//if (nuid.uidbyte[0] != nuidPICC[0] || 
//    nuid.uidbyte[1] != nuidPICC[1] || 
//    nuid.uidbyte[2] != nuidPICC[2] || 
//    nuid.uidbyte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = nuid.uidbyte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    //printHex(rfid.uid.uidByte, rfid.uid.size);
    for (char i = 0; i < 4; i++) {
      Serial.print(nuidPICC[i],HEX);
      Serial.print("\t");
      }
    printHex(nuid.uidbyte,4);
	  Serial.println();
    Serial.print(F("In dec: "));
    //printDec(rfid.uid.uidByte, rfid.uid.size);
    for (char i = 0; i < 4; i++) {
      Serial.print(nuidPICC[i],DEC);
      Serial.print("\t");
      }
	  Serial.println();
//  }
//  else Serial.println(F("Card read previously."));

  // Halt PICC
  PICC_HaltA();

  // Stop encryption on PCD
  //PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(char *buffer, char bufferSize) {
  for (char i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(char *buffer, char bufferSize) {
  for (char i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
