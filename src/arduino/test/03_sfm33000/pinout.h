#ifndef PINOUT_H
#define PINOUT_H

#include "Arduino.h"

//Display

#define LCD_ROWS 2
#define LCD_COLS 16

#ifdef I2C  //i2c

//D irección de LCD I2C
#define I2C_DIR 0x3F

#else

// pines Display parallel  // parallel
#define LCD_RS A0
#define LCD_RW A1
#define LCD_E  A2
#define LCD_D4 A3
#define LCD_D5 A4
#define LCD_D6 A5
#define LCD_D7 A6

#endif // I2C

// Rotary encoder
#define CLKpin 9
#define DTpin 3
#define SWpin 2

#define ENpin 8
// Stepper driver (FlexyStepper)
#define PIN_STEPPER_STEP 6
#define MOTOR_STEP_PIN PIN_STEPPER_STEP
#define PIN_STEPPER_DIRECTION 7
#define MOTOR_DIRECTION_PIN PIN_STEPPER_DIRECTION


// Buzzer
#define BUZZpin 11

// Sensor hall
#define ENDSTOPpin 21

// Solenoid pine
#define SOLENOIDpin 39

// BME280 SPI al menos para Arduino Nano o Mega 128
// #define BMP_SCK  13
// #define BMP_MISO 12
// #define BMP_MOSI 11
// #define BMP_CS1  10 // sensor de presion 1
// #define BMP_CS2  4  // sensor de presion 2

// BME280 SPI para Arduino Mega 256
#define BMP_SCK  52
#define BMP_MISO 50
#define BMP_MOSI 51
#define BMP_CS1  53 // sensor de presion 1
#define BMP_CS2  49 // sensor de presion 2

#endif // ENCODER_H
