#include <EEPROM.h>
const byte Setbutton = 2;
unsigned long exitMillis;
bool exitKey = false;
bool inputLevel = false;
int listLevel = 1;
int wayClick = 0;
int wayPush = 0;

struct buttons{
  unsigned long sMillis;
  byte state;
  bool startKey;
  bool endKey;
  bool pushKey;
  bool click;
  bool push;
} set, temp, function;

void setup() {
  Serial.begin(9600);
  pinMode(Setbutton, INPUT_PULLUP);
}

void loop() {
  set.click = false;
  set.push = false;
  set.state = digitalRead(Setbutton);
  temp = set;
  set = stateCheck(temp);
   
  if (inputLevel == false){
    switch (listLevel) {
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
    inputDigits(listLevel);
  }
  

}

void exit() {
  if (exitKey == false || set.click == true || set.push == true) {
    exitKey = true;
    exitMillis = millis();
  }
  if (inputLevel == true && set.click == true){
    inputLevel = false;
    
    exitKey = false;
  }
  
  if ((millis() - exitMillis)>5000){
    inputLevel = false;
    listLevel = 1;
    exitKey = false;
  }
  
}



void checkClick(int c){
  if (set.click == true){
    listLevel = c; 
  }
  set.click = false;
}

void checkPush(int p){
  if (set.push == true){
    listLevel = p; 
  }
  set.push = false;
}

void checkInput() {
    if (set.click == true){
    inputLevel = true; 
  }
  set.click = false;
}

void inputDigits(int address){
  Serial.print("address ");
  Serial.println(address);
  Serial.print("data ");
  Serial.println(EEPROM.read(address));
  exit();
}

buttons stateCheck(buttons function){
  if (function.startKey == false && function.state == 0){ // Start time press button
    function.sMillis = millis();
    function.startKey = true;
    function.endKey = false;
    function.pushKey = true;
    Serial.print("Start: ");
    Serial.println(function.sMillis);
  }
    if (function.startKey == true && function.state == 1){   // End time press buttom
    function.sMillis = millis() - function.sMillis;
    function.endKey = true;
    function.startKey = false;
    function.pushKey = false;
    Serial.print("duration1: ");
    Serial.println(function.sMillis);
  }
  
  if (function.endKey == true && function.sMillis>10 && function.sMillis<3000){    // Check click button
    function.click = true;
    function.endKey = false;
    Serial.println(function.sMillis);
    Serial.println("seftClick");
    
  } 
  if (function.pushKey == true && (millis() - function.sMillis)>3000) {    // Check push button more 3 sec
    function.push = true;
    function.pushKey = false;
    Serial.print("duration2: ");
    Serial.println(millis() - function.sMillis);
    Serial.println("setPush");
  }
  return function;
}