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

struct sTime{
  unsigned long sMillis;
  byte state;
  bool startK;
  bool endK;
  bool pushK;
} set, t, f;



void setup() {
  Serial.begin(9600);
  pinMode(Setbutton, INPUT_PULLUP);
}

void loop() {
  setClick = false;
  setPush = false;
  set.state = digitalRead(Setbutton);
  t = set;
  set = start(t);
  
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
  if (set.startK == true && set.state == 1){   // End time press buttom
    set.sMillis = millis() - set.sMillis;
    set.endK = true;
    set.startK = false;
    set.pushK = false;
    Serial.print("duration: ");
    Serial.println(set.sMillis);
  }
  
  if (set.endK == true && set.sMillis>10 && set.sMillis<3000){    //Click button
    setClick = true;
    set.endK = false;
    Serial.println(set.sMillis);
    Serial.println("setClick");
    
  } 
  if (set.pushK == true && (millis() - set.sMillis)>3000) {    //Push button more 3 sec
    setPush = true;
    set.pushK = false;
   
    Serial.print("duration: ");
    Serial.println(millis() - set.sMillis);
    Serial.println("setPush");
  }
  
  
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

sTime start(sTime f){
  if (f.startK == false && f.state == 0){
    f.sMillis = millis();
    f.startK = true;
    f.endK = false;
    f.pushK = true;
    Serial.print("Start: ");
    Serial.println(f.sMillis);
  }
  return f;
}
/*
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
*/