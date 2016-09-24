#define LED 13
#define CAMERA 10
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello world!");
  pinMode(LED,OUTPUT);
  pinMode(CAMERA,OUTPUT);
}

int last_state=0;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,last_state);
  digitalWrite(CAMERA,last_state);
  last_state = !last_state;
  delay(2000);
}
