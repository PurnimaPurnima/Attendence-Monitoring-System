#include <Adafruit_Fingerprint.h>

#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
SoftwareSerial mySerial(2, 3);
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int flag=0;
uint8_t id;
int choice;
int start;
int i;
void setup()  
{
  lcd.begin(16,2);
  Serial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Hi!, I am Arduino. Found fingerprint sensor!");
    lcd.print("Hi!, I am");
    lcd.setCursor(0,1);
    lcd.print("Arduino.");
    delay(1000);
    lcd.clear();
    delay(100);
    //start=millis();
    //while(i=0;i<=40;i++)
    //{
      lcd.setCursor(0,0);
      lcd.print("Found finger");
      lcd.setCursor(0,1);
      lcd.print("print sensor.");
      delay(1000);
    //}
    lcd.clear();
  } 
  else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.setCursor(0,0);
      lcd.print("Fingerprint");
      lcd.setCursor(0,1);
      lcd.print("sensor not found");
      delay(2000);
    
    lcd.clear();
    
    while (1) { delay(1); }
  }
  
 while(flag==0){
  while (Serial.available()){
  choice = Serial.read();
   choice-=48;
   flag=1;
  }}

}

uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()                     // run over and over again
{
  
  switch(choice)
  {
    case 1: //enrollment
          {
             Serial.println("Ready to enroll a fingerprint!\nPlease type in the ID # (from 1 to 127) you want to save this finger as...");
             id = readnumber();
             if (id == 0) 
             {// ID #0 not allowed, try again!
                return;
             }
             //Serial.print("Enrolling ID #");
             //Serial.println(id);
  
             while (!getFingerprintEnroll() );  
          }
          break;
    case 2: //checking
          {
            int k=getFingerprintIDez();
            if(k==-1)
          //      Serial.println("Fingerprint not found!");
            delay(50);  
          }
          break;
  }
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  //Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.setCursor(0,0);
      lcd.print("Image taken");
      delay(500);
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      break;
    default:
      //Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.setCursor(0,0);
      lcd.print("Image converted");
      delay(500);
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
    /*  Serial.println("Unknown error");
      lcd.setCursor(0,0);
      lcd.print("Unknown error");
      delay(2000);*/
      return p;
  }
  lcd.clear();
  delay(100);
  Serial.println("Remove finger");
  lcd.setCursor(0,0);
  lcd.print("Remove finger");
  delay(500);
  lcd.clear();
  delay(1000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  lcd.setCursor(0,0);
  lcd.setCursor(3,0);
  lcd.print("ID ");
  lcd.print(id);
  delay(500);
  lcd.clear();
  
  p = -1;
  Serial.println("Place same finger again");
  lcd.setCursor(0,0);
  lcd.print("Place same");
  lcd.setCursor(0,1);
  lcd.print("finger again");
  //delay(1500);
  //lcd.clear();
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      Serial.println("Image taken");
      lcd.setCursor(0,0);
      delay(2000);
      lcd.clear();
      break;
    case FINGERPRINT_NOFINGER:
      lcd.clear();
      Serial.print(".");
      lcd.setCursor(0,0);
      lcd.print(".");
      lcd.clear();
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.setCursor(0,0);
      lcd.print("Communication");
      lcd.setCursor(0,1);
      lcd.print("error!");
      delay(1000);
      lcd.clear();
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear();
      Serial.println("Imaging error");
      lcd.setCursor(0,0);
      lcd.print("Imaging error");
      delay(1000);
      lcd.clear();
      break;
    default:
      lcd.clear();
      Serial.println("Unknown error");
      lcd.setCursor(0,0);
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.setCursor(0,0);
      lcd.print("Image converted");
      delay(1000);
      lcd.clear();
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  lcd.setCursor(0,0);
      lcd.print("Creating model");
      lcd.setCursor(0,1);
      lcd.print("for #");
      lcd.print(id);
      delay(500);
      lcd.clear();
      //break;
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
    lcd.setCursor(0,0);
      lcd.print("Prints matched!");
      delay(500);
      lcd.clear();
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    //Serial.println("Fingerprints did not match");
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID value= "); Serial.println(id);
  lcd.setCursor(0,0);
      lcd.print("ID value= ");
      lcd.print(id);
      delay(750);
      lcd.clear();
  
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.setCursor(0,0);
      lcd.print("Stored!");
      delay(1000);
      lcd.clear();
  
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    //Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    //Serial.println("Error writing to flash");
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }   
}


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.setCursor(0,0);
      lcd.print("Image taken");
      delay(500);
      lcd.clear();
  
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.setCursor(0,0);
      lcd.print("Image converted");
      delay(500);
      lcd.clear();
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    lcd.setCursor(0,0);
      lcd.print("Found a print");
      lcd.setCursor(0,1);
      lcd.print("match!");
      delay(1000);
      lcd.clear();
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    //Serial.println("Did not find a match");
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  //Serial.print("Found ID value=#");
  Serial.println(finger.fingerID); 
  lcd.setCursor(0,0);
  lcd.print(finger.fingerID);
  delay(1500);
  lcd.clear();
  //Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  //Serial.print("Found ID value=#"); 
  Serial.println(finger.fingerID); 
  lcd.setCursor(0,0);
  lcd.print(finger.fingerID);
  delay(1500);
  lcd.clear();
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
