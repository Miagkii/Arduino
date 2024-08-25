#include "Timer.h" //include timer library
Timer t; // craete a timer object

long number = 0;
long number1 = 0; //declear the variables
int digit_1 = 0;
int digit_2 = 0;
int digit_3 = 0;
int digit_4 = 0;
int timer_event = 0;

int cathode_1 = 2;
int cathode_2 = 3;
int cathode_3 = 4;
int cathode_4 = 5;

int latchPin = 9;
int clockPin = 10;
int dataPin = 8;

int count = 0;
int coun=0;
int digits[4] ;
int words[4];
int cathodePins[4] = {2, 3, 4, 5};

int ThermistorPin = 0;
int Vo;
int R1 = 10000;
float logR2, R2, T;
float A = 1.117990317e-03, B = 2.358140330e-04, C = 0.8197896127e-07;

byte letters[27] {B01000000,    //-
                  B01110111,    //A
                  B01111100,
                  B00111001,
                  B01011110,
                  B01111001,
                  B01110001,
                  B00111101,
                  B01110110,
                  B00000100,
                  B00011110,
                  B01110000,
                  B00111000,
                  B00110111,
                  B01010100,
                  B00111111,
                  B01110011,
                  B01100111,
                  B01010000,
                  B01101101,
                  B01111000,
                  B00111110,
                  B00011100,
                  B01100010,
                  B01000110,
                  B01101110,
                  B01011011     //Z
                  };



byte numbers[10] {B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111101, B00000111, B01111111, B01101111};

#define PUSHED LOW //buttons var
byte lastState = 0;
unsigned long startMillis;
const byte PinIn = 11;
const byte PinOut = 13;
byte val;
int a;
int b=0;

void setup() {
  Serial.begin(9600); //serial start and pin config
  pinMode(cathode_1, OUTPUT);
  pinMode(cathode_2, OUTPUT);
  pinMode(cathode_3, OUTPUT);
  pinMode(cathode_4, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(cathode_1, HIGH);
  digitalWrite(cathode_2, HIGH);
  digitalWrite(cathode_3, HIGH);
  digitalWrite(cathode_4, HIGH);
  Serial.println("Please enter a number between 0 and 9999");

  pinMode(PinIn, INPUT_PULLUP); // button
  pinMode(PinOut, OUTPUT);
  val = 0;  


  words[0]=13;
  words[1]=18;
  words[2]=24;
  words[3]=23;
}


void loop() {
t.update();
  byte thisState = digitalRead(PinIn);
  

  if (lastState != thisState)
  {
    lastState = thisState;
    startMillis = millis();
  }
  else
  val = 0;

  if (lastState == PUSHED && millis() - startMillis >= 2000UL) {
  val = 1;
  a=1;

  digitalWrite(PinOut, val);
  }
  
  switch (a) {
    case 0:
        
        Vo = analogRead(ThermistorPin);
        R2 = R1* (1023.0 / Vo - 1.0); // Calculate NTC resistance Vout=Vin*(R2/(R1+R2)) -->R2=(Vout*R1)/(Vin-Vout)  --> R2 = R1* (1023.0 / Vout - 1.0)
        logR2 = log(R2);
        T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
        T =  T - 273.15;
        number=T;
        if (number!=0 && number!=number1){
        number = T;
        t.stop(timer_event);
        cathode_high();
        break_number(number);
        Serial.println("case0");
        timer_event = t.every(1, display_number);
          if (number!=number1){
          number1=T;
        }
        }
      break;
    case 1:
      
      t.update();
      Serial.println("case1");
      if (b==0){
        t.stop(timer_event);
        cathode_high();
        timer_event = t.every(1, display_letters);
        b=1;
      
      }
      a=2;
      break;
  }



  t.update(); //timer update
  if (Serial.available()) { // read from serial
    t.stop(timer_event); //stop timer if anything to read
    cathode_high(); // blank the screen
    String s = Serial.readString(); //read the serial value
    number = (long)s.toInt(); //convert it to int
  if (number > 9999) { //check if the number is 0-9999
    Serial.println("Invalid number!\nPlease enter a number between 0 and 9999");
    } else {
    Serial.println(1);
    break_number(number);
    timer_event = t.every(5, display_number); // start timer again
   }
  } 
}

void break_number(long num) { // seperate the input number into 4 single digits

  digit_1 = num / 1000;
  digits[0] = digit_1;
  int dig_1_remove = num - (digit_1 * 1000);
  digit_2 = dig_1_remove / 100;
  digits[1] = digit_2;
  int dig_2_remove = dig_1_remove - (digit_2 * 100);
  digit_3 = dig_2_remove / 10;
  digits[2] = digit_3;
  digit_4 = dig_2_remove - (digit_3 * 10);
  digits[3] = digit_4;
}

void display_number() { //scanning

  cathode_high(); //black screen
  digitalWrite(latchPin, LOW); //put the shift register to read
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[digits[count]]); //send the data
  digitalWrite(cathodePins[count], LOW); //turn on the relevent digit
  digitalWrite(latchPin, HIGH); //put the shift register to write mode
  count++; //count up the digit
  if (count == 4) { // keep the count between 0-3
    count = 0;
  
  }
}

void display_letters() { //scanning

  cathode_high(); //black screen
  digitalWrite(latchPin, LOW); //put the shift register to read
  shiftOut(dataPin, clockPin, MSBFIRST, letters[words[coun]]); //send the data
  digitalWrite(cathodePins[coun], LOW); //turn on the relevent digit
  digitalWrite(latchPin, HIGH); //put the shift register to write mode
  coun++; //count up the digit
  if (coun == 4) { // keep the count between 0-3
    coun = 0;
  
  }
}


void cathode_high() { //turn off all 4 digits
  digitalWrite(cathode_1, HIGH);
  digitalWrite(cathode_2, HIGH);
  digitalWrite(cathode_3, HIGH);
  digitalWrite(cathode_4, HIGH);
}
