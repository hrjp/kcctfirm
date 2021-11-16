#ifndef ENCODER3_H
#define ENCODER3_H

#include "Arduino.h"
#include "config.h"

// エンコーダ値
typedef struct {
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoder3_t;

class ENCODER3 {

    private:

        static Encoder3_t encoder3;
        
        static void update(){
            encoder3.signalA=digitalRead(Encoder3_pinA);
            encoder3.signalB=digitalRead(Encoder3_pinB);
 
            if((encoder3.signalA==HIGH&&encoder3.signalB==LOW&&encoder3.oldsigA==LOW&&encoder3.oldsigB==LOW) || (encoder3.signalA==HIGH&&encoder3.signalB==HIGH&&encoder3.oldsigA==HIGH&&encoder3.oldsigB==LOW) || (encoder3.signalA==LOW&&encoder3.signalB==HIGH&&encoder3.oldsigA==HIGH&&encoder3.oldsigB==HIGH) || (encoder3.signalA==LOW&&encoder3.signalB==LOW&&encoder3.oldsigA==LOW&&encoder3.oldsigB==HIGH)){
                encoder3._pulse++;
            }
            else if((encoder3.signalA==LOW&&encoder3.signalB==HIGH&&encoder3.oldsigA==LOW&&encoder3.oldsigB==LOW) || (encoder3.signalA==HIGH&&encoder3.signalB==HIGH&&encoder3.oldsigA==LOW&&encoder3.oldsigB==HIGH) || (encoder3.signalA==HIGH&&encoder3.signalB==LOW&&encoder3.oldsigA==HIGH&&encoder3.oldsigB==HIGH) || (encoder3.signalA==LOW&&encoder3.signalB==LOW&&encoder3.oldsigA==HIGH&&encoder3.oldsigB==LOW)){
                encoder3._pulse--;
            }
            encoder3.oldsigA=encoder3.signalA;
            encoder3.oldsigB=encoder3.signalB;
        }
        
        static void interrupt_200ms(){
            encoder3.ave_pulse = encoder3._pulse - encoder3.old_pulse;
            encoder3._rpm = ((float)encoder3.ave_pulse / encoder3.cyclecount) * 5.0 * 60.0;
            encoder3.old_pulse = encoder3._pulse;
        }
    
    public:
        
        ENCODER3() {};

        void set(int _cyclecount) {
            encoder3.cyclecount = _cyclecount;
            attachInterrupt(Encoder3_pinA, update, CHANGE);
            attachInterrupt(Encoder3_pinB, update, CHANGE);
            encoder3.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoder3._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoder3._rpm;
            return rpm;
        }
};

#endif
