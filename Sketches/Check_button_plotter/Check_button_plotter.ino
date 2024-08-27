
const byte Setbutton = 2;
unsigned long startMillis, endMillis;
bool setClick = false;
bool setPush = false;
bool startKey = false;
bool endKey = false;
bool pushKey = false;
byte setState = 1;
byte a = 0;
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
  if (endKey == true && (endMillis - startMillis)>50 && (endMillis - startMillis)<3000){    //Click button
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

}
