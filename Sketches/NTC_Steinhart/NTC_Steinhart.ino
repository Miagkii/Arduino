

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float A = 1.117990317e-03, B = 2.358140330e-04, C = 0.8197896127e-07;  // Steinhart-Hart and Hart Coefficients



void setup() {
Serial.begin(9600);

}

void loop() {

Vo = analogRead(ThermistorPin);
R2 = R1* (1023.0 / (float)Vo - 1.0);
logR2 = log(R2);
T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
T =  T - 273.15;

Serial.print("TEMP = ");
Serial.print(T);
Serial.println(" C");

delay(1000);     // Time delay 10 Milliseconds


}