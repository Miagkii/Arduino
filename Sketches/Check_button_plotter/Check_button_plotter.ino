#include <EEPROM.h>
const byte Setbutton = 2;
unsigned long startMillis, endMillis, exitMillis;
bool setClick = false;
bool setPush = false;
bool startKey = false;
bool endKey = false;
bool pushKey = false;
bool exitKey = false;
byte setState = 1;
int a = 1;

void setup() {
  Serial.begin(9600);
  pinMode(Setbutton, INPUT_PULLUP);
}

void loop() {
  setClick = false;
  setPush = false;
  setState = digitalRead(Setbutton);
  if (startKey == false && setState == 0) {   // Start time press buttom
    startMillis = millis();  
    startKey = true;
    endKey = false;
    pushKey = true;
    Serial.print("Start: ");
    Serial.println(startMillis);
  }
  if (startKey == true && setState == 1){   // End time press buttom
    endMillis = millis();
    endKey = true;
    startKey = false;
    pushKey = false;
    Serial.print("End: ");
    Serial.println(endMillis);
  }
  if (endKey == true && (endMillis - startMillis)>10 && (endMillis - startMillis)<3000){    //Click button
    setClick = true;
    endKey = false;
    Serial.print(endMillis);
    Serial.print(" - ");
    Serial.print(startMillis);
    Serial.print(" = ");
    Serial.println(endMillis - startMillis);
    Serial.println("setClick");
  } 
  if (pushKey == true && (millis() - startMillis)>3000) {    //Push button more 3 sec
    setPush = true;
    pushKey = false;
    Serial.print(endMillis);
    Serial.print(" - ");
    Serial.print(startMillis);
    Serial.print(" = ");
    Serial.println(millis() - startMillis);
    Serial.println("setPush");
  }
  


  switch (a) {
    case 1:
      Serial.println("temp");
      if (checkClick() == true) {
        a = 2;
      }
      if (checkPush() == true){
        a = 3;
      }
      break;
    case 2:
      Serial.println("set");
      if (checkClick() == true){
        a = 4;
      }
      exit();
      break;
    case 3:
      Serial.println("pass"); 
      exit();
      break;
    case 4:
      inputDigits(0);
      exit();
      break;
  }

}

void exit() {
  if (exitKey == false || setClick == true || setPush == true) {
    exitKey = true;
    exitMillis = millis();
  }
  if ((millis() - exitMillis)>5000){
     a = 1;
    exitKey = false;
  }
  
}

bool checkClick() { 
  if (setClick == true){
    return true; 
  }
  else {
    return false;
  }
  setClick = false;
}

bool checkPush() {
  if (setPush == true){
    return true; 
  }
  else {
    return false;
  }
  setPush = false;
}

void inputDigits(int address){
  
  Serial.println(EEPROM.read(address));
  exit();
}

