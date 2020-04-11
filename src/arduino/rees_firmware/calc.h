/** Calculation functions
 *
 * @file calc.h
 *
 *
 */
#ifndef CALC_H
#define CALC_H

#include "defaults.h"
#include "Arduino.h"
//#include <math.h>// o <cmath>

/**
 * @brief estima el volumen tidal en función de estatura y sexo, en ml.
 *
 * @param estatura en cm, del paciente
 * @param sexo 0: varón, 1: mujer, sexo del paciente
 * @return *volumenTidal volumen tidal estimado, en mililitros
 */
int estimateTidalVolume(int estatura, int sexo);

/**
 * @brief Refresca el WDT (Watch Dog Timer)
 */
void refreshWatchDogTimer();

#endif // CALC_H
