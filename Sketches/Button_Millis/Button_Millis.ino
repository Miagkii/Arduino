#define PUSHED LOW

byte lastState = 1;
unsigned long startMillis;
const byte PinIn = 2;
const byte PinOut = 13;
byte val;

void setup()
{
  Serial.begin(9600);
  pinMode(PinIn, INPUT_PULLUP);
  pinMode(PinOut, OUTPUT);
  val = 0;
}

void loop()
{

  byte thisState = digitalRead(PinIn);
  Serial.println(thisState);

  if (lastState != thisState)
  {
    lastState = thisState;
    startMillis = millis();
  }
  else
  val = 0;

  if (lastState == PUSHED && millis() - startMillis >= 2000UL)
  val = 1;

  digitalWrite(PinOut, val);

}



