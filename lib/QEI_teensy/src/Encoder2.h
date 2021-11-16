#ifndef ENCODER2_H
#define ENCODER2_H

#include "Arduino.h"
#include "config.h"

// エンコーダ値
typedef struct {
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoder2_t;

class ENCODER2 {

    private:

        static Encoder2_t encoder2;
        
        static void update(){
            encoder2.signalA=digitalRead(Encoder2_pinA);
            encoder2.signalB=digitalRead(Encoder2_pinB);
 
            if((encoder2.signalA==HIGH&&encoder2.signalB==LOW&&encoder2.oldsigA==LOW&&encoder2.oldsigB==LOW) || (encoder2.signalA==HIGH&&encoder2.signalB==HIGH&&encoder2.oldsigA==HIGH&&encoder2.oldsigB==LOW) || (encoder2.signalA==LOW&&encoder2.signalB==HIGH&&encoder2.oldsigA==HIGH&&encoder2.oldsigB==HIGH) || (encoder2.signalA==LOW&&encoder2.signalB==LOW&&encoder2.oldsigA==LOW&&encoder2.oldsigB==HIGH)){
                encoder2._pulse++;
            }
            else if((encoder2.signalA==LOW&&encoder2.signalB==HIGH&&encoder2.oldsigA==LOW&&encoder2.oldsigB==LOW) || (encoder2.signalA==HIGH&&encoder2.signalB==HIGH&&encoder2.oldsigA==LOW&&encoder2.oldsigB==HIGH) || (encoder2.signalA==HIGH&&encoder2.signalB==LOW&&encoder2.oldsigA==HIGH&&encoder2.oldsigB==HIGH) || (encoder2.signalA==LOW&&encoder2.signalB==LOW&&encoder2.oldsigA==HIGH&&encoder2.oldsigB==LOW)){
                encoder2._pulse--;
            }
            encoder2.oldsigA=encoder2.signalA;
            encoder2.oldsigB=encoder2.signalB;
        }
        
        static void interrupt_200ms(){
            encoder2.ave_pulse = encoder2._pulse - encoder2.old_pulse;
            encoder2._rpm = ((float)encoder2.ave_pulse / encoder2.cyclecount) * 5.0 * 60.0;
            encoder2.old_pulse = encoder2._pulse;
        }
    
    public:
        
        ENCODER2() {};

        void set(int _cyclecount) {
            encoder2.cyclecount = _cyclecount;
            attachInterrupt(Encoder2_pinA, update, CHANGE);
            attachInterrupt(Encoder2_pinB, update, CHANGE);
            encoder2.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoder2._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoder2._rpm;
            return rpm;
        }
};

#endif
