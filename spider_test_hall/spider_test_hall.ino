#define HALL A4
int counter=0;
unsigned long last_trigger=0;
void isr_hall()
{
  
  unsigned long t = micros();
  if(t-last_trigger>200000){
    counter++;
    Serial.print("triggered:");Serial.println(counter);
    last_trigger = t;
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Hello world!");
  // put your setup code here, to run once:
  pinMode(HALL, INPUT);
  counter=0;
  attachInterrupt(HALL,isr_hall,FALLING);
}

void loop() {
  delay(50);
}
