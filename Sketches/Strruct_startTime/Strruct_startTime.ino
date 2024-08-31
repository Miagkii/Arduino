
struct sTime {
  unsigned long sMillis;
  byte state;
  bool startK;
  bool endK;
  bool pushK;
} a,b,c,f;
unsigned long r = 10;

void setup() {
  Serial.begin(9600);
}
void loop() {

c.sMillis = 9;
f.sMillis = c.sMillis;

c = start(f);
Serial.println(c.sMillis);
}

startTime start(startTime b){
  if (b.sMillis > 10){
    b.sMillis = 88;
  }
  return b;
  
}
