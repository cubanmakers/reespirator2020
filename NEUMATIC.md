## Sistema neumático
Basado en un sistema [Jackson-Rees](https://en.wikipedia.org/wiki/Breathing_circuit), **Reespirator** es un respirador que además del mencionado sistema médico Jackson-Rees utiliza una serie de elementos neumáticos utilizados para entubar al paciente y para controlar sus flujos de respiración inspiratorios y espiratorios.

![Sistema Jakson-Rees](https://gitlab.com/reesistencia/reespirator-doc/-/raw/master/images/image005.png "Sistema Jackson-Rees")


![Esquema neumático](https://gitlab.com/reesistencia/reespirator-doc/-/raw/master/images/neumatic.png "Esquema neumático")

El circuito neumático completo está compuesto por tres secciones:
* Circuito de inspiración, resaltado en rojo en el diagrama
* Circuito de paciente, resaltado en verde en el diagrama
* Circuito de espiración, resaltado en azul en el diagrama

El circuito de inspiración (rojo) está compuesto por los siguientes elementos:
Línea de entrada de aire+O2 (1) proporciona el gas que respira el paciente. Deberá proporcionar un caudal en exceso sobre el caudal medio programando. La mezcla se realizará de forma externa al sistema, dependiendo de las capacidades de cada hospital:
En caso de que sólo exista una botella de oxígeno, se podría hacer una mezcla usando una válvula de venturi
En caso de que existan líneas separadas de oxígeno y aire, se podrá hacer una mezcla con válvulas y rotámetros para controlar la proporción de mezcla.
Balón del Mapleson o Jackson Rees (2) es accionado por el mecanismo motorizado y leva durante el ciclo de inspiración. Durante el ciclo de espiración la leva vuelve a posición de reposo para permitir que la línea de entrada (1) rellene el balón.

El circuito de inspiración (rojo) se comunica con el circuito de paciente (verde) por medio de la válvula anti-retorno (3).

El circuito de paciente (verde) está compuesto por los siguientes elementos:
Válvula de alivio de presión (4) o de seguridad: protege al paciente de sobrepresiones que pudieran suceder en el circuito, por un comportamiento incorrecto del respirador o por espasmos u otros movimientos causados por el propio paciente durante el ciclo de inspiración. La normativa indica que esta válvula de seguridad debe ser menor de 80 cmH2O, y lógicamente ha de ser mayor que la presión inspiratoria máxima que se desee que tenga el sistema, que típicamente rondará los 40 cmH2O.
Bloque de sensor (5): proporciona una medida de caudal y de presión en el circuito de paciente. Su cableado de medida se conecta a la caja del respirador mediante un conector Estará conectado a la caja del respirador a un terminal de conexión de los sensores (6). La medida de caudal se realiza mediante el método de placa orificio. Se mide la pérdida caída de presión del flujo del aire al atravesar un orificio de características conocidas. Se utiliza un sensor de presión diferencial que mide la diferencia de presiones, y también un sensor manométrico (o gauge) que proporciona una medida de la presión. El uso de estos sensores de presión para medir el caudal tiene como principales ventajas su reducido coste y alta disponibilidad en comparación con sensores de tipo caudalímetro. Inicialmente se contemplan dos opciones, en cuanto a la forma en que se realiza la medida de caudal:
Por placa orificio. Se mide la pérdida caída de presión del flujo del aire al atravesar un orificio de características conocidas. La conexión de este punto a la caja del respirador se puede realizar por medio de dos tubos, estando los sensores en el interior del respirador. Se necesita un sensor de presión diferencial que mida la dicha diferencia de presiones, y también un sensor manométrico (o gauge) que proporciona una medida de la presión. Como ventaja, se simplifica el número de elementos externos a la caja del respirador (dos tubos), y su coste y disponibilidad, dado que los sensores de presión son abundantes y baratos.
Caudalímetro tipo mass-flow. Produce una medida directa del caudal. Requiere la conexión de cables de alimentación y comunicación desde la caja del respirador hasta el sensor. Adicionalmente es necesario obtener una medida de presión que típicamente el sensor de caudal no proporciona. Esta medida se obtendría mediante un sensor manométrico o gauge, que podría estar situado junto al medidor de caudal (aprovechando que de todas maneras hay que llevar conexiones eléctricas hasta este punto) o podría estar en la caja del respirador, comunicado con el circuito de paciente mediante un tubo. 
Filtro (7): su función es purificar el aire tanto a la entrada como a la salida del paciente.  

El circuito de paciente (verde) se comunica con el circuito de espiración (azul) por medio de la válvula anti-retorno (8).

El circuito de espiración (azul) está compuesto por los siguientes elementos:
Electroválvula (9)
Válvula PEEP regulable (10): su objetivo es el mantenimiento de una presión mínima en el sistema durante la espiración para evitar el colapso pulmonar. Esta válvula se regula automáticamente para conseguir la presión PEEP establecida por el médico en el display del respirador. es de regulación automática mediante un sistema de electroválvulas, lo que permite al médico instaurarlo en el propio display.

Biocompatibilidad
Todos los elementos del circuito de inspiración (rojo) y circuito de paciente (verde), incluidas las válvulas anti-retorno (3) y (8) deben ser medical-grade, ya que el aire que circula por ellos es insuflado en los pulmones del paciente

El aire que circula los elementos del circuito de espiración (azul) nunca retorna a los pulmones del paciente gracias a la válvula anti-retorno (8), por lo cual no es necesario que sean medical-grade.

Reusabilidad
Los elementos del circuito de inspiración (rojo) se ven protegidos del aire espirado por el paciente por la válvula anti-retorno (3), por lo cual no se contaminarán y se pueden reutilizar.

Los elementos del circuito de espiración (azul) sí son contaminados, pero el aire en contacto con ellos nunca debería entrar en contacto con un nuevo paciente, gracias a la válvula anti-retorno (8), con lo cual son, también, reutilizables.

Los elementos del circuito de paciente (verde) son contaminados y su uso en un nuevo paciente sin previa esterilización no debería permitirse (salvo que la confianza en el filtro (7) sea plena). El bloque sensor y sus sensores también se contaminan y deberán ser sustituidos para cada nuevo paciente. Si se opta por una opción de sensores en la que dichos sensores están dentro de la caja del respirador, pero conectados por tubo(s) al circuito de paciente,  estos sensores, siendo estrictos, también deberían ser reemplazado o esterilizados.
