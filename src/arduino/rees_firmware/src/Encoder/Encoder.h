#ifndef ENCODER_H
#define ENCODER_H

#define LATCHSTATE 3

class Encoder
{
public:
  Encoder(int pin1, int pin2, int pulsador);
  int read();
  bool readButton();
  bool buttonHasBeenPressed(void);
  void swapValue(int *valor);
  bool swapValue(bool *valor);
  bool updateValue(int *valor, int delta = 1);
  void updateValue(float *valor, float delta = 1.0);
  long getPosition();
  int getDirection(); //0 = No rotation, 1 = Clockwise, -1 = Counter Clockwise
  void setPosition(long newPosition);
  void tick(void);

private:
  int _pin1, _pin2, _pulsador;
  volatile int _oldState;
  volatile long _position;        // Internal position (4 times _positionExt)
  volatile long _positionExt;     // External position
  volatile long _positionExtPrev; // External position (used only for direction checking)
  bool _flag;
  unsigned long _tiempo;
};

#endif // ENCODER_H
