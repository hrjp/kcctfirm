/*
  Copyright (c) 2012 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <Arduino.h>
#include "Cytron_MD13S.h"

MD13S::MD13S(int _PWM_PIN, int _invert_PIN){
    PWM_PIN = _PWM_PIN;
    invert_PIN = _invert_PIN;
    analogWriteFrequency(PWM_PIN, 20000);
    pinMode(PWM_PIN, OUTPUT);
    pinMode(invert_PIN, OUTPUT);
    
    digitalWrite(invert_PIN, LOW);
    analogWrite(PWM_PIN,LOW);
}

/*
void MD13S::set(){
    pinMode(PWM_PIN, OUTPUT);
    pinMode(invert_PIN, OUTPUT);
}*/

// Teensy用に周波数変更の関数追加予定

void MD13S::writeMicroseconds(int _pulse){
    pulse = _pulse;
    if(pulse < 1475){
        pulse = pulse < 1000 ? 1000 : pulse;
        digitalWrite(invert_PIN, LOW);
        analogWrite(PWM_PIN, map(pulse, 1475, 1000, 1, 225));
    }
    else if(pulse > 1525){
        pulse = pulse > 2000 ? 2000 : pulse;
        digitalWrite(invert_PIN, HIGH);
        analogWrite(PWM_PIN, map(pulse, 1525, 2000, 1, 225));
    }
    else{
        analogWrite(PWM_PIN, 0);
    }
}
