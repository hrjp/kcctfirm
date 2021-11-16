#ifndef ENCODER1_H
#define ENCODER1_H

#include "Arduino.h"
#include "config.h"

// エンコーダ値
typedef struct {
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoder1_t;

class ENCODER1 {

    private:

        static Encoder1_t encoder1;
        
        static void update(){
            encoder1.signalA=digitalRead(Encoder1_pinA);
            encoder1.signalB=digitalRead(Encoder1_pinB);
 
            if((encoder1.signalA==HIGH&&encoder1.signalB==LOW&&encoder1.oldsigA==LOW&&encoder1.oldsigB==LOW) || (encoder1.signalA==HIGH&&encoder1.signalB==HIGH&&encoder1.oldsigA==HIGH&&encoder1.oldsigB==LOW) || (encoder1.signalA==LOW&&encoder1.signalB==HIGH&&encoder1.oldsigA==HIGH&&encoder1.oldsigB==HIGH) || (encoder1.signalA==LOW&&encoder1.signalB==LOW&&encoder1.oldsigA==LOW&&encoder1.oldsigB==HIGH)){
                encoder1._pulse++;
            }
            else if((encoder1.signalA==LOW&&encoder1.signalB==HIGH&&encoder1.oldsigA==LOW&&encoder1.oldsigB==LOW) || (encoder1.signalA==HIGH&&encoder1.signalB==HIGH&&encoder1.oldsigA==LOW&&encoder1.oldsigB==HIGH) || (encoder1.signalA==HIGH&&encoder1.signalB==LOW&&encoder1.oldsigA==HIGH&&encoder1.oldsigB==HIGH) || (encoder1.signalA==LOW&&encoder1.signalB==LOW&&encoder1.oldsigA==HIGH&&encoder1.oldsigB==LOW)){
                encoder1._pulse--;
            }
            encoder1.oldsigA=encoder1.signalA;
            encoder1.oldsigB=encoder1.signalB;
        }
        
        static void interrupt_200ms(){
            encoder1.ave_pulse = encoder1._pulse - encoder1.old_pulse;
            encoder1._rpm = ((float)encoder1.ave_pulse / encoder1.cyclecount) * 5.0 * 60.0;
            encoder1.old_pulse = encoder1._pulse;
        }
    
    public:
        
        ENCODER1() {};

        void set(int _cyclecount) {
            encoder1.cyclecount = _cyclecount;
            attachInterrupt(Encoder1_pinA, update, CHANGE);
            attachInterrupt(Encoder1_pinB, update, CHANGE);
            encoder1.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoder1._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoder1._rpm;
            return rpm;
        }
};

#endif
