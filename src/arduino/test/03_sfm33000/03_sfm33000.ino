#include "Sensors.h"

Sensors* sensors;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("hola");
    sensors =  new Sensors();
    Serial.println("hola2");

}

void loop() {
    static unsigned long lastRead = millis();
    if (millis() > lastRead + 200) {
        //Serial.println("Reading");
        sensors->readVolume();
        SensorVolumeValue_t value = sensors->getVolume();
        if (value.state != SensorStateOK) {
            Serial.println("Reading failed");
        }
        Serial.println("Volume " + String(value.volume));
        Serial.println("Flux=" + String(sensors->getFlux()));
        lastRead = millis();
        //sensors->resetVolumeIntegrator();
    }
}