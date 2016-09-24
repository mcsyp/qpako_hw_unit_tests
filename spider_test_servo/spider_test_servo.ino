#include <Servo.h>
#define SERVO 6
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(90);
  delay(800);
  myservo.write(60);
  delay(800);
}
