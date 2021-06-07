#include <SPI.h>                          
#include <MFRC522.h>                      
#include <Servo.h>                        
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int RST_PIN = 9;                          
const int SS_PIN = 10;                          
const int role = 8;                         
int kled = 6;
int yled = 5;

Servo motor;                              
MFRC522 rfid(SS_PIN, RST_PIN);            
byte ID[4] = {42 ,103 ,14 ,16};          

void setup() { 
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);                     
  SPI.begin();                            
  rfid.PCD_Init();                        
  pinMode(role, OUTPUT); 
  pinMode(kled, OUTPUT);
  pinMode(yled, OUTPUT);
}

void loop() {
  lcd.home();
  
  if ( ! rfid.PICC_IsNewCardPresent())    
    return;

  if ( ! rfid.PICC_ReadCardSerial())      
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] && 
    rfid.uid.uidByte[4] == ID[4]) {
        Serial.println("Kapi acildi");
        ekranaYazdir();
        digitalWrite(role,HIGH); 
        delay(1000);
        digitalWrite(role,LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Yetkili Kart"); 
        renkAyarla(255, 0); 
        delay(500);
        lcd.clear();
    }
    else{                                 
      Serial.println("Yetkisiz Kart");
      ekranaYazdir();
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Yetkisiz Kart"); 
       renkAyarla(0, 255); 
       delay(500);
       lcd.clear();
    }
  rfid.PICC_HaltA();
}

void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}
void renkAyarla(int kirmizi, int yesil){ 
  kirmizi = 255-kirmizi; 
  yesil = 255-yesil; 
  analogWrite(kled, kirmizi); 
  analogWrite(yled, yesil); 
  } 
