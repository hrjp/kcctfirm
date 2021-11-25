#include <Arduino.h>
#include "Cytron_MD13S.h"
#include"ps3i2clib.h"
//#include<cout.h>

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <RosArrayPublisher.h>

//#include "Gyro_fast.h"
#include "Gyro_9axis.h"
#include <Encoders.h>
#include <cout.h>
#include "Vector.h"
#include "PIDF.h"
#include "Pixy_analog.h"
#include "Odometry.h"
//#include "GPS.h"

//1:rosからのcmd_velで動く
//0:rosを介さずコントローラの値で動く




ENCODERS Encoders(45,48);
Gyro_9axis gyro;
int x, y, z;
MD13S rmo(22,23); //(PWM_PIN,invert_PIN)
MD13S lmo(20,21);
PS3I2C ps(0x74);
PS3I2C psm(0x73);

//新機体
const double wheel_width=555.0;
const double encoder_ppr=8192;
const double wheel_size=315.0;//空気圧で変動
Odometry odom(wheel_width,encoder_ppr,wheel_size*0.931);

int lp=1500,rp=1500;
double pos_x,pos_y,angle_offset,angle_deg,angle_rad;

Vector body_vel;
Vector target_vel;

//* 190920_1730
// PID r_vel(100.0,1500,350);
// PID l_vel(100.0,1500,350);

//* 190920_1731, GOOD?
//PID r_vel(100.0,1000,350);
//PID l_vel(120.0,1000,350);

//* 190920_1731, Bad, Iの値で悪化しているよう
// PID r_vel(120.0,1200,350);
// PID l_vel(120.0,1200,350);
//2020.9.21 振れる
//PID r_vel(110.0,640,350);
//PID l_vel(110.0,640,350);
//2021.3.10
//PID r_vel(100.0,540,350);
//PID l_vel(100.0,540,350);

//PID r_vel(80.0,440,350);
//PID l_vel(80.0,440,350);

PID r_vel(80.0,440,350,250.0);
PID l_vel(80.0,440,350,250.0);

PID pixypid(0.3,0.0,0.1);
PID dispid(100.0,0.0,10);

bool using_cmd_vel;
//int ditect_mode;
//double human_dis;
//Pixy_analog pixy(A7);

const int e_stop_pin=25;

void messageCb(const geometry_msgs::Twist& twist) {
  //const float linear_x = 6*twist.linear.x;
  //const float angle_z = 0.5*twist.angular.z;
  //if(using_cmd_vel){
    //target_vel.y=2.0*twist.linear.x;
    //target_vel.yaw=0.6*twist.angular.z;
    target_vel.y=twist.linear.x;
    target_vel.yaw=twist.angular.z*1.5;
    target_vel.x=twist.linear.y;

  if(!digitalRead(e_stop_pin)){
    target_vel.y=0;
    target_vel.yaw=0;
  }

    //human_dis=twist.linear.y;
    //ditect_mode=twist.angular.x;
  //}
  //rmo.writeMicroseconds(1500+100*(linear_x+angle_z));
  //lmo.writeMicroseconds(1500-100*(linear_x-angle_z));
  /*
  if(twist.angular.x){
    pos_x=0;
    pos_y=0;
    angle_offset=angle_rad;
  }
  */
}

ros::NodeHandle nh;

ros::Subscriber<geometry_msgs::Twist> sub("final_cmd_vel", &messageCb);

//std_msgs::Float32MultiArray float_pub_array;
//ros::Publisher float_pub("float_sensor_data", &float_pub_array);
RosArrayPublisher<std_msgs::Float32MultiArray> float_pub(nh,"float_sensor_data",20);



void setup() {
   Wire.begin();
   Wire.setSDA(34);
   Wire.setSCL(33);
   //Wire.setClock(400000UL);
   gyro.set();
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  nh.initNode();
  nh.subscribe(sub);
  pinMode(26,INPUT_PULLUP);
  Encoders.Encoder1.set(8192);
  Encoders.Encoder2.set(8192);
  Encoders.set(8192);
  Serial.begin(57600);

  /*
  float_pub_array.data = (float *)malloc(sizeof(float)*5);
  float_pub_array.data_length=5;
  float_pub_array.data[0]=0.0;
  float_pub_array.data[1]=0.0;
  float_pub_array.data[2]=0.0;
  float_pub_array.data[3]=0.0;
  float_pub_array.data[4]=0.0;
  nh.advertise(float_pub);
  */
  r_vel.max_i(0.3);
  l_vel.max_i(0.3);

  pinMode(e_stop_pin,INPUT_PULLUP);
}

void loop() {
  //各センサー，モジュールの更新
  
  gyro.update();
  ps.update();
  psm.update();
  odom.update(Encoders.Encoder2.read_pulse(),Encoders.Encoder1.read_pulse(),gyro.rad(),-gyro.getRoll());
  odom.update2d(Encoders.Encoder2.read_pulse(),Encoders.Encoder1.read_pulse(),gyro.rad());

  static bool useing_line_con=false;
  static int A_Ly=0;
  static int A_Rx=0;
  if(ps.C_Select()){
    useing_line_con=false;
  }
  if(psm.C_Select()){
    useing_line_con=true;
  }
  if(useing_line_con){
    A_Ly=psm.A_Ly();
    A_Rx=psm.A_Rx();
  }
  else{
    A_Ly=ps.A_Ly();
    A_Rx=ps.A_Rx();
  }
  //pixy.update();

  //手動と自動の切り替えスイッチ
  using_cmd_vel=digitalRead(26);

//エンコーダから読み取ったタイヤの速度[m/s]
double r_rot=-Encoders.Encoder1.read_rpm()*PI/60.0*wheel_size/1000.0;
double l_rot=Encoders.Encoder2.read_rpm()*PI/60.0*wheel_size/1000.0;
//タイヤの目標速度[m/s]
double r_target=target_vel.y+0.5*wheel_width/1000.0*target_vel.yaw;
double l_target=target_vel.y-0.5*wheel_width/1000.0*target_vel.yaw;

  //速度制御
  const int max_power=300;
  r_vel.update(r_rot,r_target);
  l_vel.update(l_rot,l_target);
  int dir_r=(target_vel.y+target_vel.yaw)>0;
  int dir_l=(target_vel.y-target_vel.yaw)>0;

  if(abs(r_rot)<0.01&&abs(l_rot)<0.01){
    r_vel.max_i(0.1);
    l_vel.max_i(0.1);
  }
  else{
    r_vel.max_i(0.3);
    l_vel.max_i(0.3);
  }
  /*
  //人検出の処理
  const int max_power_dis=110;
  pixypid.update(pixy.point_x(),0);
  dispid.update(target_vel.x,0.5);

  int dis_result=constrain(dispid.result_val(),-max_power_dis,max_power_dis);

  //人検出シーケンス
  static int sik=0;
  static unsigned long wait_t=0;
  static int pre_d=0;
  static int gomi_mode=0;
  const long ditect_time=5;
  static int d_time=0;
  if(sik==0&&(ditect_mode-pre_d==1)){
    wait_t=millis();
    sik++;
  }
  if(sik==1){
    if(wait_t+20000<millis()){
      sik++;
    }
  }
  if(sik==2){
    gomi_mode=true;
    sik++;
  }
  if(sik==3){
    if(abs(target_vel.x)<0.8){
      if(pixy.finish(10)){
        d_time++;
      }
    }
    else{
      d_time=0;
    }
    if(d_time>ditect_time){
      gomi_mode=2;
    }
  }
  if(!ditect_mode){
    sik=0;
    gomi_mode=false;
  }



  pre_d=ditect_mode;
*/
//モータへの出力/////////////////////////////////////
  if(using_cmd_vel){
//人検出
/*
    if(gomi_mode==1){
      rmo.writeMicroseconds(1500+constrain(pixypid.result_val()-dis_result,-max_power,max_power));
      lmo.writeMicroseconds(1500+constrain(pixypid.result_val()+dis_result,-max_power,max_power));
    }
    else if(gomi_mode==2){
      rmo.writeMicroseconds(1500);
      lmo.writeMicroseconds(1500);
    }*/
//cmd_velで走行
    //else{
      if(!digitalRead(e_stop_pin)){
        rmo.writeMicroseconds(1500);
        lmo.writeMicroseconds(1500);
      }
      else{
        if(-0.03<(r_target)&&(r_target)<0.03){
          rmo.writeMicroseconds(1500);
          r_vel.reset_i();
        }
        else{
          rmo.writeMicroseconds(1500+constrain(r_vel.result_val(),-max_power*!dir_r,max_power*dir_r));
        }


        if(-0.03<(l_target)&&(l_target)<0.03){
          lmo.writeMicroseconds(1500);
          l_vel.reset_i();
        }
        else{
          lmo.writeMicroseconds(1500-constrain(l_vel.result_val(),-max_power*!dir_l,max_power*dir_l));
        }
      }

    }
  //}
//コントローラから操作
  else{
    rmo.writeMicroseconds(map(0.8*(A_Ly+A_Rx-255),127,-127,1500-max_power,1500+max_power));
    lmo.writeMicroseconds(map(0.8*(A_Ly-A_Rx),-127,127,1500-max_power,1500+max_power));
  }
  //速度の送信
  //double body_vel_x=(-Encoders.Encoder1.read_rpm()+Encoders.Encoder2.read_rpm())/2.0*PI/60.0*wheel_size/2.0/1000.0;
  double body_vel_x=(-Encoders.Encoder1.read_rpm()+Encoders.Encoder2.read_rpm())*PI*wheel_size/(60.0*1000.0);
 //3d odom
  float_pub.array.data[0]=odom.vec.x;//x
  float_pub.array.data[1]=odom.vec.y;//y
  float_pub.array.data[2]=odom.vec.z;//z
  //imu
  float_pub.array.data[3]=gyro.accel.x();//x
  float_pub.array.data[4]=gyro.accel.y();//y
  float_pub.array.data[5]=gyro.accel.z();//z
  float_pub.array.data[6]=gyro.angular_vel.x()*DEG_TO_RAD;//x
  float_pub.array.data[7]=gyro.angular_vel.y()*DEG_TO_RAD;//y
  float_pub.array.data[8]=gyro.angular_vel.z()*DEG_TO_RAD;//z
  float_pub.array.data[9]=gyro.quat.x();//x
  float_pub.array.data[10]=gyro.quat.y();//y
  float_pub.array.data[11]=gyro.quat.z();//z
  float_pub.array.data[12]=gyro.quat.w();//w

  float_pub.array.data[13]=body_vel_x;//直進速度
  float_pub.array.data[14]=odom.vec.yaw;//yaw
  //imu mag
  float_pub.array.data[15]=gyro.mag.x();//x
  float_pub.array.data[16]=gyro.mag.y();//y
  float_pub.array.data[17]=gyro.mag.z();//z
  //2d odom
  float_pub.array.data[18]=odom.vec2d.x;//x
  float_pub.array.data[19]=odom.vec2d.y;//y
  float_pub.publish();
  //quat
  //publishするデータの準備
  //TF map->base_link
  /*
  float_pub_array.data[0]=odom.vec.y;//x
  float_pub_array.data[1]=odom.vec.x;//y
  float_pub_array.data[2]=odom.vec.yaw;//yaw
  //速度の送信
  float_pub_array.data[3]=body_vel_x;//直進速度
  //絶対方位
  float_pub_array.data[4]=gyro.magyaw();//magyaw
  */
  //データのpublish
  //float_pub.publish(&float_pub_array);
  //int_pub.publish(&int_pub_array);
  nh.spinOnce();
  //cout<<gyro.getPitch()<<endl;
  //cout<<float_pub_array.data[0]<<float_pub_array.data[1]<<float_pub_array.data[2]<<endl;
   //cout<<r_rot<<","<<target_vel.y+0.5*wheel_width/1000.0*target_vel.yaw<<","<<gyro.rad()<<endl;
   //cout<<"X="<<pos_x<<"Y="<<pos_y<<"YAW="<<angle_rad-angle_offset<<endl;

}
