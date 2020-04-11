#include "Sensors.h"
#include "src/Honeywell_ABP-master/Honeywell_ABP.h"
Sensors* sensors;

    Honeywell_ABP abp(
  0x28,   // I2C address
  0,      // minimum pressure
  70.307,      // maximum pressure
  "mbar"   // pressure unit
);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("hola");
  Wire.begin();

}

void loop() {
    static unsigned long lastRead = millis();
    if (millis() > lastRead + 200) {
        Serial.println("Reading");

        abp.update();
        float pres = abp.pressure();
        
        Serial.println("Pressure " + String(pres));
        Serial.println(*(abp.error_msg()));
        
        lastRead = millis();
        //sensors->resetVolumeIntegrator();
    }
}