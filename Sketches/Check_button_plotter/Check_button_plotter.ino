#include <EEPROM.h>
const byte Setbutton = 2;
unsigned long startMillis, exitMillis;
bool setClick = false;
bool setPush = false;
bool startKey = false;
bool endKey = false;
bool pushKey = false;
bool exitKey = false;
byte setState = 1;
bool b = false;
int a = 1;
int wayClick = 0;
int wayPush = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Setbutton, INPUT_PULLUP);
}

void loop() {
  setClick = false;
  setPush = false;
  setState = digitalRead(Setbutton);

  start(setState);
  /*
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
  */
  if (startKey == true && setState == 1){   // End time press buttom
    startMillis = millis() - startMillis;
    endKey = true;
    startKey = false;
    pushKey = false;
    Serial.print("End: ");
    Serial.println(startMillis);
  }

  if (endKey == true && startMillis>10 && startMillis<3000){    //Click button
    setClick = true;
    endKey = false;
    
    Serial.println(startMillis);
    Serial.println("setClick");
    
  } 
  if (pushKey == true && (millis() - startMillis)>3000) {    //Push button more 3 sec
    setPush = true;
    pushKey = false;
   
    Serial.print(" - ");
    Serial.print(startMillis);
    Serial.print(" = ");
    Serial.println(millis() - startMillis);
    Serial.println("setPush");
  }
  
  /*
  if (b == false){
    switch (a) {
      case 1:
        Serial.println("temp");
        wayClick = 2;
        wayPush = 3;
        checkClick(wayClick);
        checkPush(wayPush);
        break;
      case 2:
        Serial.println("set");
        checkInput();
        exit();
        break;
      case 3:
        Serial.println("pass"); 
        exit();
        break;
      case 4:
        
        exit();
        break;
    }
  }
  else {
    inputDigits(a);
  }
  */

}

void exit() {
  if (exitKey == false || setClick == true || setPush == true) {
    exitKey = true;
    exitMillis = millis();
  }
  if (b == true && setClick == true){
    b = false;
    
    exitKey = false;
  }
  
  if ((millis() - exitMillis)>5000){
    b = false;
    a = 1;
    exitKey = false;
  }
  
}



void checkClick(int c){
  if (setClick == true){
    a = c; 
  }
  setClick = false;
}

void checkPush(int p){
  if (setPush == true){
    a = p; 
  }
  setPush = false;
}

void checkInput() {
    if (setClick == true){
    b = true; 
  }
  setClick = false;
}

void inputDigits(int address){
  Serial.print("address ");
  Serial.println(address);
  Serial.print("data ");
  Serial.println(EEPROM.read(address));
  exit();
}

void start(byte set){
if (startKey == false && set == 0) {   // Start time press buttom
    startMillis = millis();  
    startKey = true;
    endKey = false;
    pushKey = true;
    Serial.print("Start: ");
    Serial.println(startMillis);
  }
}