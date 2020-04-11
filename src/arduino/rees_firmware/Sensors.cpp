/**
 * Sensors reading module
 */
#include "Sensors.h"

static Honeywell_ABP* abp;

unsigned int Sensors::begin(void) {
    // Arrancar sensores de presion 1 y 2
#if 0

    if(!_pres1Sensor.begin()) {
        return 1;
    }
    if(!_pres2Sensor.begin()) {
        return 2;
    }


    /* Default settings from datasheet. */  //TODO: valorar SAMPLING_NONE, lecturas mas rapidas?
    // Ver ejemplos: https://github.com/adafruit/Adafruit_BME280_Library/blob/master/examples/advancedsettings/advancedsettings.ino
    _pres1Sensor.setSampling(Adafruit_BME280::MODE_NORMAL,     /* Operating Mode. */
                      Adafruit_BME280::SAMPLING_X1,     /* Temp. oversampling */
                      Adafruit_BME280::SAMPLING_X4,    /* Pressure oversampling */
                      Adafruit_BME280::SAMPLING_NONE,   /* humidity sampling */
                      Adafruit_BME280::FILTER_X4,      /* Filtering. */
                      Adafruit_BME280::STANDBY_MS_0_5); /* Standby time. */
    _pres2Sensor.setSampling(Adafruit_BME280::MODE_NORMAL,     /* Operating Mode. */
                      Adafruit_BME280::SAMPLING_X1,     /* Temp. oversampling */
                      Adafruit_BME280::SAMPLING_X4,    /* Pressure oversampling */
                      Adafruit_BME280::SAMPLING_NONE,   /* humidity sampling */
                      Adafruit_BME280::FILTER_X4,      /* Filtering. */
                      Adafruit_BME280::STANDBY_MS_0_5); /* Standby time. */
#endif
    return 0;
}

Sensors::Sensors(void) {
    _init();
}


void Sensors::_init () {
    abp = new Honeywell_ABP(
  0x28,   // I2C address
  0,      // minimum pressure
  70.307,      // maximum pressure
  "mbar"   // pressure unit
);
#if 0
    Adafruit_BME280 bmp1(
    PIN_BME_CS1,
    PIN_BME_MOSI,
    PIN_BME_MISO,
    PIN_BME_SCK
    );

    Adafruit_BME280 bmp2(
    PIN_BME_CS2,
    PIN_BME_MOSI,
    PIN_BME_MISO,
    PIN_BME_SCK
    );

    _pres1Sensor = bmp1;
    _pres2Sensor = bmp2;
        #endif
        Wire.begin();

    _errorCounter = 0;
    _state = SensorStateFailed;

#if ENABLED_SENSOR_VOLUME_SFM3300
    pinMode(20, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);
    _sfm3000 = new SFM3000wedo(64);
    _sfm3000->init();
#endif
#if ENABLED_SENSOR_VOLUME
    resetVolumeIntegrator();
#endif
}

void Sensors::rebootVolumeSensor() {
    _sfm3000->reset();
    _sfm3000->init();
    resetVolumeIntegrator();
}

bool Sensors::stalledVolumeSensor()
{
    if (_flowRepetitionCounter > 10)
    {
        _flowRepetitionCounter = 0;
        return true;
    }
    return false;
}


void Sensors::readPressure() {
    float pres1, pres2;
    // Acquire sensors data
    abp->update();
    pres1 = abp->pressure();
    _pressure1 = pres1;
    if (_minPressure > _pressure1) {
        _minPressure = _pressure1;
    }
    if (_maxPressure < _pressure1) {
        _maxPressure = _pressure1;
    }
    #if 0
    pres1 = _pres1Sensor.readPressure(); // Pa
    pres2 = _pres2Sensor.readPressure(); // Pa

    if (pres1 == 0.0 || pres2 == 0.0) {

        if (_errorCounter > SENSORS_MAX_ERRORS) {
            _state = SensorStateFailed;
            //TODO do something?
        } else {
            _errorCounter++;
        }

    } else {
        _state = SensorStateOK;
        _errorCounter = 0;
        _pressure1 = pres1;
        _pressure2 = pres2;
    }
    #endif
}

/**
 * @brief Get absolute pressure in pascals.
 *
 * @return SensorValues_t - pressure values
 */
SensorPressureValues_t Sensors::getAbsolutePressureInPascals() {
    SensorPressureValues_t values;
    values.state = _state;
    values.pressure1 = _pressure1;
    values.pressure2 = _pressure2 + _pressureSensorsOffset;
    return values;
}

/**
 * @brief Get relative pressure in pascals.
 *
 * @return SensorValues_t - pressure values
 */
SensorPressureValues_t Sensors::getRelativePressureInPascals() {
    SensorPressureValues_t values = getAbsolutePressureInPascals();
    values.pressure1 = 0;
    values.pressure2 = values.pressure2 - values.pressure1;
    return values;
}

/**
 * @brief Get absolute pressure in H2O cm.
 *
 * @return SensorValues_t - pressure values
 */
SensorPressureValues_t Sensors::getAbsolutePressureInCmH2O() {
    SensorPressureValues_t values = getAbsolutePressureInPascals();
    values.pressure1 *= DEFAULT_PA_TO_CM_H2O;
    values.pressure2 *= DEFAULT_PA_TO_CM_H2O;
    return values;
}

SensorLastPressure_t Sensors::getLastPressure(void) {
    SensorLastPressure_t lastPres;
    lastPres.minPressure = _lastMinPressure;
    lastPres.maxPressure = _lastMaxPressure;
    return lastPres;
}


/**
 * @brief Get relative pressure in H2O cm.
 *
 * @return SensorValues_t - pressure values
 */
SensorPressureValues_t Sensors::getRelativePressureInCmH2O() {
    SensorPressureValues_t values;
    values.pressure1 = _pressure1;
    values.state = SensorStateOK;
    return values;
}

/**
 * @brief Get the Offset Between Pressure Sensors object
 *
 * This function must be called when flow is 0.
 *
 * @param sensors - pressure sensors that derive flow
 * @param samples - number of samples to compute offset
 * @return float - averaged offset bewteen pressure readings
 */
void Sensors::getOffsetBetweenPressureSensors(int samples)
{
    SensorPressureValues_t values;
    float deltaPressure, deltaAvg;
    float cumDelta = 0.0;
    for (int i = 0; i < samples; i++)
    {
        readPressure();
        values = getAbsolutePressureInPascals();
        deltaPressure = values.pressure1 - values.pressure2;
        cumDelta += deltaPressure;
    }
    deltaAvg = cumDelta / samples;
    _pressureSensorsOffset = deltaAvg;
}

#if ENABLED_SENSOR_VOLUME
float Sensors::getFlow(void) {
    return _flow;
}

void Sensors::saveVolume(void) {
    _lastVolume = _volume_ml;
    _lastMinPressure = _minPressure;
    _lastMaxPressure = _maxPressure;
}

void Sensors::readVolume(void) {
    #if ENABLED_SENSOR_VOLUME_SFM3300
        SFM3000_Value_t tmp = _sfm3000->getvalue(); //TODO crc
        if (tmp.crcOK) {
            _volumeState = SensorStateOK;
        } else {
            _volumeState = SensorStateFailed;
        }
        float flow = ((float)tmp.value - SFM3300_OFFSET) / SFM3300_SCALE; //lpm

        // Record flow samples
        if (flow == _flow && flow != 0)
        {
            _flowRepetitionCounter++;
        } else {
            _flowRepetitionCounter = 0;
        }
        _flow = flow;


        unsigned short mseconds = (unsigned short)(millis() - _lastReadFlow);
        float ml = flow * mseconds / 60; // l/min * ms * 1000 (ml) /60000 (ms)
        _volume_ml += ml;
        _lastReadFlow = millis();

    #else
    #error "not implemented"
    #endif
}

void Sensors::resetPressures(void) {
    _minPressure = 255;
    _maxPressure = 0;
}

void Sensors::resetVolumeIntegrator(void) {
    _volume_ml = 0;
    _lastReadFlow = millis();
}
#endif

SensorVolumeValue_t Sensors::getVolume() {
    SensorVolumeValue_t values;

#if ENABLED_SENSOR_VOLUME_SFM3300
    values.state = _volumeState;
    values.volume = _lastVolume;
#endif
    return values;
}
