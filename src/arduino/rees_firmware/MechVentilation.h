/** Mechanical ventilation.
 *
 * @file MechVentilation.h
 *
 * This is the mechanical ventilation software module.
 * It handles the mechanical ventilation control loop.
 */
#ifndef INC_MECHANICAL_VENTILATION_H
#define INC_MECHANICAL_VENTILATION_H

#include <float.h>
#include <inttypes.h>
#include "defaults.h"
#include "calc.h"
#include "Sensors.h"
#include "src/AutoPID/AutoPID.h"
#include "src/FlexyStepper/FlexyStepper.h"

/** States of the mechanical ventilation. */
enum State
{
    Init_Insufflation = 1,
    State_Insufflation = 2, /**< Insufflating (PID control). */
    Init_Exsufflation = 3,
    State_Exsufflation = 4, /**< Return to position 0 and wait for the patient to exsufflate. */
    State_Homing = 0,
    State_Error = -1
};

enum Alarm
{
    No_Alarm = 0,
    Alarm_Overpressure = 1,
    Alarm_Underpressure = 2,
    Alarm_No_Flux = 3
};

typedef struct {
    float pip;
    unsigned short timeoutIns;
} Configuration_t;

/**
 * This is the mechanical ventilation class.
 */
class MechVentilation
{
public:
    /**
	 * @brief Construct a new Mech Ventilation object
	 *
	 * @param stepper
	 * @param sensors
	 * @param pid
	 * @param options
	 */
    MechVentilation(
        FlexyStepper *stepper,
        Sensors *sensors,
        AutoPID *pid,
        VentilationOptions_t options);

    boolean getStartWasTriggeredByPatient();
    void setVentilationCyle_WaitTime(float speedExsufflation);
    /** Start mechanical ventilation. */
    void start(void);
    /** Stop mechanical ventilation. */
    void stop(void);
    /** Alarms */
    void evaluatePressure(void);
    /** Update mechanical ventilation.
     *
     * If any control variable were to change, new value
     * would be applied at the beginning of the next ventilation
     * cycle.
     *
     * @note This method must be called on a timer loop.
     */
    void update(void);

    /** Recruitment */
    void activateRecruitment(void);
    void deactivateRecruitment(void);

    /**
     * getters
     */
    bool getSensorErrorDetected();
    uint8_t getRPM(void);
    short getExsuflationTime(void);
    short getInsuflationTime(void);
    short getPeakInspiratoryPressure(void);
    short getPeakEspiratoryPressure(void);
    State getState(void);
    /**
     * setters
     */
    void setRPM(uint8_t rpm);
    void setPeakInspiratoryPressure(float pip);
    void setPeakEspiratoryPressure(float peep);
    void setState(State state);


private:
    /** Initialization. */
    void _init(
        FlexyStepper *stepper,
        Sensors *sensors,
        AutoPID *pid,
        VentilationOptions_t options);
#if 0
    int _calculateInsuflationPosition (void);
#endif

    /** Set state. */
    void _setAlarm(Alarm alarm);
#if 0
    void _increaseInsuflationSpeed (byte factor);
    void _decreaseInsuflationSpeed (byte factor);
    void _increaseInsuflation (byte factor);
    void _decreaseInsuflation (byte factor);
#endif
    void _setInspiratoryCycle(void);

    /* Configuration parameters */
    FlexyStepper *_stepper;
    Sensors *_sensors;
    AutoPID *_pid;

    /** Flow trigger activation. */
    bool _hasTrigger;
    /** Flow trigger value in litres per minute. */
    float _triggerThreshold;
    /**  Insufflation timeout in seconds. */
    unsigned short volatile _timeoutIns;
    /** Exsufflation timeout in seconds. */
    unsigned short _timeoutEsp;
    /** Breaths per minute */
    uint8_t _rpm;
    /** Peak inspiratory pressure */
    short volatile _pip;
    /** Peak espiratory pressure */
    short _peep;
    /** Recruitment */
    bool volatile _recruitmentMode = false;

    /* Configuration */
    Configuration_t _nominalConfiguration;

    /* Internal state */
    /** Current state. */
    State _currentState = State_Homing;
    Alarm _currentAlarm = No_Alarm;

    /** Stepper speed. Steps per seconds. */
    float _stepperSpeed;
    bool _running = false;
    bool _sensor_error_detected;
    bool _startWasTriggeredByPatient = false;
    float _currentPressure = 0.0;
    //float _currentFlow = 0.0;
    //float _currentVolume = 0.0;
};

#endif /* INC_MECHANICAL_VENTILATION_H */
