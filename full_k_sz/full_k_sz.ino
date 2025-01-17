//könyvtárak importálása
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTTYPE DHT11 //Hőmérsékletszenzor típusának beállítása (DHT11)
#define DHTPIN 8 //Hőmérsékletszenzor bemeneti PIN-je.
  int water; //Vízszenzor jelének tárolása
  LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //LCD képernyő konfigurálása
  DHT dht(DHTPIN, DHTTYPE); //DHT konfigurálása
  //dht DHT;
  char strt [4]; //Hőmérséklet naplózása
  char strh [4]; //Páratartalom naplózása
//----------------------------------  
void setup(){
  pinMode(13,OUTPUT); //Digitális kimenet a motorhoz
  pinMode(7,INPUT); //Digitális bemenet a vízszenzortól
  
  lcd.begin(16,2); //LCD képernyő méretének konfigurálása (16 oszlop, 2 sor)  
  lcd.backlight(); //LCD képernyő világításának bekapcsolása

//Naplózás fejléc
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Time,Homerseklet,Paratartalom,Viz");
}
//----------------------------------
void loop() {
  
  float t = dht.readTemperature(); //Hőmérséklet aktuális értéke
  float h = dht.readHumidity(); //Relatív páratartalom aktuális értéke
  dtostrf(t, 4, 2, strt); //Float -> String konvertálás
  dtostrf(h, 4, 2, strh); //Float -> String konvertálás
  
//Naplózás excelbe  
  Serial.println( (String) "DATA,DATE,TIME," + t + "," + h + "," + String(water)); 
  
//Aktuális szenzorértékek kiírása a kijelzőre  
 //Hőmérséklet
  lcd.setCursor(0,0); 
  lcd.print("Homersek:");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
 //Relatív páratartalom
  lcd.setCursor(0,1);
  lcd.print("Paratart:");
  lcd.print(h);
  lcd.print("%");
  
//Soros monitor beállításai 
  Serial.begin(9600); //Soros monitor címe
  Serial.print("Homerseklet = ");
  Serial.print(t,h);
  Serial.print("°C | ");
 //Serial.print((t*9.0)/5.0+32.0);
 //Serial.println("°F ");
  Serial.print("Paratartalom = ");
  Serial.print(h);
  Serial.println("% ");
  Serial.println("");

//Vízszenzor tesztelés
   water = digitalRead(7);
  if(water == LOW) //Rövidzár (szenor a vízben van)
  {
  digitalWrite(13,LOW); //Szivattyú kikapcsolása
  }
  else
  {
  digitalWrite(13,HIGH);//Szakadás (szenzor nincs a vízben)
  }
  delay(100); //2 másodperc késleltetés a következő ciklus előtt
}
