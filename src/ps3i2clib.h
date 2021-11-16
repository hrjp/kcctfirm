#ifndef PS3I2CLIB_H
#define PS3I2CLIB_H
#include<Wire.h>
class PS3I2C{
public:

void set();
void set(int slave_ad);
PS3I2C();
PS3I2C(int slave_ad);

void update();

bool connect();

int A_Lx();
int A_Ly();
int A_Rx();
int A_Ry();
int A_L2();
int A_R2();

bool P_Circle();
bool P_Triangle();
bool P_Square();
bool P_Cross();
bool P_Up();
bool P_Down();
bool P_Right();
bool P_Left();
bool P_R1();
bool P_L1();
bool P_R3();
bool P_L3();
bool P_Start();
bool P_Select();
bool P_Ps();

bool C_Circle();
bool C_Triangle();
bool C_Square();
bool C_Cross();
bool C_Up();
bool C_Down();
bool C_Right();
bool C_Left();
bool C_R1();
bool C_L1();
bool C_R3();
bool C_L3();
bool C_Start();
bool C_Select();
bool C_Ps();

private:
int slave_adrress=0x73;
byte rdata[10];
byte p_data[20];
byte c_data[20];
byte pre_data[20];

};







void PS3I2C::set(int slave_ad){
    slave_adrress=slave_ad;
    Wire.begin();
}
void PS3I2C::set(){
    set(slave_adrress);
}
PS3I2C::PS3I2C(int slave_ad){
    slave_adrress=slave_ad;
    Wire.begin();
    Wire.setSDA(34);
  Wire.setSCL(33);
}
PS3I2C::PS3I2C(){}

void PS3I2C::update(){

    Wire.requestFrom(slave_adrress, 8);
    for(int i=0;i<8;i++){
        rdata[i]=Wire.read();
    }
    p_data[0]=bitRead(rdata[6],0);
    p_data[1]=bitRead(rdata[6],1);
    p_data[2]=bitRead(rdata[6],2);
    p_data[3]=bitRead(rdata[6],3);
    p_data[4]=bitRead(rdata[6],4);
    p_data[5]=bitRead(rdata[6],5);
    p_data[6]=bitRead(rdata[6],6);
    p_data[7]=bitRead(rdata[6],7);
    p_data[8]=bitRead(rdata[7],0);
    p_data[9]=bitRead(rdata[7],1);
    p_data[10]=bitRead(rdata[7],2);
    p_data[11]=bitRead(rdata[7],3);
    p_data[12]=bitRead(rdata[7],4);
    p_data[13]=bitRead(rdata[7],5);
    p_data[14]=bitRead(rdata[7],6);
    p_data[15]=bitRead(rdata[7],7);

    for(int i=0;i<16;i++){
        if(pre_data[i]==false && p_data[i]==true){
            c_data[i]=true;
        }
        else{
            c_data[i]=false;
        }
        pre_data[i]=p_data[i];
    }

}

bool PS3I2C::connect(){return p_data[15];}
int PS3I2C::A_Lx(){return rdata[1];}
int PS3I2C::A_Ly(){return rdata[0];}
int PS3I2C::A_Rx(){return rdata[3];}
int PS3I2C::A_Ry(){return rdata[2];}
int PS3I2C::A_L2(){return rdata[4];}
int PS3I2C::A_R2(){return rdata[5];}

bool PS3I2C::P_Circle(){return p_data[0];}
bool PS3I2C::P_Triangle(){return p_data[1];}
bool PS3I2C::P_Square(){return p_data[2];}
bool PS3I2C::P_Cross(){return p_data[3];}
bool PS3I2C::P_Up(){return p_data[4];}
bool PS3I2C::P_Down(){return p_data[6];}
bool PS3I2C::P_Right(){return p_data[5];}
bool PS3I2C::P_Left(){return p_data[7];}
bool PS3I2C::P_R1(){return p_data[9];}
bool PS3I2C::P_L1(){return p_data[8];}
bool PS3I2C::P_R3(){return p_data[11];}
bool PS3I2C::P_L3(){return p_data[10];}
bool PS3I2C::P_Start(){return p_data[12];}
bool PS3I2C::P_Select(){return p_data[13];}
bool PS3I2C::P_Ps(){return p_data[14];}

bool PS3I2C::C_Circle(){return c_data[0];}
bool PS3I2C::C_Triangle(){return c_data[1];}
bool PS3I2C::C_Square(){return c_data[2];}
bool PS3I2C::C_Cross(){return c_data[3];}
bool PS3I2C::C_Up(){return c_data[4];}
bool PS3I2C::C_Down(){return c_data[6];}
bool PS3I2C::C_Right(){return c_data[5];}
bool PS3I2C::C_Left(){return c_data[7];}
bool PS3I2C::C_R1(){return c_data[9];}
bool PS3I2C::C_L1(){return c_data[8];}
bool PS3I2C::C_R3(){return c_data[11];}
bool PS3I2C::C_L3(){return c_data[10];}
bool PS3I2C::C_Start(){return c_data[12];}
bool PS3I2C::C_Select(){return c_data[13];}
bool PS3I2C::C_Ps(){return c_data[14];}

#endif
