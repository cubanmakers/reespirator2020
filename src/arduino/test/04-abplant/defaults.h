
#ifndef _DEFAULTS_H
#define _DEFAULTS_H

#undef I2C // definido = Display i2c, sin definir Display parallel

#define DEBUG_UPDATE 0 //
//#define DEBUG_STATE_MACHINE 1
//#define PRUEBAS 1 // testing over arduino without sensors

// Base de tiempos. Periodo de llamada a mechVentilation.update
#define TIME_BASE 5 //msec

// Sensores
#define ENABLED_SENSOR_VOLUME 1
#if ENABLED_SENSOR_VOLUME
#define ENABLED_SENSOR_VOLUME_SFM3300 1
#endif

// Valores motor
#define STEPPER_MICROSTEPS 4
#define STEPPER_STEPS_PER_REVOLUTION 200

#define STEPPER_MICROSTEPS_PER_REVOLUTION (STEPPER_STEPS_PER_REVOLUTION * STEPPER_MICROSTEPS)
#define STEPPER_DIR 1
#define STEPPER_HOMING_DIRECTION    (-1)
#define STEPPER_HOMING_SPEED        (STEPPER_MICROSTEPS *   50)   // Steps/s
#define STEPPER_LOWEST_POSITION     (STEPPER_MICROSTEPS *   70)   // Steps
#define STEPPER_HIGHEST_POSITION    (STEPPER_MICROSTEPS * -120)   // Steps
#define STEPPER_SPEED_DEFAULT       (STEPPER_MICROSTEPS *  800)   // Steps/s
#define STEPPER_SPEED_INSUFFLATION  (STEPPER_MICROSTEPS *  800)   // Steps/s
#define STEPPER_SPEED_EXSUFFLATION  (STEPPER_MICROSTEPS *  800)   // Steps/s
#define STEPPER_ACC_DEFAULT         (STEPPER_MICROSTEPS *  600)   // Steps/s2
#define STEPPER_ACC_EXSUFFLATION    (STEPPER_MICROSTEPS *  600)   // Steps/s2
#define STEPPER_ACC_INSUFFLATION    (STEPPER_MICROSTEPS *  450)   // Steps/s2

// Valores por defecto
#define DEFAULT_ESTATURA 170 // cm
#define DEFAULT_SEXO 0 // 0: varón, 1: mujer
#define DEFAULT_ML_POR_KG_DE_PESO_IDEAL 7
#define DEFAULT_MAX_VOLUMEN_TIDAL 800
#define DEFAULT_MIN_VOLUMEN_TIDAL 240
#define DEFAULT_FLUJO_TRIGGER 3
#define DEFAULT_RPM 15
#define DEFAULT_MAX_RPM 24
#define DEFAULT_MIN_RPM 3
#define DEFAULT_POR_INSPIRATORIO 33  // %

#define DEFAULT_PRESSURE_V_FLOW_K1 0.1   //Constante proporcional que relaciona presión con caudal

#define FLOW__INSUFLATION_TRIGGER_LEVEL 3.0   //LPM

// Ventilation cycle timing
#define WAIT_BEFORE_EXSUFLATION_TIME 500    //msec

// PID constants
#define PID_MIN 0
#define PID_MAX 100

#define PID_P 1.0
#define PID_I 0.1 //TODO To be adjusted
#define PID_D 0.0 //TODO To be adjusted
#define PID_dt TIME_BASE //msec. I hast to match the MechVentilation.update() refresh period.

#define PID_KP PID_P
#define PID_KI (PID_I * PID_dt)
#define PID_KD (PID_D / PID_dt)

//Volume to Position and viceversa constants
#define STEPS_FOR_TOTALLY_PRESSED_AMBU (STEPPER_MICROSTEPS_PER_REVOLUTION / 2) //steps
#define VOLUME_FOR_TOTALLY_PRESSED_AMBU 800 //ml
#define K_VOL2POS (STEPS_FOR_TOTALLY_PRESSED_AMBU / VOLUME_FOR_TOTALLY_PRESSED_AMBU)
#define K_POS2VOL (VOLUME_FOR_TOTALLY_PRESSED_AMBU / STEPS_FOR_TOTALLY_PRESSED_AMBU)
#define K_FLOW2SPEED (25/12)

// Solenoid
#define SOLENOID_CLOSED true
#define SOLENOID_OPEN (!SOLENOID_CLOSED)

#endif // DEFAULTS_H
