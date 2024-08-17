#include "Timer.h" //include timer library
Timer t; // craete a timer object

long number = 0; //declear the variables
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
int digits[4] ;
int cathodePins[4] = {2, 3, 4, 5};

byte numbers[10] {B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111101, B00000111, B01111111, B01101111};

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
}

void loop() {
  t.update(); //timer update
  if (Serial.available()) { // read from serial
    t.stop(timer_event); //stop timer if anything to read
    cathode_high(); // blank the screen
    String s = Serial.readString(); //read the serial value
    number = (long)s.toInt(); //convert it to int
    if (number > 9999) { //check if the number is 0-9999
      Serial.println("Invalid number!\nPlease enter a number between 0 and 9999");
      } else {
      break_number(number);
      timer_event = t.every(1, display_number); // start timer again
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

void cathode_high() { //turn off all 4 digits
  digitalWrite(cathode_1, HIGH);
  digitalWrite(cathode_2, HIGH);
  digitalWrite(cathode_3, HIGH);
  digitalWrite(cathode_4, HIGH);
}