#include  "SpiderMotor.h"
#include <arduino.h>

SpiderMotor::SpiderMotor(int walk_0,int walk_1,
                         int walk_pwm,
                         int rotate_0,int rotate_1,
                         int rotate_pwm)
{
  m_walk_0 = walk_0;
  m_walk_1 = walk_1;
  m_walk_pwm = walk_pwm;

  m_rotate_0 = rotate_0;
  m_rotate_1 = rotate_1;
  m_rotate_pwm = rotate_pwm;
  
  pinMode(m_walk_0,OUTPUT);
  pinMode(m_walk_1,OUTPUT);
  pinMode(m_walk_pwm,OUTPUT);

  pinMode(m_rotate_0,OUTPUT);
  pinMode(m_rotate_1,OUTPUT);
  pinMode(m_rotate_pwm,OUTPUT);

  stopWalking();
  stopRotating();

  m_dir=0;
}
void SpiderMotor::walk(int pwm){
  int v = abs(pwm);
  if(v>255) return;

  if(pwm>0){
    digitalWrite(m_walk_0,1);
    digitalWrite(m_walk_1,0);
  }else if(pwm<0){
    digitalWrite(m_walk_0,0);
    digitalWrite(m_walk_1,1);
  }else{//pwm=0;
    stopWalking();
  }
  //write speed
  analogWrite(m_walk_pwm,v);
  if(pwm>0){
    m_dir =1;
  }else if(pwm<0){
    m_dir=-1;
  }else{
    m_dir=0;
  }
}

void SpiderMotor::rotate(int pwm){
   int v = abs(pwm);
  if(v>255) return;

  if(pwm>0){
    digitalWrite(m_rotate_0,1);
    digitalWrite(m_rotate_1,0);
  }else if(pwm<0){
    digitalWrite(m_rotate_0,0);
    digitalWrite(m_rotate_1,1);
  }else{//pwm=0;
    stopRotating();
  }
  //write speed
  analogWrite(m_rotate_pwm,v);
}
void SpiderMotor::stopWalking(){
  digitalWrite(m_walk_0,0);
  digitalWrite(m_walk_1,0);
  digitalWrite(m_walk_pwm,0);
  m_dir=0;
}
void SpiderMotor::stopRotating(){  
  digitalWrite(m_rotate_0,0);
  digitalWrite(m_rotate_1,0);
  digitalWrite(m_rotate_pwm,0);
}

void SpiderMotor::brakeWaking(){
  digitalWrite(m_walk_0,1);
  digitalWrite(m_walk_1,1);
  digitalWrite(m_walk_pwm,0);
   m_dir=0;
}
void SpiderMotor::brakeRotating(){
  digitalWrite(m_rotate_0,1);
  digitalWrite(m_rotate_1,1);
  digitalWrite(m_rotate_pwm,0);
}







