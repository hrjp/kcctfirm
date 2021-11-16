#pragma once
#include <Arduino.h>

class Pixy_analog{
  public:
  Pixy_analog(int pin_num);
  void update();
  bool flag();
  int point_x();
  bool finish(int diff);
  private:
  int pin_num_;
  int val_min=50;
  int val_max=950;
  bool flag_;
  int point;
};


Pixy_analog::Pixy_analog(int pin_num){
  pin_num_=pin_num;
}

bool Pixy_analog::flag(){
  return flag_;
}

int Pixy_analog::point_x(){
  return point;
}

void Pixy_analog::update(){
  int readval=analogRead(pin_num_);
  flag_=val_min<readval&&readval<val_max;
  point=flag_*map(readval,val_min,val_max,-100,100);
}

bool Pixy_analog::finish(int diff){
  return ((-diff<point&&point<diff)&&flag_);
}
