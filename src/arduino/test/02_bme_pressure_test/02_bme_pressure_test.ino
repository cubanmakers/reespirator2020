/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include "src/Adafruit_BME280/Adafruit_BME280.h"

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



#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme1(
  BMP_CS1,
  BMP_MOSI,
  BMP_MISO,
  BMP_SCK
);
Adafruit_BME280 bme2(
  BMP_CS2,
  BMP_MOSI,
  BMP_MISO,
  BMP_SCK
);

unsigned long delayTime;

void setup() {
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    // Serial.println(F("BME280 test"));

    unsigned status1;
    unsigned status2;

    // default settings
    status1 = bme1.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status1) {
        Serial.print("Could not find a valid BME280 sensor in position 1, check wiring, address, sensor ID!; CS Pin:"); Serial.println(BMP_CS1);
        Serial.print("SensorID was: 0x"); Serial.println(bme1.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }


    status2 = bme2.begin();
    Serial.print("SensorID was: 0x"); Serial.println(bme2.sensorID(),16);
    if (!status2) {
        Serial.print("Could not find a valid BME280 sensor in position 2, check wiring, address, sensor ID!; CS Pin:"); Serial.println(BMP_CS2);
        Serial.print("SensorID was: 0x"); Serial.println(bme2.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }


    bme1.setSampling(Adafruit_BME280::MODE_NORMAL,     // Operating Mode.
                      Adafruit_BME280::SAMPLING_NONE,     // Temp. oversampling
                      Adafruit_BME280::SAMPLING_X16,    // Pressure oversampling
                      Adafruit_BME280::SAMPLING_NONE,   // humidity sampling
                      Adafruit_BME280::FILTER_OFF,      // Filtering.
                      Adafruit_BME280::STANDBY_MS_0_5); // Standby time.
    
    // Serial.println("-- Setting sampling BME280_1--");

    bme2.setSampling(Adafruit_BME280::MODE_NORMAL,     // Operating Mode.
                      Adafruit_BME280::SAMPLING_NONE,     // Temp. oversampling
                      Adafruit_BME280::SAMPLING_X16,    // Pressure oversampling
                      Adafruit_BME280::SAMPLING_NONE,   // humidity sampling
                      Adafruit_BME280::FILTER_OFF,      // Filtering.
                      Adafruit_BME280::STANDBY_MS_0_5); // Standby time.
    
    // Serial.println("-- Setting sampling BME280_2--");
    
    delayTime = 1000;

    // Serial.println();
}


void printValues1() {

    Serial.println("-- Default Test BME280_1--");
    Serial.print("Temperature BME280_1 = ");
    Serial.print(bme1.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure BME280_1 = ");

    Serial.print(bme1.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude BME280_1 = ");
    Serial.print(bme1.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity BME280_1 = ");
    Serial.print(bme1.readHumidity());
    Serial.println(" %");

    Serial.println();

}

void printValues2() {
    Serial.println("-- Default Test BME280_2--");
    Serial.print("Temperature BME280_2 = ");
    Serial.print(bme2.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure BME280_2 = ");

    Serial.print(bme2.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude BME280_2 = ");
    Serial.print(bme2.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity BME280_2 = ");
    Serial.print(bme2.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void testDiference (){
    float pres1, pres2, diff;
    pres1 = bme1.readPressure() / 100.0F; // hPa
    pres2 = bme2.readPressure() / 100.0F; // hPa

    // Serial.print("Sensor_1 Pressure");
    // Serial.print(pres1);
    // Serial.println(" hPa");

    // Serial.print("Sensor_2 Pressure");
    // Serial.print(pres2);
    // Serial.println(" hPa");

    diff = 100 * (pres1 - pres2);

    // Serial.print("Diference:");
    Serial.print("0,");
    Serial.println(diff);
    // Serial.println(" hPa");
    
}


void loop() { 
    // Serial.println("-- Default Test BME280_1--");
    // printValues1();
    // delay(delayTime);

    // Serial.println("-- Default Test BME280_2--");
    // printValues2();
    // delay(delayTime);

    // Serial.println("-- Testing Sensor pressure reading diference between 1 & 2--");
    testDiference();
    delay(25);
    // delay(delayTime);
}

