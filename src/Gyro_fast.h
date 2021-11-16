#ifndef GYRO_FAST_H
#define GYRO_FAST_H

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================


class Gyro_fast{
  public:
  void set();
  void update();
  float degz();
  void reset();
  double rad();
  private:
  float degyaw,offset;
};

void Gyro_fast::set(){
  //Wire.begin();
    //Wire.setClock(400000UL);
    //Serial.begin(115200);
    //delay(5000);

  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(-31);
  mpu.setYGyroOffset(-247);
  mpu.setZGyroOffset(-220);
  mpu.setZAccelOffset(1455); // 1688 factory default for my test chip
  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
        attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
      /*  Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));   
        */   
  }
}


void Gyro_fast::update(){
  //Serial.println("loop");
    if (!dmpReady) return;
    //while (!mpuInterrupt&& fifoCount < packetSize) { }
//Serial.println("loop");
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        mpu.resetFIFO();
    } else if (mpuIntStatus & 0x02) {
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;

        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        static int16_t offset;
        float yaw = degrees(ypr[0]);
        static float preyaw;
        static float lot_c;
        if(yaw>preyaw+180){
          lot_c-=360;
        }
        if(yaw<preyaw-180){
          lot_c+=360;
        }

        preyaw=yaw;
        //float yaw = ypr[0]*57.295779513;
        /*
        byte buf[3];
        buf[0] = 'H';
        buf[1] = (yaw >> 8) & 0x00ff;
        buf[2] = yaw & 0x00ff;

        Serial.write(buf,3);
        */
      /*
      if(Serial.available()>0){
        if(Serial.read()=='R'){
          offset=yaw;
        }
      }
      yaw=yaw-offset;
      yaw=yaw*5;
      yaw=constrain(yaw,-126,126);
      Serial.write(byte(yaw+127));
      
      */
      //Serial.println(yaw);
      degyaw=yaw+lot_c;
    }
}

float Gyro_fast::degz(){
  return -(degyaw-offset);
}

void Gyro_fast::reset(){
  offset=degyaw;
}
double Gyro_fast::rad(){
  return ypr[0];
}

#endif
