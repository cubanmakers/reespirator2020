/**
 * @file rees_firmware.ino
 * @author Reesistencia Team
 * @brief 
 * @version 0.1
 * @date 2020-03-29
 * 
 * @copyright GPLv3
 * 
 */

/**
 * Dependencies
 */

#include "defaults.h"
#include "calc.h"
#include "Sensors.h"
#include "MechVentilation.h"

#include "src/AutoPID/AutoPID.h"
#include "src/FlexyStepper/FlexyStepper.h"
#include "src/TimerOne/TimerOne.h"
#include "src/TimerThree/TimerThree.h"

/**
 * Variables
 */

#if DEBUG_STATE_MACHINE
volatile String debugMsg[15];
volatile byte debugMsgCounter = 0;
#endif

FlexyStepper *stepper = new FlexyStepper();
Sensors *sensors;
AutoPID *pid;
MechVentilation *ventilation;

VentilationOptions_t options;

/**
 * Read commands
 */

void readIncomingMsg(void)
{
    char msg[100];
    Serial2.readStringUntil('\n').toCharArray(msg, 100);
    int pip, peep, fr;
    if (String(msg).substring(0, 6) == "CONFIG")
    {
        int rc = sscanf(msg, "CONFIG PIP %d", &pip);
        if (rc == 1)
        {
            ventilation->setPeakInspiratoryPressure(pip);
        }
        else
        {
            int rc = sscanf(msg, "CONFIG PEEP %d", &peep);
            if (rc == 1)
            {
                ventilation->setPeakEspiratoryPressure(peep);
            }
            else
            {
                int rc = sscanf(msg, "CONFIG BPM %d", &fr);
                if (rc == 1)
                {
                    ventilation->setRPM(fr);
                }
            }
        }
    }
    else if (String(msg).substring(0, 7) == "RECRUIT")
    {
        uint8_t tmp = 255;
        int rc = sscanf(msg, "RECRUIT %d", &tmp);
        switch (tmp)
        {
        case 0:
            Serial.println("ACK 0");
            ventilation->deactivateRecruitment();
            break;
        case 1:
            Serial.println("ACK 1");
            ventilation->activateRecruitment();
            break;
        default:
            break;
        }
    }
}

/**
 * Setup
 */

void setup()
{
    // Puertos serie
    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println(F("Setup"));

    // Zumbador
    pinMode(PIN_BUZZ, OUTPUT);
    digitalWrite(PIN_BUZZ, HIGH); // test zumbador
    delay(100);
    digitalWrite(PIN_BUZZ, LOW);

    // FC efecto hall
    pinMode(PIN_STEPPER_ENDSTOP, INPUT_PULLUP); // el sensor de efecto hall da un 1 cuando detecta

    // Solenoid
    pinMode(PIN_SOLENOID, OUTPUT);

    // Sensores de presión
    sensors = new Sensors();
    int check = sensors->begin();
#if 0
    if (check) {
        if (check == 1) {
            Serial.println(F("Could not find sensor BME280 number 1, check wiring!"));
        } else if (check == 2) {
            Serial.println(F("Could not find sensor BME280 number 2, check wiring!"));
        }
        while (1);
    }
#endif

    // PID
    pid = new AutoPID(PID_MIN, PID_MAX, PID_KP, PID_KI, PID_KD);
    // if pressure is more than PID_BANGBANG below or above setpoint,
    // output will be set to min or max respectively
    pid->setBangBang(PID_BANGBANG);
    // set PID update interval
    pid->setTimeStep(PID_TS);

    // Parte motor
    pinMode(PIN_STEPPER_EN, OUTPUT);
    digitalWrite(PIN_STEPPER_EN, HIGH);

    // TODO: Añadir aquí la configuarcion inicial desde puerto serie

    options.height = DEFAULT_HEIGHT;
    options.sex = DEFAULT_SEX;
    options.respiratoryRate = DEFAULT_RPM;
    options.peakInspiratoryPressure = DEFAULT_PEAK_INSPIRATORY_PRESSURE;
    options.peakEspiratoryPressure = DEFAULT_PEAK_ESPIRATORY_PRESSURE;
    options.triggerThreshold = DEFAULT_TRIGGER_THRESHOLD;
    options.hasTrigger = false;

    ventilation = new MechVentilation(
        stepper,
        sensors,
        pid,
        options
    );

    Serial.println("Tiempo del ciclo (seg):" + String(ventilation->getExsuflationTime() + ventilation->getInsuflationTime()));
    Serial.println("Tiempo inspiratorio (mseg):" + String(ventilation->getInsuflationTime()));
    Serial.println("Tiempo espiratorio (mseg):" + String(ventilation->getExsuflationTime()));

    // TODO: Esperar aqui a iniciar el arranque desde el serial

    // Habilita el motor
    digitalWrite(PIN_STEPPER_EN, LOW);

    // Relay and stepper driver alarm
    // pinMode(PIN_RELAY, OUTPUT);
    // digitalWrite(PIN_RELAY, LOW);
    // pinMode(PIN_STEPPER_ALARM, INPUT_PULLUP);

    // configura la ventilación
    ventilation->start();
    ventilation->update();

    delay(1000);

    sensors->readPressure();

    //TODO: Option: if (Sensores ok) { arranca timer3 }
    Timer3.initialize(50); //50us
    Timer3.attachInterrupt(timer3Isr);

    // TODO: Make this period dependant of TIME_BASE
    // TIME_BASE * 1000 does not work!!
    // Timer1.initialize(50000); // 50 ms
    Timer1.initialize(20000);
    Timer1.attachInterrupt(timer1Isr);

    // attachInterrupt(digitalPinToInterrupt(PIN_STEPPER_ALARM), driverAlarmIsr, FALLING);
}

/**
 * Loop
 */

void loop()
{
    unsigned long time;
    time = millis();
    unsigned long static lastReadSensor = 0;
    unsigned long static lastSendConfiguration = 0;
    State static lastState;

    if (time > lastSendConfiguration + TIME_SEND_CONFIGURATION)
    {
        Serial2.print(F("CONFIG "));
        Serial2.print(ventilation->getPeakInspiratoryPressure());
        Serial2.print(F(" "));
        Serial2.print(ventilation->getPeakEspiratoryPressure());
        Serial2.print(F(" "));
        Serial2.println(ventilation->getRPM());
        lastSendConfiguration = time;

        // Check volume sensor
        if (sensors->stalledVolumeSensor())
        {
            Serial.println("Rebooting");
            sensors->rebootVolumeSensor();
        }
    }

    if (time > lastReadSensor + TIME_SENSOR)
    {
        sensors->readPressure();
        SensorPressureValues_t pressure = sensors->getRelativePressureInCmH2O();

        sensors->readVolume();
        SensorVolumeValue_t volume = sensors->getVolume();

        char string[100];
        sprintf(string, "DT %05d %05d %05d %06d", ((int)pressure.pressure1), ((int)pressure.pressure2), volume.volume, ((int)(sensors->getFlow() * 1000)));
        Serial2.println(string);
        // Serial.println(string);

        if (pressure.state == SensorStateFailed)
        {
            //TODO sensor fail. do something
            Serial.println(F("FALLO Sensor"));
            // TODO: BUZZ ALARMS LIKE HELL
        }
        if (volume.state == SensorStateFailed)
        {
            Serial.println("Fallo CRC sensor volumen");
        }
        lastReadSensor = time;

        /*
         * Notify insufflated volume
         */
        if (ventilation->getState() != lastState)
        {
            SensorLastPressure_t lastPressure = sensors->getLastPressure();
            if (ventilation->getState() == Init_Exsufflation)
            {
                Serial2.println("EOC " + String(lastPressure.maxPressure) + " " +
                                String(lastPressure.minPressure) + " " + String(volume.volume));
                sensors->resetPressures();
                sensors->resetVolumeIntegrator();
            }
            else if (ventilation->getState() == State_Exsufflation)
            {
                if (lastState != Init_Exsufflation)
                {
                    Serial2.println("EOC " + String(lastPressure.maxPressure) + " " +
                                    String(lastPressure.minPressure) + " " + String(volume.volume));
                    sensors->resetPressures();
                    sensors->resetVolumeIntegrator();
                }
            }
        }
        lastState = ventilation->getState();
    }

    if (Serial2.available())
    {
        readIncomingMsg();
    }

#if DEBUG_STATE_MACHINE
    if (debugMsgCounter)
    {
        for (byte i = 0; i < debugMsgCounter; i++)
        {
            Serial.println(debugMsg[i]);
        }
        debugMsgCounter = 0;
    }
#endif
}

void timer1Isr(void)
{
    ventilation->update();
}

void timer3Isr(void)
{
    stepper->processMovement();
}

// void driverAlarmIsr(void)
// {
//     digitalWrite(PIN_SOLENOID, SOLENOID_OPEN);
//     digitalWrite(PIN_RELAY, HIGH);
//     delayMicroseconds(60000);
//     delayMicroseconds(60000);
//     delayMicroseconds(60000);
//     digitalWrite(PIN_RELAY, LOW);
//     delayMicroseconds(60000);
//     delayMicroseconds(60000);
//     delayMicroseconds(60000);
//     ventilation->setState(State_Homing);
//     digitalWrite(PIN_BUZZ, HIGH); // test zumbador
//     delayMicroseconds(60000);
//     digitalWrite(PIN_BUZZ, LOW);
// }
