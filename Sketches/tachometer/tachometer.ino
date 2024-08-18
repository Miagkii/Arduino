/*
  Created 2017
  by AlexGyver
  AlexGyver Home Labs Inc.
*/

byte n = 1;      // число лопастей
float r = 3.5;   // радиус тела В САНТИМЕТРАХ

float r_speed, rev_time;
volatile unsigned long lastflash, flash, lastshow;
unsigned int RPM;
String spaces = "       ";

void setup() {
  Serial.begin(9600);                  // открыть порт
  attachInterrupt(0, sens, RISING);    // подключить прерывание на 2 пин при повышении сигнала
  pinMode(3, OUTPUT);                  // 3 пин как выход
  digitalWrite(3, HIGH);               // подать 5 вольт на 3 пин
  
}
void sens() {
  flash = micros() - lastflash;   // вычислить время между двумя оборотами
  lastflash = micros();           // запомнить время последнего оборота
}

void loop() {
  if (micros() - lastflash > 1000000) { // если сигнала нет больше секунды
    RPM = 0;                            // считаем, что всё стоит и не крутится
    r_speed = 0;
  } else {
    rev_time = (float) flash / 1000000 * n;             // время одного оборота в секундах, с учётом числа лопастей
    RPM = (float) 60 / rev_time;                        // обороты в минуту
    r_speed = (float) 2 * 3.1415 * r / 100 / rev_time * 3.6;  // скорость точки на радиусе, км/ч
  }
  if (millis() - lastshow > 300) {  // кадждые 300 миллисекунд
    Serial.println(r_speed);
    lastshow = millis();  // сброс таймера
  }
}
