***Este documento describe la electrónica basada en PLC. Si desea ver la versión para Arduino, está disponible en el siguiente enlace: https://gitlab.com/reespirator/reespirator2020/-/blob/master/ARDUINO-ELECTRONICS.md***

## Electrónica con PLC 
La electrónica de control gestiona el movimiento del motor y los sensores que permiten realizar un control de lazo cerrado automatizado del sistema. Además se emplea una electrónica adicional de interfaz de usuario que permite monitorizar diferentes señales del respirador y modificar en tiempo real diferentes configuraciones del mismo.

El diagrama de bloques funcionales y elementos electrónicos del sistema se muestra en la siguiente figura:
_PENDIENTE_

### PLC

Según este esquema podemos ver que el sistema electrónico está compuesto por un autómata SIEMENS Simatic S7-1200 CPU 1215 al que se conectan los sensores y actuadores del sistema. Opcionalmente se puede suministrar la misma CPU en su versión SAFETY CAT-IV/SIL 3 mejorando grandemente tiempo medio entre fallos (mtbf), que ya de por si es bajo.

![SIEMENS Simatic S7-1200](https://gitlab.com/reespirator/reespirator2020/-/raw/master/images/PLC-Simatic-S7.jpg "SIEMENS Simatic S7-1200")

### Display táctil

Dispone de un display táctil SIEMENS TP700, con las siguientes capacidades: registro de alarmas, histórico de datos, monitorización remota con gestión de usuario y password para evitar accionamientos no autorizados. El gestor de accesos indica en la pantalla si se está operando sobre la pantalla en remoto. Dispone de una memoria SD para almacenamiento de datos de alarmas y datos de trabajo.

![SIEMENS TP700](https://gitlab.com/reespirator/reespirator2020/-/raw/master/images/PLC-TP700.jpg "SIEMENS TP700")

### Etapa de alimentación:
El dispositivo está preparado para conectarse a la red eléctrica de 110-230V de corriente alterna y utiliza una fuente de alimentación principal de baja tensión de 24V de corriente continua capaz de suministrar al menos 15A. Para mantener su funcionamiento en caso de fallo de la alimentación debe emplearse un SAI o bien solicitar alimentación auxiliar de 24Vdc.

### Sistema de actuación y sensorización

* Se utilizarán motores NEMA, concretamente NEMA 24 que si bien no son tan comunes como los NEMA 23 dan un torque suficiente. En los prototipos hemos utilizado motores de 4,2N/m. En cualquier caso el uso de otro tipo de motores debe garantizar la suficiente presión sobre el globo del Jackson-Rees para producir el suficiente flujo ventilatorio.

![Nema 24](https://gitlab.com/reespirator/reespirator-doc/-/raw/master/images/Nema24.jpg "Motor Nema 24")

* Los motores NEMA se controlarán con un driver HSS57. Se ha elegido este modelo ya que puede controlar tanto el NEMA24 como motores más pequeños sin necesidad de cambiar todo el hardware.

![Esquema de conexión](https://gitlab.com/reespirator/reespirator-doc/-/raw/master/images/motor-driver.png "Esquema de conexión del driver y el motor paso a paso")

* Para monitorizar la posición inicial del sistema, se utilizará un sensor de efecto hall o un simple final de carrera, (aunque también se ha considerado la opción de un segundo sensor para evitar problemas).

* Electroválvula de 24V para el control de salida de aire del sistema neumático, (en el prototipo original se utilizaron 2 porque eran de un diámetro demasiado pequeño como para permitir un caudal apropiado).

* Sensor de caudal Sensirion SFM3300-AW para la medición del caudal en el espacio muerto del sistema de ventilación. Al ser una pieza que estará en contacto con el circuito de inspiración del paciente, se emplea un sensor homologado para aplicaciones médicas. (Si este modelo no estuviera disponible se pueden buscar sustitutos y con pequeñas modificaciones del código se podrían utilizar igualmente).

![Caudalímetro](https://gitlab.com/reespirator/reespirator-doc/-/raw/master/images/SFM3200-AW_t.webp "Caudalímetro")


* Sensor de presión diferencial para la diferencia de presión que existe entre el circuito inspiratorio y la presión ambiental. Se ha empleado el modelo ABPLANT001PG2A5 de Honeywell, que está homologado para aplicaciones médicas. (En versiones previas utilizamos 2 BME280 conectados por SPI). 
	
