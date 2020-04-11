#include "Encoder.h"
#include "Arduino.h"

const int8_t KNOBDIR[] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0};

static volatile bool _buttonPressedFlag = false;
static volatile unsigned long _buttonPressedTimestamp = 0;
static void _buttonPressed(void);

Encoder::Encoder(int pin1, int pin2, int pulsador)
{
  _pin1 = pin1;
  _pin2 = pin2;
  _pulsador = pulsador;

  // Setup the input pins and turn on pullup resistor
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pulsador, INPUT_PULLUP);
  byte interrupt = digitalPinToInterrupt(pulsador);
  if (interrupt >= 0)
  {
    attachInterrupt(interrupt, _buttonPressed, FALLING);
  }

  // when not started in motion, the current state of the encoder should be 3
  _oldState = 3;

  // start with position 0;
  _position = 0;
  _positionExt = 0;
  _positionExtPrev = 0;
  _flag = false;
  _tiempo = 0;
}

long Encoder::getPosition()
{
  return _positionExt;
}

// unused
int Encoder::getDirection()
{

  int ret = 0;

  if (_positionExtPrev > _positionExt)
  {
    ret = -1;
    _positionExtPrev = _positionExt;
  }
  else if (_positionExtPrev < _positionExt)
  {
    ret = 1;
    _positionExtPrev = _positionExt;
  }
  else
  {
    ret = 0;
    _positionExtPrev = _positionExt;
  }

  return ret;
}

// unused
void Encoder::setPosition(long newPosition)
{
  _position = ((newPosition << 2) | (_position & 0x03L));
  _positionExt = newPosition;
  _positionExtPrev = newPosition;
}

void Encoder::tick(void)
{
  int sig1 = digitalRead(_pin1);
  int sig2 = digitalRead(_pin2);
  int8_t thisState = sig1 | (sig2 << 1);

  if (_oldState != thisState)
  {
    _position += KNOBDIR[thisState | (_oldState << 2)];

    if (thisState == LATCHSTATE)
      _positionExt = _position >> 2;

    _oldState = thisState;
  }
}

/**
 * @brief Modifica un valor dicotómico entre 0 y 1.
 *
 * Cuando se gira el encoder, el valor se pasa de 0 a 1 y
 * de 1 a 0 cada vez que se mueve el dial.
 *
 * @param valor valor a actualizar
 */
void Encoder::swapValue(int *valor)
{
  int reading = read();
  // Giramos horario o antihorario
  if (reading == 2 || reading == 8)
  {
    if (*valor == 0)
    {
      *valor = 1;
    }
    else if (*valor == 1)
    {
      *valor = 0;
    }
  }
}

/**
 * @return true if change
 */
bool Encoder::swapValue(bool *valor)
{
  int reading = read();
  // Giramos horario o antihorario
  if (reading == 2 || reading == 8)
  {
    *valor = !(*valor);
    return true;
  }
  return false;
}

/**
 * @brief Altera un valor entero un incremento delta.
 *
 * Incrementa (antihorario) o decrementa (horario) un
 * valor dado, un delta determinado.
 *
 * @param valor valor a actualizar
 * @param delta incremento, por defecto: 1
 * @return true if change
 */
bool Encoder::updateValue(int *valor, int delta)
{
  int reading = read();
  // Giramos horario (incremento)
  if (reading == 8)
  {
    *valor = *valor - delta;
    return true;
    // Giramos antihorario (decremento)
  }
  else if (reading == 2)
  {
    *valor = *valor + delta;
    return true;
  }
  return false;
}

void Encoder::updateValue(float *valor, float delta)
{
  int reading = read();
  // Giramos horario (incremento)
  if (reading == 8)
  {
    *valor = *valor - delta;
    // Giramos antihorario (decremento)
  }
  else if (reading == 2)
  {
    *valor = *valor + delta;
  }
}

/**
 * @brief Lee la señal emitida al pulsar el encoder
 *
 * @return true cuando se pulsa
 * @return false si no se ha pulsado
 */
bool Encoder::readButton()
{
  if (digitalRead(_pulsador) != 1)
  {
    if (!_flag)
    {
      _tiempo = millis();
      _flag = true;
    }
    while (digitalRead(_pulsador) == 0)
    {
      if (millis() - _tiempo > 300)
      {
        _flag = false;
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief Lee el giro del knob del encoder.
 *
 * @return int giro antihorario: 8, giro horario: 2
 */
int Encoder::read()
{
  static int _pos = 0;
  tick();
  int _newPos = getPosition();

  // Giramos antihorario (Subimos en el menu)
  if (_pos > _newPos)
  {
    _pos = _newPos;
    return 8;
  }
  // Giramos horario (Subimos en el menu)
  else if (_pos < _newPos)
  {
    _pos = _newPos;
    return 2;
  }
  // Pulsamos (Modificamos valor)
  if (readButton())
  {
    return 5;
  }
  return 0;
}

bool Encoder::buttonHasBeenPressed(void)
{
  bool tmp = _buttonPressedFlag;
  _buttonPressedFlag = false;
  return tmp;
}

/**
 * ISR
 */
static void _buttonPressed(void)
{
  if (_buttonPressedTimestamp + 300 < millis())
  {
    _buttonPressedTimestamp = millis();
    _buttonPressedFlag = true;
  }
}
