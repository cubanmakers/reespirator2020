
#ifndef _DEFAULTS_H
#define _DEFAULTS_H

/*
 * Constants
 */

#define DEBUG_UPDATE 0
//#define DEBUG_STATE_MACHINE 1

// Timebase
#define TIME_BASE               20   // msec
#define TIME_SENSOR             100  // msec
#define TIME_SEND_CONFIGURATION 2000 // msec

// Sensors
#define ENABLED_SENSOR_VOLUME 1
#if ENABLED_SENSOR_VOLUME
#define ENABLED_SENSOR_VOLUME_SFM3300 1
#endif

// Stepper
#define STEPPER_MICROSTEPS 4
#define STEPPER_STEPS_PER_REVOLUTION 200

#define STEPPER_MICROSTEPS_PER_REVOLUTION (STEPPER_STEPS_PER_REVOLUTION * STEPPER_MICROSTEPS)
#define STEPPER_DIR                 1
#define STEPPER_HOMING_DIRECTION    (-1)
#define STEPPER_HOMING_SPEED        (STEPPER_MICROSTEPS * 100)   // steps/s
#define STEPPER_LOWEST_POSITION     (STEPPER_MICROSTEPS *  85)   // steps
#define STEPPER_HIGHEST_POSITION    (STEPPER_MICROSTEPS * -100)  // steps
#define STEPPER_SPEED_DEFAULT       (STEPPER_MICROSTEPS *  800)  // steps/s
#define STEPPER_ACC_EXSUFFLATION    (STEPPER_MICROSTEPS *  600)  // steps/s2
#define STEPPER_ACC_INSUFFLATION    (STEPPER_MICROSTEPS *  450)  // steps/s2

// Defaults
#define DEFAULT_HEIGHT                    170 // cm
#define DEFAULT_SEX                       0   // 0: varón, 1: mujer
#define DEFAULT_ML_PER_KG_IDEAL_WEIGHT    7
#define DEFAULT_MAX_TIDAL_VOLUME          800
#define DEFAULT_MIN_TIDAL_VOLUME          240
#define DEFAULT_TRIGGER_THRESHOLD         3.0
#define DEFAULT_RPM                       14
#define DEFAULT_MAX_RPM                   24
#define DEFAULT_MIN_RPM                   3
#define DEFAULT_INSPIRATORY_FRACTION      0.3333F
#define DEFAULT_PEAK_INSPIRATORY_PRESSURE 20
#define DEFAULT_PEAK_ESPIRATORY_PRESSURE  10
#define STEPPER_PEEP_SOLENOID_HYSTERESIS  0.8F     // cmH2O

// Pressure
#define DEFAULT_PA_TO_CM_H2O 0.0102F

// Recruitment
#define DEFAULT_RECRUITMENT_TIMEOUT 40000 // msec
#define DEFAULT_RECRUITMENT_PIP     40    // cmH2O

// Alarms
#define ALARM_MAX_PRESSURE 35 // cmH2O
#define ALARM_MIN_PRESSURE 1  // cmH2O

// Overpressure that triggers valve
#define VALVE_MAX_PRESSURE 60 // cmH2O

// PID constants
#define PID_MIN       -20000
#define PID_MAX        20000
#define PID_KP         80
#define PID_KI         2
#define PID_KD         5
#define PID_TS         TIME_BASE
#define PID_BANGBANG   8

// Solenoid
#define SOLENOID_CLOSED 0
#define SOLENOID_OPEN   1


/*
 * Pinout
 */

#define PIN_STEPPER_STEP        6
#define PIN_STEPPER_DIRECTION   7
#define PIN_STEPPER_EN          8
#define PIN_STEPPER_ALARM       3
#define PIN_BUZZ                11
#define PIN_STEPPER_ENDSTOP     2
#define PIN_SOLENOID            39
#define PIN_RELAY               25

// BME280 SPI for Arduino Nano or Mega 128
// #define PIN_BME_SCK  13
// #define PIN_BME_MISO 12
// #define PIN_BME_MOSI 11
// #define PIN_BME_CS1  10 // sensor de presion 1
// #define PIN_BME_CS2  4  // sensor de presion 2

// BME280 SPI for Arduino Mega 256
// #define PIN_BME_SCK  52
// #define PIN_BME_MISO 50
// #define PIN_BME_MOSI 51
// #define PIN_BME_CS1  53 // sensor de presion 1
// #define PIN_BME_CS2  49 // sensor de presion 2


/*
 * Types
 */

typedef struct {
    short height;
    bool sex;
    short respiratoryRate;
    short peakInspiratoryPressure;
    short peakEspiratoryPressure;
    float triggerThreshold;
    bool hasTrigger;
} VentilationOptions_t;

#endif // DEFAULTS_H
