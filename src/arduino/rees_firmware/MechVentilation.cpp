/** Mechanical ventilation.
 *
 * @file MechVentilation.cpp
 *
 * This is the mechanical ventilation software module.
 * It handles the mechanical ventilation control loop.
 */

#include "MechVentilation.h"

int currentWaitTriggerTime = 0;
int currentStopInsufflationTime = 0;
float currentFlow = 0;

MechVentilation::MechVentilation(
    FlexyStepper *stepper,
    Sensors *sensors,
    AutoPID *pid,
    VentilationOptions_t options)
{

    _init(
        stepper,
        sensors,
        pid,
        options);
}

//TODO: use this method to play a beep in main loop, 1 second long for example.
boolean MechVentilation::getStartWasTriggeredByPatient()
{ //returns true if last respiration cycle was started by patient trigger. It is cleared when read.
    if (_startWasTriggeredByPatient)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//TODO: use this method to play a beep in main loop, 2 second long for example.
boolean MechVentilation::getSensorErrorDetected()
{ //returns true if there was an sensor error detected. It is cleared when read.
    if (_sensor_error_detected)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MechVentilation::start(void)
{
    _running = true;
}

void MechVentilation::stop(void)
{
    _running = false;
}

uint8_t MechVentilation::getRPM(void)
{
    return _rpm;
}
short MechVentilation::getExsuflationTime(void)
{
    return _timeoutEsp;
}
short MechVentilation::getInsuflationTime(void)
{
    return _timeoutIns;
}

short MechVentilation::getPeakInspiratoryPressure(void)
{
    return _pip;
}

short MechVentilation::getPeakEspiratoryPressure(void)
{
    return _peep;
}

State MechVentilation::getState(void)
{
    return _currentState;
}

void MechVentilation::setRPM(uint8_t rpm)
{
    _rpm = rpm;
    _setInspiratoryCycle();
}

void MechVentilation::setPeakInspiratoryPressure(float pip)
{
    _pip = pip;
}

void MechVentilation::setPeakEspiratoryPressure(float peep)
{
    _peep = peep;
}

void MechVentilation::_setInspiratoryCycle(void)
{
    float timeoutCycle = ((float)60) * 1000 / ((float)_rpm); // Tiempo de ciclo en msegundos
    _timeoutIns = timeoutCycle * DEFAULT_INSPIRATORY_FRACTION;
    _timeoutEsp = (timeoutCycle) - _timeoutIns;
}

void MechVentilation::evaluatePressure(void)
{
    if (_currentPressure > ALARM_MAX_PRESSURE)
    {
        digitalWrite(PIN_BUZZ, HIGH);
        _currentAlarm = Alarm_Overpressure;
    }
    // else if (_currentPressure < ALARM_MIN_PRESSURE)
    // {
        // digitalWrite(PIN_BUZZ, HIGH);
        // _currentAlarm = Alarm_Underpressure;
    // }
    else
    {
        if (_currentAlarm != No_Alarm) {
            digitalWrite(PIN_BUZZ, LOW);
            _currentAlarm = No_Alarm;
        }
    }

    // Valve
    if (_currentPressure > VALVE_MAX_PRESSURE)
    {
        digitalWrite(PIN_SOLENOID, SOLENOID_OPEN);
    }
}

void MechVentilation::activateRecruitment(void)
{
    _nominalConfiguration.pip = _pip;
    _nominalConfiguration.timeoutIns = _timeoutIns;
    _pip = DEFAULT_RECRUITMENT_PIP;
    _timeoutIns = DEFAULT_RECRUITMENT_TIMEOUT;
    _recruitmentMode = true;
    setState(Init_Insufflation);
}

void MechVentilation::deactivateRecruitment(void)
{
    _pip = _nominalConfiguration.pip;
    _timeoutIns = _nominalConfiguration.timeoutIns;
    _recruitmentMode = false;
    setState(Init_Exsufflation);
}

/**
 * It's called from timer1Isr
 */
void MechVentilation::update(void)
{

    static int totalCyclesInThisState = 0;
    static int currentTime = 0;
    static int flowSetpoint = 0;

#if DEBUG_STATE_MACHINE
    extern volatile String debugMsg[];
    extern volatile byte debugMsgCounter;
#endif


    SensorPressureValues_t pressures = _sensors->getRelativePressureInCmH2O();
    _currentPressure = pressures.pressure1;
    // @dc unused
    // _currentVolume = _sensors->getVolume().volume;
    //_currentFlow = _sensors->getFlow();
    if (pressures.state != SensorStateOK)
    {                                  // Sensor error detected: return to zero position and continue from there
        _sensor_error_detected = true; //An error was detected in sensors
        /* Status update, for this time */
        // TODO: SAVE PREVIOUS CYCLE IN MEMORY AND RERUN IT
#if DEBUG_UPDATE
        Serial.println("fail sensor");
#endif
        setState(State_Exsufflation);
    }
    else
    {
        _sensor_error_detected = false; //clear flag
    }

    // Check pressures
    evaluatePressure();

    refreshWatchDogTimer();

    switch (_currentState)
    {
    case Init_Insufflation:
    {
#if DEBUG_UPDATE
        Serial.println("Starting insuflation");
#endif
        // Close Solenoid Valve
        digitalWrite(PIN_SOLENOID, SOLENOID_CLOSED);

        // Reset volume
        _sensors->resetVolumeIntegrator();

        totalCyclesInThisState = (_timeoutIns) / TIME_BASE;

        /* Stepper control: set acceleration and end-position */
        _stepper->setSpeedInStepsPerSecond(_stepperSpeed);
        _stepper->setAccelerationInStepsPerSecondPerSecond(
            STEPPER_ACC_INSUFFLATION);
        _stepper->setTargetPositionInSteps(STEPPER_HIGHEST_POSITION);

        _pid->reset();

#if DEBUG_STATE_MACHINE
        debugMsg[debugMsgCounter++] = "State: InitInsuflation at " + String(millis());
#endif

        /* Status update, reset timer, for next time, and reset PID integrator to zero */
        setState(State_Insufflation);

        currentTime = 0;
    }
    break;

    /*
     * Insufflation
     */
    case State_Insufflation:
    {

        /* Stepper control: set end position */

#if DEBUG_UPDATE
//Serial.println("Motor:speed=" + String(_stepperSpeed));
#endif

        // time expired
        if (currentTime > totalCyclesInThisState)
        {
            if (!_stepper->motionComplete())
            {
                // motor not finished, force motor to stop in current position
                _stepper->setTargetPositionInSteps(_stepper->getCurrentPositionInSteps());
            }
            setState(Init_Exsufflation);
            currentTime = 0;

            if (_recruitmentMode) {
                deactivateRecruitment();
            }
        }
        else
        {
            _pid->run(_currentPressure, (float)_pip, &_stepperSpeed);

            _stepper->setSpeedInStepsPerSecond(abs(_stepperSpeed));
            if (_stepperSpeed >= 0)
            {
                _stepper->setTargetPositionInSteps(STEPPER_HIGHEST_POSITION);
            }
            else
            {
                _stepper->setTargetPositionInSteps(STEPPER_LOWEST_POSITION);
            }

            if (_recruitmentMode)
            {
                if (_currentPressure > DEFAULT_RECRUITMENT_PIP + 2)
                {
                    digitalWrite(PIN_SOLENOID, SOLENOID_OPEN);
                }
                else if (_currentPressure < DEFAULT_RECRUITMENT_PIP - 0.5)
                {
                    digitalWrite(PIN_SOLENOID, SOLENOID_CLOSED);
                }
            }

            currentTime++;
        }
    }
    break;
    case Init_Exsufflation:
    {
#if DEBUG_UPDATE
        Serial.println("Starting exsuflation");
#endif
        // Open Solenoid Valve
        digitalWrite(PIN_SOLENOID, SOLENOID_OPEN);

        totalCyclesInThisState = _timeoutEsp / TIME_BASE;
        _sensors->saveVolume();
        _sensors->resetVolumeIntegrator();


#if DEBUG_STATE_MACHINE
        debugMsg[debugMsgCounter++] = "ExsuflationTime=" + String(totalCyclesInThisState);
#endif


        /* Stepper control*/
        _stepper->setSpeedInStepsPerSecond(_stepperSpeed);
        _stepper->setAccelerationInStepsPerSecondPerSecond(
            STEPPER_ACC_EXSUFFLATION);
        _stepper->setTargetPositionInSteps(
            STEPPER_DIR * (STEPPER_LOWEST_POSITION));
#if DEBUG_STATE_MACHINE
        debugMsg[debugMsgCounter++] = "Motor: to exsuflation at " + String(millis());
#endif

        _pid->reset();

        /* Status update and reset timer, for next time */
        setState(State_Exsufflation);
        currentTime = 0;
    }
    break;

    /*
     * Exsufflation
     */
    case State_Exsufflation:
    {
#if 0
        if (_stepper->motionComplete())
        {
            if (currentFlow < _triggerThreshold && _hasTrigger)
            { // The start was triggered by patient
                _startWasTriggeredByPatient = true;

#if DEBUG_STATE_MACHINE
                debugMsg[debugMsgCounter++] = "!!!! Trigered by patient";
#endif

                /* Status update, for next time */
                setState(Init_Insufflation);
            }
        }
#endif
        // Time has expired
        if (currentTime > totalCyclesInThisState)
        {
            if (!_stepper->motionComplete())
            {
                // motor not finished, force motor to stop in current position
                _stepper->setTargetPositionInSteps(_stepper->getCurrentPositionInSteps());
            }
            /* Status update and reset timer, for next time */
            setState(Init_Insufflation);
            _startWasTriggeredByPatient = false;

            currentTime = 0;
        }
        else
        {
            _pid->run(_currentPressure, (float)_peep, &_stepperSpeed);

            _stepper->setSpeedInStepsPerSecond(abs(_stepperSpeed));
            if (_stepperSpeed >= 0)
            {
                _stepper->setTargetPositionInSteps(STEPPER_HIGHEST_POSITION);
            }
            else
            {
                _stepper->setTargetPositionInSteps(STEPPER_LOWEST_POSITION);
            }

            // Assist stepper with solenoid
            if (_currentPressure <= _peep - STEPPER_PEEP_SOLENOID_HYSTERESIS)
            {
                digitalWrite(PIN_SOLENOID, SOLENOID_CLOSED);
            }
            else if (_currentPressure > _peep + STEPPER_PEEP_SOLENOID_HYSTERESIS)
            {
                digitalWrite(PIN_SOLENOID, SOLENOID_OPEN);
            }
            currentTime++;
        }
    }
    break;

    case State_Homing:
    {
        // Open Solenoid Valve
        digitalWrite(PIN_SOLENOID, SOLENOID_OPEN);

        if (_sensor_error_detected)
        {
            // error sensor reading
            _running = false;
#if DEBUG_UPDATE
            Serial.println("Sensor: FAILED");
#endif
        }

        /*
                 * If not in home, do Homing.
                 * 0: stepper is in home
                 * 1: stepper is not in home
                 */

        if (digitalRead(PIN_STEPPER_ENDSTOP))
        {

            /* Stepper control: homming */
#if DEBUG_UPDATE
            Serial.println("Attempting homing...");
#endif
            if (_stepper->moveToHomeInSteps(
                    STEPPER_HOMING_DIRECTION,
                    STEPPER_HOMING_SPEED,
                    STEPPER_STEPS_PER_REVOLUTION * STEPPER_MICROSTEPS,
                    PIN_STEPPER_ENDSTOP) != true)
            {
#if DEBUG_UPDATE
                    Serial.println("Homing failed");
#endif
            }
        }

        /* Status update and reset timer, for next time */
        currentTime = 0;
        setState(Init_Exsufflation);
    }
    break;

    case State_Error:
        break;
    default:
        //TODO
        break;
    }
}

void MechVentilation::_init(
    FlexyStepper *stepper,
    Sensors *sensors,
    AutoPID *pid,
    VentilationOptions_t options)
{
    /* Set configuration parameters */
    _stepper = stepper;
    _sensors = sensors;
    _pid = pid;
    _rpm = options.respiratoryRate;
    _pip = options.peakInspiratoryPressure;
    _peep = options.peakEspiratoryPressure;
    setRPM(_rpm);
    _hasTrigger = options.hasTrigger;
    if (_hasTrigger)
    {
        _triggerThreshold = options.triggerThreshold;
    }
    else
    {
        _triggerThreshold = FLT_MAX;
    }

    /* Initialize internal state */
    _currentState = State_Homing;
    _stepperSpeed = STEPPER_SPEED_DEFAULT;

    //
    // connect and configure the stepper motor to its IO pins
    //
    //;
    _stepper->connectToPins(PIN_STEPPER_STEP, PIN_STEPPER_DIRECTION);
    _stepper->setStepsPerRevolution(STEPPER_STEPS_PER_REVOLUTION * STEPPER_MICROSTEPS);

    _sensor_error_detected = false;
}

void MechVentilation::setState(State state)
{
    _currentState = state;
}

void MechVentilation::_setAlarm(Alarm alarm)
{
    _currentAlarm = alarm;
}
