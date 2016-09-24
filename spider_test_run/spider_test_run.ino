#include <Servo.h>
#include "SpiderMotor.h"
#include <Adafruit_NeoPixel.h>

#define SERVO 6
#define LED 13
#define CAMERA 10
#define IR_DIST A0 

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
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(CAMERA,OUTPUT);

  digitalWrite(LED,HIGH);
  digitalWrite(CAMERA,LOW);
  
  pixels.begin();  
  motor.walk(-255);
}

int dist_val=0;
int last_state=0;
void loop() {
  // put your main code here, to run repeatedly:

 int val_left = 150*last_state;
 int val_right = 150*(!last_state);
  //Left
  pixels.setPixelColor(0, pixels.Color(val_left,0,val_right)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2); // Delay for a period of ti me (in milliseconds).
  //right
  pixels.setPixelColor(1, pixels.Color(val_right,0,val_left)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2); // Delay for a period of time (in milliseconds).

  last_state = !last_state;

  dist_val = analogRead(IR_DIST);
  Serial.print("IR Raw:");Serial.println(dist_val);
  delay(1000);
}
