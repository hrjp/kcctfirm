#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define TRUE_NORTH_OFFSET_DEG 7.0

class Gyro_9axis{
  public:
  Gyro_9axis();
  void set();
  void update();
  float degz();
  double rad();
  double magyaw();
  double getPitch();
  double getRoll();
  imu::Quaternion quat;
  imu::Vector<3> angular_vel;
  imu::Vector<3> accel;
  imu::Vector<3> mag;
  private:
  double roll,pitch;
  double yaw,myaw;//[rad]
  Adafruit_BNO055 bno;
  void QuaternionToEulerAngles(double q0, double q1, double q2, double q3,
                             double& roll, double& pitch, double& yaw);
};

Gyro_9axis::Gyro_9axis():bno(-1, 0x28){}

void Gyro_9axis::set(){
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);

}

void Gyro_9axis::update(){
  mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  quat = bno.getQuat();
  accel=bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);// m/s^2
  angular_vel=bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);// rad/s

  
  myaw=atan2(mag.x(),mag.y())-TRUE_NORTH_OFFSET_DEG*DEG_TO_RAD;
  QuaternionToEulerAngles(quat.w(),quat.x(),quat.y(),quat.z(),roll,pitch,yaw);
  //Serial.print(absyaw*180/3.141592-7.0);
}

float Gyro_9axis::degz(){
  return yaw*RAD_TO_DEG;
}

double Gyro_9axis::rad(){
  return -yaw;
}

double Gyro_9axis::magyaw(){
  return myaw;
}

void Gyro_9axis::QuaternionToEulerAngles(double q0, double q1, double q2, double q3,
                             double& roll, double& pitch, double& yaw)
{
    double q0q0 = q0 * q0;
    double q0q1 = q0 * q1;
    double q0q2 = q0 * q2;
    double q0q3 = q0 * q3;
    double q1q1 = q1 * q1;
    double q1q2 = q1 * q2;
    double q1q3 = q1 * q3;
    double q2q2 = q2 * q2;
    double q2q3 = q2 * q3;
    double q3q3 = q3 * q3;
    roll = atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3);
    pitch = asin(2.0 * (q0q2 - q1q3));
    yaw = atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3);
}

double Gyro_9axis::getPitch(){
  return pitch;
}

double Gyro_9axis::getRoll(){
  return roll;
}