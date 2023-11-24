#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

struct SensorData {

  float massConcentrationPm1p0;
  float massConcentrationPm2p5;
  float massConcentrationPm4p0;
  float massConcentrationPm10p0;
  float ambientHumidity;
  float ambientTemperature;
  float vocIndex;
  float noxIndex;
  bool valid_data;
  
};

#endif
