# Reespirator 2020 Docs

Este repositorio pretende documentar y organizar los pasos para fabricar prototipos de  **Reespirator-2020**, un respirador open-source basado en el sistema de ventilación mecánica Jackson-Rees, diseñado y mejorado a partir de los prototipos elaborados por el equipo de Reesistencia Tem para todas aquellas personas, organizaciones o empresas que quieran fabricarlo en cualquier parte del mundo.  


> ESTA DOCUMENTACIÓN ESTÁ EN ELABORACIÓN, COMPRUEBE REGULARMENTE LOS CAMBIOS, LAS PRIMERAS VERSIONES PUBLICADAS ESTÁN DESACTUALIZAS. 



## Disclaimer
*Recuerde que un respirador es un dispositivo médico que sólo puede ser utilizado por personal cualificado y que un mal respirador o un respirador mal utilizado puede matar.*

La presente documentación **NO PERMITE CONSTRUIR UN RESPIRADOR FINAL**, sólo se publica para que se pueda fabricar PROTOTPOS para investigación. 

## Info
*¿Qué es Reespirator 2020?*

El dispositivo Reespirator 2020 es un sistema respirador de emergencia con elementos disponibles por la mayoría de las personas en cualquier parte del mundo, de rápida construcción y con la capacidad para mantener constantes ventilatorias aceptables en un paciente afecto de [Síndrome de Distrés Respiratorio Agudo](https://es.wikipedia.org/wiki/S%C3%ADndrome_de_dificultad_respiratoria_aguda) o SDRA.

Aunque su origen es España, debido a las regulaciones y validaciones necesarias para los productos, y aunque hemos superado varias pruebas preclínicas con animales, suponemos que este dispositivo nunca se llegará a fabricar masivamente en España, dónde afortunadamente lo peor de la crisis del COVID-19 parece que ya ha pasado (08/04/20); pero esperamos que nuestro diseño pueda ser útil en otros países. Aún así no nos damos por vencidos y seguiremos desarrollando el proyecto al menos en 2 versiones:

* Versión low cost (basada en Arduino y con caja de metacrilato, madera...)
* Versión pro (con un autómata PLC + un HMI y caja de chapa plegada en acero inoxidable)

![Reespirator](https://gitlab.com/reespirator/reespirator2020/-/raw/master/images/Reespirator-2020-redesign.jpg "Reespirator")


## Primeros pasos
Antes de montar un respirador lea toda la documentación posible e infórmese bien, si necesita alguna aclaración abra un Issue y lo corregiremos en cuanto podamos. Si crees que puedes mejorar el diseño o el código envíanos un Pull request.


## [Estructura básica](https://gitlab.com/reespirator/reespirator-doc/-/blob/master/CASE.md)
Reespirator 2020 consta de una caja diseñada para fabricarse mediante corte láser que contiene casi todos elementos del respirador en su interior. En el prototipo actual las piezas del prototipo se han diseñado para su corte por láser en metacrilato si bien la imagen anterior corresponde a la nueva evolución que podrá fabricarse también con chapa plegada.

## [Sistema neumático](https://gitlab.com/reespirator/reespirator-doc/-/blob/master/NEUMATIC.md)
Basado en un sistema Jackson-Rees, Reespirator 2020 utiliza una serie de válvulas, sensores de presión y caudal y tubuladuras para hacer llegar al aire a los pulmones del paciente.

## [Mecánica](https://gitlab.com/reespirator/reespirator-doc/-/blob/master/MECHANIC.md)
El sistema mecánico pretende realizar los movimientos necesarios para realizar las maniobras de inspiración y espiración forzada del paciente mediante elementos mecánicos sustituyendo al personal humano que utilizaría el sistema de ventilación.

## [Electrónica](https://gitlab.com/reespirator/reespirator-doc/-/blob/master/ELECTRONIC.md)
La electrónica de control gestiona el movimiento del motor y los sensores que permiten realizar un control de lazo cerrado automatizado del sistema.
Además de la electrónica de control se emplea una electrónica adicional como interfaz de usuario que permite monitorizar diferentes señales del respirador y modificar en tiempo real diferentes configuraciones del mismo.

## [Firmware](https://gitlab.com/reespirator/reespirator-doc/-/blob/master/FIRMWARE.md)
El sistema de control necesita ser programado con un firmware que permita hacer funcionar el dispositivo. Dicho programa se ha realizado conforme a las especificaciones de los especialistas médicos para realizar las funciones para las que el dispositivo fue diseñado.

## Historia y principales cambios de esta versión

El proyecto Reespirator2020 toma como punto de partida el proyecto Reespirator 23 (o 24) v3 de **Reesistencia Team** a partir del cual realizamos un fork.

En esta nueva versión se incluyen principalmente los siguientes cambios:

 - Revisión y reestructuración en profundidad del códido de Arduino para asegurar la robustez de funcionamiento en todos los supuestos.
 - La recuperación del interfaz básico con LCD de 20x04 y elementos sencillos de control (4 pulsadores y un encoder con pulsador).
 - Establecimiento y documentación de una interfaz de comunicación serie que permite la utilización de sistemas (en adelante llamados Display+) de visualización, control y conectividad, que pueden ser utilizados como accesorios para aportar mejor usabilidad al sistema.
 - Se trabaja para estandarizar y popularizar los sensores y electro-válvulas para utilizar partes (comerciales o diseñadas) posibles de conseguir con la situación de emergencia actual y a precios accesibles.

## Repositorio temporal de trabajo para el código de Reespirator2020

El siguiente repositorio se está utilizando como fork de trabajo para transformar el código de Respirator 23 (o 24) v3 (cuyo código se ha denominado 'batalla') en el código estable que se usará en Respirator 2020 de arduino, cuyo código se ha denominado ['retaguardia'](https://gitlab.com/reespirator-arduino).
