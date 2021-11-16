#pragma once
#include"Vector.h"

class Odometry{
public:
  Odometry(const double wheel_width=555.0,
          const double encoder_ppr=8192,
          const double wheel_size=315.0);
  Vector update(long l_enc,long r_enc,double gyro_yaw,double pitch);
  Vector update2d(long l_enc,long r_enc,double gyro_yaw);
  Vector vec;
  Vector vec2d;
private:
  double pre_rad;
  long pre_pul;
  long pre_pul2d;
  double wheel_width;
  double encoder_ppr;
  double wheel_size;
};

Odometry::Odometry(const double wheel_width,
                 const double encoder_ppr,
                 const double wheel_size){
  this->wheel_width=wheel_width;
  this->encoder_ppr=encoder_ppr;
  this->wheel_size=wheel_size;
}

Vector Odometry::update(long l_enc,long r_enc,double gyro_yaw,double pitch){
  //odometry
  long rpul= -r_enc;
  long lpul= l_enc;

  double angle_rad=-gyro_yaw;

  long now_pul=rpul+lpul;
  double diff_pos=((now_pul-pre_pul)/2.0)*wheel_size*PI/encoder_ppr/1000.0;
  pre_pul=now_pul;

  vec.y+=diff_pos*cos(angle_rad)*cos(pitch);
  vec.x+=diff_pos*sin(angle_rad)*cos(pitch);
  vec.z+=diff_pos*sin(pitch);
  //vec.yaw=angle_rad;
  //pre_rad=angle_rad;
  return vec;
}

Vector Odometry::update2d(long l_enc,long r_enc,double gyro_yaw){
  //odometry
  long rpul= -r_enc;
  long lpul= l_enc;

  double angle_rad=-gyro_yaw;

  long now_pul=rpul+lpul;
  double diff_pos=((now_pul-pre_pul2d)/2.0)*wheel_size*PI/encoder_ppr/1000.0;
  pre_pul2d=now_pul;

  vec2d.y+=diff_pos*cos(angle_rad);
  vec2d.x+=diff_pos*sin(angle_rad);
  //vec.yaw=angle_rad;
  //pre_rad=angle_rad;
  return vec2d;
}
