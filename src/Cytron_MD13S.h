/*
 * Cytron_MD13S.h
 * 2019-04-27
 */


#ifndef CYTRON_MD13S_H
#define CYTRON_MD13S_H
#include <Arduino.h>

class MD13S {
   public:

      MD13S(int _PWM_PIN, int _invert_PIN);
   
      //void set();
   
      void writeMicroseconds(int _pulse);
      
   private:
      int PWM_PIN, invert_PIN;
      int pulse;
};

#endif
