#include <EEPROM.h>
const byte setButton = 2;
const byte defButton = 5;
const byte downButton = 3;
const byte upButton = 4;
unsigned long exitMillis;
bool exitKey = false;
bool inputLevel = false;
int listLevel = 1;
int setClick = 0;
int setPush = 0;

struct buttons{
  unsigned long buttonMillis;
  byte state;
  bool startKey;
  bool endKey;
  bool pushKey;
  bool click;
  bool push;
} set, def, down, up, temp, function;

void setup() {
  Serial.begin(9600);
  pinMode(setButton, INPUT_PULLUP);
  pinMode(defButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
}

void loop() {
  set.click = false;
  set.push = false;
  def.click = false;
  def.push = false;
  down.click = false;
  down.push = false;
  up.click = false;
  up.push = false;

  set.state = digitalRead(setButton);
  def.state = digitalRead(defButton);
  down.state = digitalRead(downButton);
  up.state = digitalRead(upButton);

  temp = set;
  set = stateCheck(temp);
  temp = def;
  def = stateCheck(temp);
  temp = down;
  down = stateCheck(temp);
  temp = up;
  up = stateCheck(temp);

  if (inputLevel == false){
    switch (listLevel) {
      case 1:
        Serial.println("temp");
        setClick = 11;
        setPush = 10;
        checkClick();
        checkPush();
        break;
      case 2:
        exit();
        break;
      case 3:
        exit();
        break;
      case 5:
        exit();
        break;
      case 6:
        exit();
        break;
      case 7:
        exit();
        break;
      case 8:
        exit();
        break;
      case 9:
        Serial.println("set");
        checkInput();
        exit();
        break;
      case 10:
        Serial.println("pass"); 
        exit();
        break;
      case 11:
        Serial.println("set");
        exit();
        updown();
        checkInput();
        break;
      case 12:
        Serial.println("hy");
        exit();
        updown();
        checkInput();
        break;
      case 13:
        Serial.println("ls");
        exit();
        updown();
        checkInput();
        break;
      case 14:
        exit();
        break;
      case 15:
        exit();
        break;
      case 16:
        exit();
        break;
      case 17:
        exit();
        break;
      case 18:
        exit();
        break;
      case 19:
        exit();
        break;
      case 20:
        exit();
        break;
      case 21:
        exit();
        break;
      case 22:
        exit();
        break;
      case 23:
        exit();
        break;
      case 24:
        exit();
        break;
      case 25:
        exit();
        break;
      case 26:
        exit();
        break;
      case 27:
        exit();
        break;
      case 28:
        exit();
        break;
      case 29:
        exit();
        break;
      case 30:
        exit();
        break;
      case 31:
        exit();
        break;
      case 32:
        exit();
        break;
      case 33:
        exit();
        break;
      case 34:
        exit();
        break;
      case 35:
        exit();
        break;
      case 36:
        exit();
        break;
      case 37:
        exit();
        break;
      case 38:
        exit();
        break;
      case 39:
        exit();
        break;

    }
  }
  else {
    inputDigits(listLevel);
  }
  

}

void exit() {
  if (exitKey == false || set.click == true || set.push == true || def.click == true || def.push == true|| down.click == true || down.push == true|| up.click == true || up.push == true) {
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

void checkClick(){
  if (set.click == true){
    listLevel = setClick; 
  }
  set.click = false;
}

void checkPush(){
  if (set.push == true){
    listLevel = setPush; 
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
  exit();
  Serial.print("address ");
  Serial.println(address);
  Serial.print("data ");
  Serial.println(EEPROM.read(address));
}
void updown(){
  if (listLevel > 10 && listLevel < 40) {
    if (up.click == true){
      if (listLevel < 39){
        listLevel += 1;
        up.click = false;
      }
      else {
        listLevel = 11;
        up.click = false;
      }
    }
    if (down.click == true){
      if (listLevel > 11){
        listLevel -= 1;
        down.click = false;
      }
      else {
        listLevel = 39;
        down.click = false;
      }
    }
  }
}

buttons stateCheck(buttons function){
  if (function.startKey == false && function.state == 0){ // Start time press button
    function.buttonMillis = millis();
    function.startKey = true;
    function.endKey = false;
    function.pushKey = true;
    Serial.print("Start: ");
    Serial.println(function.buttonMillis);
  }
    if (function.startKey == true && function.state == 1){   // End time press buttom
    function.buttonMillis = millis() - function.buttonMillis;
    function.endKey = true;
    function.startKey = false;
    function.pushKey = false;
    Serial.print("duration1: ");
    Serial.println(function.buttonMillis);
  }
  
  if (function.endKey == true && function.buttonMillis>10 && function.buttonMillis<3000){    // Check click button
    function.click = true;
    function.endKey = false;
    Serial.println(function.buttonMillis);
    Serial.println("Click");
    
  } 
  if (function.pushKey == true && (millis() - function.buttonMillis)>3000) {    // Check push button more 3 sec
    function.push = true;
    function.pushKey = false;
    Serial.print("duration2: ");
    Serial.println(millis() - function.buttonMillis);
    Serial.println("Push");
  }
  return function;
}