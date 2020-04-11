#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <stdint.h>
#include "defaults.h"
#ifdef ENABLED_SENSOR_VOLUME_SFM3300
#include "src/SFM3200/sfm3000wedo.h"
#endif
#include "src/Adafruit_BME280/Adafruit_BME280.h"
#include "src/Honeywell_ABP/Honeywell_ABP.h"

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
    uint8_t minPressure;
    uint8_t maxPressure;
} SensorLastPressure_t;

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
    void readPressure(void);
    void rebootVolumeSensor(void);
    SensorLastPressure_t getLastPressure(void);
    SensorPressureValues_t getRelativePressureInPascals(void);
    SensorPressureValues_t getAbsolutePressureInPascals(void);
    SensorPressureValues_t getAbsolutePressureInCmH2O(void);
    SensorPressureValues_t getRelativePressureInCmH2O(void);
    SensorVolumeValue_t getVolume(void);
    void saveVolume(void);
    void getOffsetBetweenPressureSensors(int samples = 100);
    bool stalledVolumeSensor();
#if ENABLED_SENSOR_VOLUME
    void readVolume(void);
    void resetPressures(void);
    void resetVolumeIntegrator(void);
    float getFlow(void);
#endif
    private:
    void _init(void);
    Adafruit_BME280 _pres1Sensor;
    Adafruit_BME280 _pres2Sensor;
#if ENABLED_SENSOR_VOLUME_SFM3300
    SFM3000wedo* _sfm3000;
#endif
    uint8_t _minPressure;
    uint8_t _maxPressure;
    float _pressure1;
    float _pressure2;
    float _pressureSensorsOffset = 0.0;
    SensorState _state;
    SensorState _volumeState;
    byte _errorCounter;
    volatile uint8_t _lastMinPressure;
    volatile uint8_t _lastMaxPressure;
#if ENABLED_SENSOR_VOLUME
    float _volume_ml;
    float _flow;
    volatile float _lastVolume;
    unsigned long _lastReadFlow;
    unsigned int _flowRepetitionCounter = 0;

#endif


};

#endif