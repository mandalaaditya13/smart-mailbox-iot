#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#define SS_PIN 53
#define RST_PIN 5


#include <Servo.h>

Servo myservo; 
int trigPin = 49;
int echoPin = 48;
String data = "";
char d;
String arrData[2];
int pinButton = 8;
int pinButton1 = 9;
long waktu;
String  teststr="";
int jarak;
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#include <LiquidCrystal_PCF8574.h> //memasukan library LCD
#include <Keypad.h>
 LiquidCrystal_PCF8574 lcd(0x27); //didapat dari i2c scanner

String kartu="D3 72 96 35";
String hotp;
long otp;
#include <DFPlayer_Mini_Mp3.h> 
 int pintu = 3;
 int led =4;
int akses;
void setup() 
{
  akses=1;
  teststr="";

  Serial.begin(9600);   // Initiate a serial communication
 Serial1.begin(115200);
 Serial2.begin(9600);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
   myservo.attach(10); 
  myservo.write(80);
pinMode(pinButton, INPUT);
pinMode(pinButton1, INPUT);
  pinMode(trigPin, OUTPUT);

pinMode(echoPin, INPUT);

  randomSeed(analogRead(0));
Serial3.begin (9600);
    mp3_set_serial (Serial3); //set softwareSerial for DFPlayer
    mp3_set_volume (30); //set Volume module DFPlayer, bisa diatur hingga maksimal 25

pinMode(pintu,OUTPUT);
pinMode(led,OUTPUT);
digitalWrite(pintu,HIGH);
digitalWrite(led,LOW);
lcd.begin(16, 2); 
lcd.setBacklight(255);
lcd.setCursor(0, 0);
lcd.print("Jika ada Paket");
lcd.setCursor(0, 1);
lcd.print("Tekan merah");
mp3_play (1);
         delay(2000); 
}

void loop() 
{
    while(Serial1.available()>0){
    delay(10);
    d = Serial1.read();
    data += d;  
   // Serial.println(data);
  }
  if (data !="") {
        
   if(data == "GO")
    {
         mp3_play (2);
         delay(6000);
          akses=2;
     }
     if(data == "TUTUP")
    {
  myservo.write(80);
     }     
  if(data == "BK")
    {
 mp3_play (4); 
akses=3;
     }   
    }
  data ="";
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  waktu = pulseIn(echoPin, HIGH);
  jarak= waktu*0.034/2;
  //Serial.print("Jarak: ");
 // Serial.println(jarak);
if (akses==1){
  lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Jika ada Paket");
lcd.setCursor(0, 1);
lcd.print("Tekan merah");
  if (digitalRead(pinButton) ==HIGH){
      teststr="";
    otpp();
        lcd.clear();
       lcd.setCursor(0, 0);
     lcd.print("Meminta QR ");
     lcd.setCursor(0, 1);
     lcd.print(".......... ");
      String kirimsh ="Ada Paket,Kode  QR : " + (hotp) + "#";

    Serial.print(kirimsh);
    delay(4000); 
    akses=6;
        }
        delay(500);
}
if (akses==8){
 if (digitalRead(pinButton1) ==HIGH){
  
lcd.clear();
  myservo.write(80);
  lcd.setCursor(0, 0);
lcd.print("  Terimakasih");
lcd.setCursor(0, 1);
lcd.print("-----------------");
   Serial1.print("TUTUP");
   mp3_play (6);
  delay(3000);
 setup(); }       
        }

        if (akses==6){
          lcd.clear();
          lcd.setCursor(0, 0);
lcd.print(" Menunggu ");
lcd.setCursor(0, 1);
lcd.print("Konfirmasi.......");
        }
if (akses==2){
   
if ((jarak >= 50) && (jarak <=70)){
  Serial1.print("FOTO") ;
   lcd.clear();
       lcd.setCursor(0, 0);
     lcd.print("Mengambil foto");
       lcd.setCursor(0, 1);
     lcd.print("..............");
     mp3_play (3);
    delay(3000);
         
     akses=7;
     
}
else{
     lcd.clear();
       lcd.setCursor(0, 0);
     lcd.print("jarak > 50cm");
       lcd.setCursor(0, 1);
     lcd.print("jarak :");
        lcd.setCursor(8, 1);
     lcd.print(jarak);
     lcd.setCursor(12, 1);
     lcd.print("cm");
}
}

if (akses==3){
   lcd.clear();
       lcd.setCursor(0, 0);
     lcd.print("Silahkan Scan ");
       lcd.setCursor(0, 1);
     lcd.print("----QR------- ");
    
    if(Serial2.available()>0) // Chek for availablity of data at Serial Port
  {
  teststr = Serial2.readString();  //read until timeout
  teststr.trim();  
 //Serial.println(teststr);
  if (teststr==hotp)  {
akses=5;
  }         
  teststr="";
  }
    }

    if (akses==5){
    lcd.clear();
       lcd.setCursor(0, 0);
     lcd.print("QR valid ");
       lcd.setCursor(0, 1);
     lcd.print("Masukan paket");
      myservo.write(0);
       mp3_play (5);
         delay(4000);
      lcd.clear();
       lcd.setCursor(0, 0);
     lcd.print("  Tombol Putih");
       lcd.setCursor(0, 1);
     lcd.print("Untuk Tutup Box ");
     akses=8;
    }

  rfid();
  delay(500);
 }
