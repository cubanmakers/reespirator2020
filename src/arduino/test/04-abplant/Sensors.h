#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <stdint.h>
#include "src/Adafruit_BME280/Adafruit_BME280.h"
#include "defaults.h"
#ifdef ENABLED_SENSOR_VOLUME_SFM3300
#include "src/SFM3200/sfm3000wedo.h"
#endif

#define SENSORS_MAX_ERRORS 5

#if ENABLED_SENSOR_VOLUME_SFM3300
#define SFM3300_OFFSET 32768
#define SFM3300_SCALE   120
#endif

enum SensorState {
    SensorStateOK = 0,
    SensorStateFailed = 1
};

typedef struct {
    SensorState state;
    float pressure1;
    float pressure2;
} SensorPressureValues_t;

typedef struct {
    SensorState state;
    short volume; // ml
} SensorVolumeValue_t;

class Sensors
{
    public:
    Sensors();
    unsigned int begin(void);
    void readPressure();
    SensorPressureValues_t getPressure(); 
    SensorVolumeValue_t getVolume();
#if ENABLED_SENSOR_VOLUME
    void readVolume(void);
    void resetVolumeIntegrator(void);
    float getFlux(void);
#endif
    private:
    void _init(void);
    Adafruit_BME280 _pres1Sensor;
    Adafruit_BME280 _pres2Sensor;
#if ENABLED_SENSOR_VOLUME_SFM3300
    SFM3000wedo* _sfm3000;
#endif
    float _pressure1;
    float _pressure2;
    SensorState _state;
    byte _errorCounter;
#if ENABLED_SENSOR_VOLUME
    float _volume_ml;
    float _flux;
    unsigned long _lastReadFlow;
#endif


};

#endif