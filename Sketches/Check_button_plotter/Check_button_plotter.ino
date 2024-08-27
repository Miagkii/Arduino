const byte PUSHED = 0;

unsigned long startMillis;
const byte Setbutton = 2;
const byte outled = 13;
byte push;
byte click = 0;
byte lastState = 1;
byte thisState = 1;
bool clickKey = false;
bool pushKey = false;
bool clickEnd = false;
int b;

void setup() {
  Serial.begin(9600);
  pinMode(outled, OUTPUT);
  pinMode(Setbutton, INPUT_PULLUP);
  click = 0;
}

void loop() {
  
  click = 0;
  push = 0;

  thisState = digitalRead(Setbutton);
  
  if (thisState == PUSHED && lastState != thisState)
  {
    startMillis = millis();
    b=1;
    
  }
  
  if (b == 1 && lastState == thisState) {
    if ((millis()-startMillis)<3000) {
      clickKey = true;
    }
    if ((millis()-startMillis)>3000) {
      pushKey = true;

    }
    b = 0;
  }

  if (clickKey == true && (millis()-startMillis)>50){
  
    click = 1;
    clickKey = false;
    Serial.println("click");
  }

  
  if (pushKey == true){
  
    push = 1;
    pushKey = false;
    Serial.println("push");
  }
  
  

}
