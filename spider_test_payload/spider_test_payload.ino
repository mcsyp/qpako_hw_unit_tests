 #include <Servo.h>
#include "SpiderMotor.h"
#include <Adafruit_NeoPixel.h>

#define SERVO 6
#define LED 13
#define CAMERA 10

#define MOTOR_F_1 7
#define MOTOR_F_2 8
#define MOTOR_F_PWM 9

#define MOTOR_R_1 4
#define MOTOR_R_2 3
#define MOTOR_R_PWM 5

#define RGBLED A1
#define RGBLED_PIXELS 2

SpiderMotor motor(MOTOR_F_1,MOTOR_F_2,MOTOR_F_PWM,MOTOR_R_1,MOTOR_R_2,MOTOR_R_PWM);
Servo myservo;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(RGBLED_PIXELS, RGBLED);

void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVO);
  pinMode(LED,OUTPUT);
  pinMode(CAMERA,OUTPUT);

  digitalWrite(LED,HIGH);
  digitalWrite(CAMERA,LOW);
  
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.walk(255);
  motor.rotate(255);
  myservo.write(90);

  //Left
  pixels.setPixelColor(0, pixels.Color(150,0,0)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2); // Delay for a period of ti me (in milliseconds).
  //right
  pixels.setPixelColor(1, pixels.Color(0,0,150)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2); // Delay for a period of time (in milliseconds).
  
  delay(1000);
  
  motor.walk(-255);
  motor.rotate(-255);
  myservo.write(30);
  
  //Left
  pixels.setPixelColor(0, pixels.Color(0,0,150)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2); // Delay for a period of time (in milliseconds).
  //right
  pixels.setPixelColor(1, pixels.Color(150,0,0)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2); // Delay for a period of time (in milliseconds).
  
  delay(1000);
}
