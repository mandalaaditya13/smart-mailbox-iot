  void mulai(){
               SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
 rfid();
    }
  void otpp(){
     otp = random(10000,99999);
    hotp=String(otp);
  
   
    }