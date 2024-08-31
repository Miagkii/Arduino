#include <EEPROM.h>
const byte setButton = 2;
const byte defButton = 5;
const byte downButton = 3;
const byte upButton = 4;
unsigned long exitMillis;
bool exitKey = false;
bool inputLevel = false;
bool digitKey = false;
int listLevel = 1;
int setClick = 0;
int setPush = 0;
byte digits;

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
        startExitTime();
        checkExitTime();
        break;
      case 3:
        startExitTime();
        checkExitTime();
        break;
      case 5:
        startExitTime();
        checkExitTime();
        break;
      case 6:
        startExitTime();
        checkExitTime();
        break;
      case 7:
        startExitTime();
        checkExitTime();
        break;
      case 8:
        startExitTime();
        checkExitTime();
        break;
      case 9:
        startExitTime();
        Serial.println("set");
        checkInput();
        checkExitTime();
        break;
      case 10:
        startExitTime();
        Serial.println("pass"); 
        checkExitTime();
        break;
      case 11:
        Serial.println("set");
        startExitTime();
        updown();
        checkInput();
        checkExitTime();
        break;
      case 12:
        Serial.println("hy");
        startExitTime();
        updown();
        checkInput();
        checkExitTime();
        break;
      case 13:
        Serial.println("ls");
        startExitTime();
        updown();
        checkInput();
        checkExitTime();
        break;
      case 14:
        Serial.println("us");
        startExitTime();
        updown();
        checkInput();
        checkExitTime();
        break;
      case 15:
        startExitTime();
        checkExitTime();
        break;
      case 16:
        startExitTime();
        checkExitTime();
        break;
      case 17:
        startExitTime();
        checkExitTime();
        break;
      case 18:
        startExitTime();
        checkExitTime();
        break;
      case 19:
        startExitTime();
        checkExitTime();
        break;
      case 20:
        startExitTime();
        checkExitTime();
        break;
      case 21:
        startExitTime();
        checkExitTime();
        break;
      case 22:
        startExitTime();
        checkExitTime();
        break;
      case 23:
        startExitTime();
        checkExitTime();
        break;
      case 24:
        startExitTime();
        checkExitTime();
        break;
      case 25:
        startExitTime();
        checkExitTime();
        break;
      case 26:
        startExitTime();
        checkExitTime();
        break;
      case 27:
        startExitTime();
        checkExitTime();
        break;
      case 28:
        startExitTime();
        checkExitTime();
        break;
      case 29:
        startExitTime();
        checkExitTime();
        break;
      case 30:
        startExitTime();
        checkExitTime();
        break;
      case 31:
        startExitTime();
        checkExitTime();
        break;
      case 32:
        startExitTime();
        checkExitTime();
        break;
      case 33:
        startExitTime();
        checkExitTime();
        break;
      case 34:
        startExitTime();
        checkExitTime();
        break;
      case 35:
        startExitTime();
        checkExitTime();
        break;
      case 36:
        startExitTime();
        checkExitTime();
        break;
      case 37:
        startExitTime();
        checkExitTime();
        break;
      case 38:
        startExitTime();
        checkExitTime();
        break;
      case 39:
        startExitTime();
        checkExitTime();
        break;

    }
  }
  else {
    startExitTime();
    inputDigits();
    inputExit();
    checkExitTime();
  }
  

}

void startExitTime(){
  if (exitKey == false || set.click == true || set.push == true || def.click == true || def.push == true|| down.click == true || down.push == true|| up.click == true || up.push == true) {
    exitKey = true;
    exitMillis = millis();
  }
}
void checkExitTime() {
  if ((millis() - exitMillis)>5000){
    inputLevel = false;
    listLevel = 1;
    exitKey = false;
    digitKey = false;
  } 
}

void inputDigits(){
  if (digitKey == false){
    digits = EEPROM.read(listLevel);
    digitKey = true;
  }
  if (up.click == true && digits < 255) {
    digits += 1;
    up.click = false;
  }
  if (down.click == true && digits > 0) {
    digits -= 1;
    down.click = false;
  }
  Serial.println(digits);
}

void inputExit(){
    if (inputLevel == true && set.click == true){
    EEPROM.update(listLevel, digits);
    inputLevel = false;   
    exitKey = false;
    digitKey = false;
    Serial.print("Saved: ");
    Serial.println(digits);
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