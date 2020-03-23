# Reespirator doc

A collection of resources for the Reespirator electronics.

If you want to access the **source files**, [click here](https://gitlab.com/coronavirusmakers/reespirator).

## Team

* Iván Torres - Diseño PCB y documentación (@itorres1)
* Antonio Ruiz - Diseño PCB (@antoniorn1)
* Joaquín Cubillo - BOM y documentación (@joaquincubillo)
* Fernando Peral (@fperal)

# Versión penúltima, se irá actualizando conforme avance el proyecto.


**Sistema electrónico Reespirator**

**1. Introducción**


La PCB se ha diseñado de manera que se pueda pinchar encima de un Arduino MEGA e integra en la propia PCB un display LCD, un encoder rotativo con pulsador y un buzzer, así como conectores para los diferentes módulos, que se describen a continuación.

Se ha separado el sistema en 4 grupos, que forman parte del Reespirator:

- Microcontrolador: se ha optado por un Arduino MEGA
- Interfaz hombre-máquina (completamente integrada en la placa)
  - Se utilizará un display de 20x4 con interfaz paralela. Opcionalmente se puede colocar una pantalla gráfica OLED de 128x64.
  - Para navegar por los menús y configurar parámetros se utilizará un encoder rotativo con pulsador.
  - Para avisar de alguna alarma se utilizará un zumbador activo.
- Sistema de actuación
  - Se utilizarán motores NEMA, concretamente NEMA17 o NEMA23 según el modelo de Reespirator a fabricar.
  - Los motores NEMA se controlarán con un driver TB6600. Se ha elegido este modelo ya que puede controlar tanto el NEMA23 como motores más pequeños sin necesidad de cambiar todo el hardware.
  - Para monitorizar la posición inicial del sistema, se utilizará un sensor de efecto hall o un final de carrera mecánico, según la disponibilidad. Se recomienda el uso de un sensor de efecto hall o de un sensor óptico ya que, al ser sin contacto, no hay problemas de ciclos de funcionamiento máximos.
- Sistema de potencia / eléctrico
  - Para alimentar todo el aparato se utilizará una fuente de alimentación a 24V con una salida igual o superior a 5A.
  - Para alimentar el Arduino se utilizará un regulador de tensión LM7812 integrado en la propia placa, con proteccion ante polaridad inversa. Se podrá conectar tanto con un screw-block terminal como con un jack de alimentación. El LM7812 se ha colocado tumbado y en contacto con la placa para mejorar la disipación térmica. Si se tienen problemas de disipación se puede sustituir por un convertidor DC/DC VXO78012, totalmente compatible en pines.
  - Se utilizará una seta para poder cortar la alimentación a la máquina en caso de emergencia.
  - La conexión a la red eléctrica se realizará mediante un conector IEC-C14 macho con fusible e interruptor.

**2. Conexión de los módulos**

Faltan imagenes.

**Sensor efecto hall / final de carrera.** 
-Se conectará al conector marcado como HALL en la parte trasera de la PCB, mediante un conector MOLEX 10-11-2033, aunque es compatible con otros headers con 2.54 mm de pitch (incluso se podrían usar cables Dupont o similares).

**Driver TB6600 + NEMA.**
-Señales de control: Se conectará al conector marcado como DRIVER0 en la parte trasera de la PCB, mediante un conector MOLEX 10-11-2043, aunque es compatible con otros headers con 2.54 mm de pitch (incluso se podrían usar cables Dupont o similares).
-Señales del motor: Conectados a un motor paso a paso. Los colores del cableado pueden cambiar según el motor utilizado, consultar el datasheet del motor antes de poner la máquina en marcha.
  - B- y B+: conectado a la fase B del motor paso a paso
  - A- y A+: conectado a la fase A del motor paso a paso
-Señales de potencia: se conectarán directamente desde la fuente de alimentación (V+ y V-) con cable rojo y negro (o del que se disponga) de sección AWG 20 / 0.5mm2 o superior (recomendado).
  - VCC:  conectado al positivo de la fuente de 24V
  - GND: conectado a la masa de la fuente de 24V

**3. Conexiones auxiliares**

La placa consta de puertos auxiliares para sensores analógicos (SENS0, SENS1, SENS2  y SENS3), así como puertos SPI e I2C (SPI0, SPI1, I2C0, I2C1).

**4. Conexionado de corriente alterna**

El conexionado de la parte de 230 VAC **se debe realizar con extremo cuidado**. Para las conexiones de alterna barajamos tres situaciones.

**Situación A con posibilidad de crimpar cable**

- Conector IEC-C14

**La toma de tierra irá con cable crimpado directo a la toma de tierra de la fuente de alimentación.**

Los otros dos terminales irán conectados a los terminales de entrada del interruptor, también con cable crimpado.

Una de las salidas del interruptor irá conectada a la entrada del pulsador de emergencia. También se conectará la salida del pulsador de emergencia a la entrada L de la fuente de alimentación.

La salida del interruptor restante irá conectada directamente a la entrada N de la fuente de alimentación.

**Situación B con posibilidad de soldar cable.**

En el caso de no contar con material para crimpar los terminales, se podrá optar por soldar la conexiones del conector e interruptor; ya que el pulsador de emergencia y la fuente de alimentación llevarán los cables atornillados.

**Situación C sin posibilidad de soldar/ crimpar cable.**

Si no se dispone de herramientas para soldar ni crimpar se cableará directamente a la fuente pasando solo la fase por la seta de emergencia.