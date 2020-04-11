## Firmware Arduino

El firmware para el Arduino Mega está en el repositorio [reespirator-firmware](https://gitlab.com/reesistencia/reespirator)

Otro grupo de programadores está reorganizando y refactorizando el código para hacerlo más sólido:
[https://gitlab.com/reespirator-arduino/reespirator](https://gitlab.com/reespirator-arduino/reespirator)

Hay que tener en cuenta que para la versión con Arduino se han barajado al menos 3 configuraciones distintas:

* 1 LCD de 20 caracteres x 4 líneas y un encoder.
* 1 LCD de 20 caracteres x 4 líneas y cuatro encoders o 1 encoder y 4 botones.
* 1 Pantalla gráfica táctil con otro dispositivo externo como una beagle-bone, una Raspberry Pi o un portátil o PC de escritorio conectados por puerto serie.

El software para la Beagle-bone y la pantalla utilizadas en el prototipo Reespirator 23 fue programado en Python y está disponible en el repositorio [reespirator-beagle-touch](https://gitlab.com/reesistencia/reespirator-beagle-touch) 

En otros grupos de Telegram se ha logrado hacer funcionar este mismo código de visualización en un portátil y en una Raspberry Pi.

