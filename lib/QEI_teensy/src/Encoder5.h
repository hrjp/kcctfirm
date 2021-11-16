#ifndef ENCODER5_H
#define ENCODER5_H

#include "Arduino.h"
#include "config.h"

// エンコーダ値
typedef struct {
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoder5_t;

class ENCODER5 {

    private:

        static Encoder5_t encoder5;
        
        static void update(){
            encoder5.signalA=digitalRead(Encoder5_pinA);
            encoder5.signalB=digitalRead(Encoder5_pinB);
 
            if((encoder5.signalA==HIGH&&encoder5.signalB==LOW&&encoder5.oldsigA==LOW&&encoder5.oldsigB==LOW) || (encoder5.signalA==HIGH&&encoder5.signalB==HIGH&&encoder5.oldsigA==HIGH&&encoder5.oldsigB==LOW) || (encoder5.signalA==LOW&&encoder5.signalB==HIGH&&encoder5.oldsigA==HIGH&&encoder5.oldsigB==HIGH) || (encoder5.signalA==LOW&&encoder5.signalB==LOW&&encoder5.oldsigA==LOW&&encoder5.oldsigB==HIGH)){
                encoder5._pulse++;
            }
            else if((encoder5.signalA==LOW&&encoder5.signalB==HIGH&&encoder5.oldsigA==LOW&&encoder5.oldsigB==LOW) || (encoder5.signalA==HIGH&&encoder5.signalB==HIGH&&encoder5.oldsigA==LOW&&encoder5.oldsigB==HIGH) || (encoder5.signalA==HIGH&&encoder5.signalB==LOW&&encoder5.oldsigA==HIGH&&encoder5.oldsigB==HIGH) || (encoder5.signalA==LOW&&encoder5.signalB==LOW&&encoder5.oldsigA==HIGH&&encoder5.oldsigB==LOW)){
                encoder5._pulse--;
            }
            encoder5.oldsigA=encoder5.signalA;
            encoder5.oldsigB=encoder5.signalB;
        }
        
        static void interrupt_200ms(){
            encoder5.ave_pulse = encoder5._pulse - encoder5.old_pulse;
            encoder5._rpm = ((float)encoder5.ave_pulse / encoder5.cyclecount) * 5.0 * 60.0;
            encoder5.old_pulse = encoder5._pulse;
        }
    
    public:
        
        ENCODER5() {};

        void set(int _cyclecount) {
            encoder5.cyclecount = _cyclecount;
            attachInterrupt(Encoder5_pinA, update, CHANGE);
            attachInterrupt(Encoder5_pinB, update, CHANGE);
            encoder5.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoder5._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoder5._rpm;
            return rpm;
        }
};

#endif
