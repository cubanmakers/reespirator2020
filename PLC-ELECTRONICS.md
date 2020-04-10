***Este documento describe la electrónica basada en PLC. Si desea ver la versión para Arduino, está disponible en el siguiente enlace: https://gitlab.com/reespirator/reespirator2020/-/blob/master/ARDUINO-ELECTRONICS.md***

## Electrónica
La electrónica de control gestiona el movimiento del motor y los sensores que permiten realizar un control de lazo cerrado automatizado del sistema. Además se emplea una electrónica adicional de interfaz de usuario que permite monitorizar diferentes señales del respirador y modificar en tiempo real diferentes configuraciones del mismo.

La electrónica de control está basada en un Arduino Mega y una serie de dispositivos sensores y actuadores conectados al mismo para realizar un sistema de control en lazo cerrado. Estamos trabajando también en una versión basada en un autómata o PLC que fundamentalmente ha permitido realizar una correcta modelización del sistema.

En el prototipo actual la conexión de los distintos elementos se ha realizado sobre una shield de prototipado o breakout pero se está diseñando también una shield específica con los elementos necesarios para un ensamblado rápido de toda la electrónica, de forma que sólo sea necesario conectar los elementos sensores y actuadores mediante conectores.

Actualmente, se está trabajando el diseño de un PCB específico que integre la diversa electrónica que, en el prototipo, se ha realizado mediante módulos externos. Este desarrollo se irá liberando en el repositorio https://gitlab.com/reesistencia/reespirator-hardware

El diagrama de bloques funcionales y elementos electrónicos del sistema se muestra en la siguiente figura:
_PENDIENTE_

##PLC##

Según este esquema podemos ver que el sistema electrónico está compuesto por un autómata SIEMENS Simatic S7-1200 CPU 1512 al que se conectan los sensores y actuadores del sistema. Opcionalmente se puede suministrar la misma CPU en su versión SAFETY CAT-IV mejorando grandemente tiempo medio entre fallos (mtbf), que ya de por si es bajo.

![SIEMENS Simatic S7-1200](https://gitlab.com/reespirator/reespirator2020/-/raw/master/images/PLC-Simatic-S7.jpg "SIEMENS Simatic S7-1200")

##Display táctil##

Dispone de un display táctil SIEMENS TP700, con las siguientes capacidades: registro de alarmas, histórico de datos, monitorización remota con gestión de usuario y password para evitar accionamientos no autorizados. El gestor de accesos indica en la pantalla si se está operando sobre la pantalla en remoto. Dispone de una memoria SD para almacenamiento de datos de alarmas y datos de trabajo.

![SIEMENS TP700](https://gitlab.com/reespirator/reespirator2020/-/raw/master/images/PLC-TP700.jpg "SIEMENS TP700")

## Etapa de alimentación:
El dispositivo está preparado para conectarse a la red eléctrica de 230Vac y utiliza una fuente de alimentación principal de baja tensión de 24V de corriente continua capaz de suministrar al menos 15A. Para mantener su funcionamiento en caso de fallo de la alimentación debe emplearse un SAI o bien solicitar alimentación auxiliar de 24Vdc.

## Sistema de actuación y sensorización

	* Se utilizarán motores NEMA, concretamente NEMA24.

	* Los motores NEMA se controlarán con un driver HSS57. Se ha elegido este modelo ya que puede controlar tanto el NEMA24 como motores más pequeños sin necesidad de cambiar todo el hardware.

	* Para monitorizar la posición inicial del sistema, se utilizará un sensor de efecto hall.

	* Electroválvula para el control de salida de aire del sistema neumático.

	* Sensor de caudal Sensirion SFM3300-AW para la medición del caudal en el espacio muerto del sistema de ventilación. Al ser una pieza que estará en contacto con el circuito de inspiración del paciente, se emplea un sensor homologado para aplicaciones médicas.

	* Sensor de presión diferencial para la diferencia de presión que existe entre el circuito inspiratorio y la presión ambiental. Se ha empleado el modelo ABPLANT001PG2A5 de Honeywell, que está homologado para aplicaciones médicas.

