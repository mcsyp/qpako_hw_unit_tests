#ifndef _SPIDER_CTL_H_
#define _SPIDER_CTL_H_


class SpiderMotor{
public:
  SpiderMotor(int walk_0,int walk_1,
              int walk_pwm,
              int rotate_0,int rotate_1,
              int rotate_pwm);
  void walk(int pwm);
  void rotate(int pwm);

  void stopWalking();
  void stopRotating();

  void brakeWaking();
  void brakeRotating();

  int dir(){return m_dir;}
private:
  int m_dir;
  
  int m_walk_0; //walk pin 0
  int m_walk_1; //walk pin 1
  int m_walk_pwm; //walk pin pwm
  int m_rotate_0; //rotate pin 0
  int m_rotate_1; //rotate pin 1
  int m_rotate_pwm; //rotate pin pwm
};

#endif







