#define BATT A2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello world!");
  pinMode(BATT,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val =  analogRead(BATT);
  Serial.print("val:");Serial.println(val);
  delay(1000);
}
