#pragma once
#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS


class GPS{
  public:
  GPS();
  void set();
  void update();
  long latitude,longitude;//[degrees * 10^-7]
  long altitude;//[mm]
  private:
  SFE_UBLOX_GPS myGPS;
  long lastTime = 0;
};

GPS::GPS():myGPS(){}

void GPS::set(){
  if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
}

void GPS::update(){
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    latitude = myGPS.getLatitude();
    longitude = myGPS.getLongitude();
    altitude = myGPS.getAltitude();
  }
}
