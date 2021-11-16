#ifndef ENCODER6_H
#define ENCODER6_H

#include "Arduino.h"
#include "config.h"

// エンコーダ値
typedef struct {
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoder6_t;

class ENCODER6 {

    private:

        static Encoder6_t encoder6;
        
        static void update(){
            encoder6.signalA=digitalRead(Encoder6_pinA);
            encoder6.signalB=digitalRead(Encoder6_pinB);
 
            if((encoder6.signalA==HIGH&&encoder6.signalB==LOW&&encoder6.oldsigA==LOW&&encoder6.oldsigB==LOW) || (encoder6.signalA==HIGH&&encoder6.signalB==HIGH&&encoder6.oldsigA==HIGH&&encoder6.oldsigB==LOW) || (encoder6.signalA==LOW&&encoder6.signalB==HIGH&&encoder6.oldsigA==HIGH&&encoder6.oldsigB==HIGH) || (encoder6.signalA==LOW&&encoder6.signalB==LOW&&encoder6.oldsigA==LOW&&encoder6.oldsigB==HIGH)){
                encoder6._pulse++;
            }
            else if((encoder6.signalA==LOW&&encoder6.signalB==HIGH&&encoder6.oldsigA==LOW&&encoder6.oldsigB==LOW) || (encoder6.signalA==HIGH&&encoder6.signalB==HIGH&&encoder6.oldsigA==LOW&&encoder6.oldsigB==HIGH) || (encoder6.signalA==HIGH&&encoder6.signalB==LOW&&encoder6.oldsigA==HIGH&&encoder6.oldsigB==HIGH) || (encoder6.signalA==LOW&&encoder6.signalB==LOW&&encoder6.oldsigA==HIGH&&encoder6.oldsigB==LOW)){
                encoder6._pulse--;
            }
            encoder6.oldsigA=encoder6.signalA;
            encoder6.oldsigB=encoder6.signalB;
        }
        
        static void interrupt_200ms(){
            encoder6.ave_pulse = encoder6._pulse - encoder6.old_pulse;
            encoder6._rpm = ((float)encoder6.ave_pulse / encoder6.cyclecount) * 5.0 * 60.0;
            encoder6.old_pulse = encoder6._pulse;
        }
    
    public:
        
        ENCODER6() {};

        void set(int _cyclecount) {
            encoder6.cyclecount = _cyclecount;
            attachInterrupt(Encoder6_pinA, update, CHANGE);
            attachInterrupt(Encoder6_pinB, update, CHANGE);
            encoder6.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoder6._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoder6._rpm;
            return rpm;
        }
};

#endif
