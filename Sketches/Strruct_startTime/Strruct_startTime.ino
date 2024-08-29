
struct startTime {
  unsigned long startM;
  bool startK;
  bool endK;
  bool pushK;
} a,b,c;
unsigned long r = 10;

void setup() {
  Serial.begin(9600);
}
void loop() {
 
c = start(startTime{r,1,1,1});
Serial.println(c.startM);
}

startTime start(startTime b){


  
  
  return b;
  
}
