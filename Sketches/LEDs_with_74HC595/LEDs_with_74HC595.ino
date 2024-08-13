
int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

byte leds = 0;

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);   // Low signal to start bit data transmission
   shiftOut(dataPin, clockPin, LSBFIRST, leds);   // ShiftOut data(dataPin, clockPin, leds) and bitorder LSBFIRST
   digitalWrite(latchPin, HIGH); // High signal to latch data transmission
}

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);    // Writes one bit to the variable leds, at position i
    if (i>=1)
    {
      bitClear(leds,i-1);   // Clears (writes a 0 to) a bit of a numeric variable leds, at position i-1
    }
    updateShiftRegister();
    delay(tDelay);
  }
}

