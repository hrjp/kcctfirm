#ifndef ENCODER4_H
#define ENCODER4_H

#include "Arduino.h"
#include "config.h"

// エンコーダ値
typedef struct {
    volatile int _pulse, ave_pulse, old_pulse;
    volatile int signalA, signalB, oldsigA, oldsigB, cyclecount;
    volatile float _rpm;
    IntervalTimer Interrupt_200ms;
}Encoder4_t;

class ENCODER4 {

    private:

        static Encoder4_t encoder4;
        
        static void update(){
            encoder4.signalA=digitalRead(Encoder4_pinA);
            encoder4.signalB=digitalRead(Encoder4_pinB);
 
            if((encoder4.signalA==HIGH&&encoder4.signalB==LOW&&encoder4.oldsigA==LOW&&encoder4.oldsigB==LOW) || (encoder4.signalA==HIGH&&encoder4.signalB==HIGH&&encoder4.oldsigA==HIGH&&encoder4.oldsigB==LOW) || (encoder4.signalA==LOW&&encoder4.signalB==HIGH&&encoder4.oldsigA==HIGH&&encoder4.oldsigB==HIGH) || (encoder4.signalA==LOW&&encoder4.signalB==LOW&&encoder4.oldsigA==LOW&&encoder4.oldsigB==HIGH)){
                encoder4._pulse++;
            }
            else if((encoder4.signalA==LOW&&encoder4.signalB==HIGH&&encoder4.oldsigA==LOW&&encoder4.oldsigB==LOW) || (encoder4.signalA==HIGH&&encoder4.signalB==HIGH&&encoder4.oldsigA==LOW&&encoder4.oldsigB==HIGH) || (encoder4.signalA==HIGH&&encoder4.signalB==LOW&&encoder4.oldsigA==HIGH&&encoder4.oldsigB==HIGH) || (encoder4.signalA==LOW&&encoder4.signalB==LOW&&encoder4.oldsigA==HIGH&&encoder4.oldsigB==LOW)){
                encoder4._pulse--;
            }
            encoder4.oldsigA=encoder4.signalA;
            encoder4.oldsigB=encoder4.signalB;
        }
        
        static void interrupt_200ms(){
            encoder4.ave_pulse = encoder4._pulse - encoder4.old_pulse;
            encoder4._rpm = ((float)encoder4.ave_pulse / encoder4.cyclecount) * 5.0 * 60.0;
            encoder4.old_pulse = encoder4._pulse;
        }
    
    public:
        
        ENCODER4() {};

        void set(int _cyclecount) {
            encoder4.cyclecount = _cyclecount;
            attachInterrupt(Encoder4_pinA, update, CHANGE);
            attachInterrupt(Encoder4_pinB, update, CHANGE);
            encoder4.Interrupt_200ms.begin(interrupt_200ms, 200000);
        }

        inline int32_t read_pulse(){
            int32_t positions = encoder4._pulse;
            return positions;
        }

        inline float read_rpm() {
            float rpm = encoder4._rpm;
            return rpm;
        }
};

#endif
