#include <Cytron_MD13S.h>

MD13S motor1(11, 12); //(PWM_PIN,invert_PIN)

void setup() {
  motor1.set();
}

void loop() {
  motor1.writeMicroseconds(1500); // stop
  delay(1000);
  motor1.writeMicroseconds(2000); // normal rotation
  delay(1000);
  motor1.writeMicroseconds(1500); // stop
  delay(1000);
  motor1.writeMicroseconds(1000); // reverse rotation
  delay(1000);
}
