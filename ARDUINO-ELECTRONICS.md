***Este documento describe la electrónica basada en Arduino. Si desea ver la versión para PLC, está disponible en el siguiente enlace: https://gitlab.com/reespirator/reespirator2020/-/blob/master/PLC-ELECTRONICS.md***

## Electrónica basada en Arduino
La electrónica de control gestiona el movimiento del motor y los sensores que permiten realizar un control de lazo cerrado automatizado del sistema. Además se emplea una electrónica adicional de interfaz de usuario que permite monitorizar diferentes señales del respirador y modificar en tiempo real diferentes configuraciones del mismo.

* En la versión de Arduino la electrónica de control está basada en un Arduino Mega y una serie de dispositivos sensores y actuadores conectados al mismo para realizar un sistema de control en lazo cerrado. 

* Estamos trabajando también en una versión basada en un autómata o PLC que fundamentalmente ha permitido realizar una correcta modelización del sistema.

En el prototipo actual la conexión de los distintos elementos se ha realizado sobre una shield de prototipado o breakout pero se está diseñando también una shield específica con los elementos necesarios para un ensamblado rápido de toda la electrónica, de forma que sólo sea necesario conectar los elementos sensores y actuadores mediante conectores.
En el prototipo actual la conexión de los distintos elementos se ha realizado sobre una shield de prototipado o breakout pero se está diseñando también una shield específica con los elementos necesarios para un ensamblado rápido de toda la electrónica, de forma que sólo sea necesario conectar los elementos sensores y actuadores mediante conectores.

Actualmente, se está trabajando el diseño de un PCB específico que integre la diversa electrónica que, en el prototipo, se ha realizado mediante módulos externos. Este desarrollo se irá liberando en el repositorio https://gitlab.com/reesistencia/reespirator-hardware

El diagrama de bloques funcionales y elementos electrónicos del sistema se muestra en la siguiente figura:
![Diagrama de bloques](https://gitlab.com/reesistencia/reespirator-doc/-/raw/master/images/diagrama-de-bloques.jpg "Diagrama de bloques")

Según este esquema podemos ver que el sistema electrónico está compuesto por:

## Microcontrolador: se ha empleado un Arduino Mega 2560 Rev3
![Arduino Mega](https://gitlab.com/reesistencia/reespirator-doc/-/raw/master/images/Arduino-mega.jpg "Arduino Mega")

## Etapa de alimentación:
	* La conexión a la red eléctrica se realizará mediante un conector IEC-C14 con fusible e interruptor.
	* La fuente de alimentación con entrada de 115-220V de corriente alterna de 50Hz/60Hz y salida 24Vdc.
	* Regulador step-down (LM2596, por ejemplo), con salida de 12Vdc.

{Insertar esquema de conexión}


## Interfaz hombre-máquina:

	* PC embebido BeagleBone Black, que dispone de un procesador AM325x 1GHz Cortex A8, con 4GB de memoria flash y 512MB de memoria RAM DDR3.

	* Pantalla TFT táctil de 7 pulgadas, con conexión HDMI, del fabricante ShareWave y resolución 800x480.

	* Para la señalización de alarmas, se dispondrá de un zumbador acústico activo.

> Insistimos en que este es el sistema utilizado en nuestro prototipo; pero se podría plantear la utilización de otros, aunque caso de ser aprobado este no tendría la validación necesaria en España.

## Sistema de actuación y sensorización

* Se utilizarán motores NEMA, concretamente NEMA 24 que si bien no son tan comunes como los NEMA 23 dan un par motor suficiente. En los prototipos hemos utilizado motores de 4 Newton metros. En cualquier caso el uso de otro tipo de motores debe garantizar la suficiente presión sobre el globo del Jackson-Rees para producir el suficiente flujo ventilatorio. (Se hicieron pruebas con nema 17 y no daban sufiente par motor, seguramente algunos nema 23 puedan ser suficiente).

![Nema 24](https://gitlab.com/reespirator/reespirator-doc/-/raw/master/images/Nema24.jpg "Motor Nema 24")

* Los motores NEMA se controlarán con un driver para motores paso a paso que proporcione la intensidad suficiente para comandar el motor elegido. El modelo utilizado en el prototipo está en el siguiente esquemma, el ZDM-2HA865. Se ha elegido este modelo ya que puede controlar tanto el NEMA24 como motores más pequeños sin necesidad de cambiar todo el hardware.

![Esquema de conexión](https://gitlab.com/reespirator/reespirator-doc/-/raw/master/images/motor-driver.png "Esquema de conexión del driver y el motor paso a paso")

* Para monitorizar la posición inicial del sistema, se utilizará un sensor de efecto hall o un simple final de carrera, (aunque también se ha considerado la opción de un segundo sensor para evitar problemas).

* Electroválvula de 24V para el control de salida de aire del sistema neumático, (en el prototipo original se utilizaron 2 porque eran de un diámetro demasiado pequeño como para permitir un caudal apropiado).

* Sensor de caudal Sensirion SFM3300-AW para la medición del caudal en el espacio muerto del sistema de ventilación. Al ser una pieza que estará en contacto con el circuito de inspiración del paciente, se emplea un sensor homologado para aplicaciones médicas. (Si este modelo no estuviera disponible se pueden buscar sustitutos y con pequeñas modificaciones del código se podrían utilizar igualmente).

![Caudalímetro](https://gitlab.com/reespirator/reespirator-doc/-/raw/master/images/SFM3200-AW_t.webp "Caudalímetro")


* Sensor de presión diferencial para la diferencia de presión que existe entre el circuito inspiratorio y la presión ambiental. Se ha empleado el modelo ABPLANT001PG2A5 de Honeywell, que está homologado para aplicaciones médicas. (En versiones previas utilizamos 2 BME280 conectados por SPI). 

En la tabla siguiente podemos ver el pinout utilizado en el prototipo:

| USO                   |PIN |
| --------------------- | -- |
| PIN_STEPPER_STEP      |  6 |
| PIN_STEPPER_DIRECTION |  7 | 
| PIN_STEPPER_EN STEP   |  8 |
| PIN_STEPPER_ALARM     |  3 | 
| PIN_BUZZ              | 11 |
| PIN_STEPPER_ENDSTOP   |  2 | 
| PIN_SOLENOID          | 39 |
| PIN_RELAY             | 25 | 
