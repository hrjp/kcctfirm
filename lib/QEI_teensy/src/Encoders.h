#ifndef ENCODERS_H
#define ENCODERS_H

#include "Arduino.h"
#include "Encoder1.h"
#include "Encoder2.h"
#include "Encoder3.h"
#include "Encoder4.h"
#include "Encoder5.h"
#include "Encoder6.h"

#if defined(__MK64FX512__)
#elif defined(__MK66FX1M0__)
#else
  #error serect Teensy3.5 or Teensy 3.6
#endif

#ifdef TEMPLATE_USE
#define TEMPLATE_USE_ENCODER
#else
#define STRUCT_USE_ENCODER
#endif


#ifdef STRUCT_USE_ENCODER
// エンコーダ値
typedef struct {
    int pinA, pinB;
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoders_t;

class ENCODERS {

    private:

        static Encoders_t encoders;
        
        static void update(){
            encoders.signalA=digitalRead(encoders.pinA);
            encoders.signalB=digitalRead(encoders.pinB);
 
            if((encoders.signalA==HIGH&&encoders.signalB==LOW&&encoders.oldsigA==LOW&&encoders.oldsigB==LOW) || (encoders.signalA==HIGH&&encoders.signalB==HIGH&&encoders.oldsigA==HIGH&&encoders.oldsigB==LOW) || (encoders.signalA==LOW&&encoders.signalB==HIGH&&encoders.oldsigA==HIGH&&encoders.oldsigB==HIGH) || (encoders.signalA==LOW&&encoders.signalB==LOW&&encoders.oldsigA==LOW&&encoders.oldsigB==HIGH)){
                encoders._pulse++;
            }
            else if((encoders.signalA==LOW&&encoders.signalB==HIGH&&encoders.oldsigA==LOW&&encoders.oldsigB==LOW) || (encoders.signalA==HIGH&&encoders.signalB==HIGH&&encoders.oldsigA==LOW&&encoders.oldsigB==HIGH) || (encoders.signalA==HIGH&&encoders.signalB==LOW&&encoders.oldsigA==HIGH&&encoders.oldsigB==HIGH) || (encoders.signalA==LOW&&encoders.signalB==LOW&&encoders.oldsigA==HIGH&&encoders.oldsigB==LOW)){
                encoders._pulse--;
            }
            encoders.oldsigA=encoders.signalA;
            encoders.oldsigB=encoders.signalB;
        }
        
        static void interrupt_200ms(){
            encoders.ave_pulse = encoders._pulse - encoders.old_pulse;
            encoders._rpm = ((float)encoders.ave_pulse / encoders.cyclecount) * 5.0 * 60.0;
            encoders.old_pulse = encoders._pulse;
        }
    
    public:

        ENCODER1 Encoder1;
        ENCODER2 Encoder2;
        ENCODER3 Encoder3;
        ENCODER4 Encoder4;
        ENCODER5 Encoder5;
        ENCODER6 Encoder6;
        
        
        ENCODERS(int _pinA, int _pinB) {
            encoders.pinA = _pinA;
            encoders.pinB = _pinB;
        };

        void set(int _cyclecount) {
            Serial.println("STRUCT_MODE");
            encoders.cyclecount = _cyclecount;
            attachInterrupt(encoders.pinA, update, CHANGE);
            attachInterrupt(encoders.pinB, update, CHANGE);
            encoders.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoders._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoders._rpm;
            return rpm;
        }
};
#endif


#ifdef TEMPLATE_USE_ENCODER
template <uint16_t pin, uint16_t pin1>
class ENCODERS {

    public:

        static void set(int cycle) {
            cyclecount = cycle;
            static ENCODERS<pin, pin1> instance;
            instance._set();
        }
        
  
        static float read_rpm() {
            static ENCODERS<pin, pin1> instance;
            float rpm = instance._read_rpm();
            return rpm;
        }
        

        static int read_pulse() {
            static ENCODERS<pin, pin1> instance;
            int pulse = instance._read_pulse();
            return pulse;
        }
        
        
    private:
    
        IntervalTimer Interrupt_200ms;
 
        // エンコーダ値
        static volatile int _pulse, ave_pulse, old_pulse;
        static volatile int signalA, signalB, oldsignalA, oldsignalB, cyclecount;
        static volatile float _rpm;


        void _set() {
            pinMode(pin, INPUT);
            pinMode(pin1, INPUT);
            attachInterrupt(pin, doCounter, CHANGE);
            attachInterrupt(pin1, doCounter, CHANGE);
            Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

  
        static void doCounter(){
            signalA=digitalRead(pin);
            signalB=digitalRead(pin1);
 
            if((signalA==HIGH&&signalB==LOW&&oldsignalA==LOW&&oldsignalB==LOW) || (signalA==HIGH&&signalB==HIGH&&oldsignalA==HIGH&&oldsignalB==LOW) || (signalA==LOW&&signalB==HIGH&&oldsignalA==HIGH&&oldsignalB==HIGH) || (signalA==LOW&&signalB==LOW&&oldsignalA==LOW&&oldsignalB==HIGH)){
                _pulse++;
            }
            else if((signalA==LOW&&signalB==HIGH&&oldsignalA==LOW&&oldsignalB==LOW) || (signalA==HIGH&&signalB==HIGH&&oldsignalA==LOW&&oldsignalB==HIGH) || (signalA==HIGH&&signalB==LOW&&oldsignalA==HIGH&&oldsignalB==HIGH) || (signalA==LOW&&signalB==LOW&&oldsignalA==HIGH&&oldsignalB==LOW)){
                _pulse--;
            }
            oldsignalA=signalA;
            oldsignalB=signalB;
        }


        static void interrupt_200ms(){
            ave_pulse = _pulse - old_pulse;
            _rpm = ((float)ave_pulse / cyclecount) * 5.0 * 60.0;
            old_pulse = _pulse;
        }


        int _read_pulse(){
            return _pulse;
        }


        float _read_rpm() {
            return _rpm;
        }


        ENCODERS() {}

};


template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::_pulse = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::ave_pulse = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::old_pulse = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::signalA = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::signalB = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::oldsignalA = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::oldsignalB = 0;
template <uint16_t pin, uint16_t pin1>
volatile int ENCODERS<pin, pin1>::cyclecount = 0;
template <uint16_t pin, uint16_t pin1>
volatile float ENCODERS<pin, pin1>::_rpm = 0;
#endif


#endif
