# Reespirator Docs - Manual de montaje 

Este repositorio pretende documentar y organizar la forma de construcción del Reespirator 23, un respirador open-source de bajo coste basado en el sistema de ventilación mecánica Jackson-Rees, para todas aquellas personas, organizaciones o empresas que quieran fabricarlo.

ESTE DOCUMENTO ESTÁ EN ELABORACIÓN.

A collection of resources for Reespirator, an open-source low-cost Jackson-Rees-based mechanical ventilator.

## Disclaimer
*Recuerde que un respirador es un dispositivo médico que sólo puede ser utilizado por personal cualificado y que un mal respirador o un respirador mal utilizado puede matar.*

La presente documentación NO PERMITE CONSTRUIR UN RESPIRADOR FINAL, sólo se publica para que se pueda fabricar PROTOTPOS para investigación, hoy 5 de abril no se ha logrado aún una validación de la Agencia Española del Medicamento, si esto cambiara se cambiará este texto.


## Info
*¿Qué es Reespirator 23?*

El dispositivo Reespirator 23 es un sistema respirador de emergencia con elementos disponibles por la mayoría de las personas en cualquier parte del mundo, de rápida construcción y con la capacidad para mantener constantes ventilatorias aceptables en un paciente afecto de Síndrome de Distrés Respiratorio Agudo o SDRA.

## Primeros pasos
Antes de montar un respirador lea toda la documentación posible e infórmese bien.


## [Estructura básica](https://gitlab.com/reesistencia/reespirator-doc/-/blob/master/CASE.md)
Reespirator 23 consta de una caja diseñada para fabricarse mediante corte láser que contiene casi todos elementos del respirador en su interior.

En el prototipo actual las piezas del prototipo se han diseñado para su corte por láser en metacrilato.

## Sistema neumático
Basado en un sistema Jackson-Rees 

## Mecánica
El sistema mecánico pretende realizar los movimientos necesarios para realizar las maniobras de inspiración y espiración forzada del paciente mediante elementos mecánicos sustituyendo al personal humano que utilizaría el sistema de ventilación.

## Electrónica
La electrónica de control gestiona el movimiento del motor y los sensores que permiten realizar un control de lazo cerrado automatizado del sistema.
Además de la electrónica de control se emplea una electrónica adicional como interfaz de usuario que permite monitorizar diferentes señales del respirador y modificar en tiempo real diferentes configuraciones del mismo.

## Firmware
El sistema de control necesita ser programado con un firmware que permita hacer funcionar el dispositivo. Dicho programa se ha realizado conforme a las especificaciones de los especialistas médicos para realizar las funciones para las que el dispositivo fue diseñado.

## Usage

|              Purpose              |          File          |
| --------------------------------- | ---------------------- |
| Technical documentation (Spanish) | technical_specs_es.pdf |
| Hardware assembly                 | assembly.x_t           |

## Source code

|         Purpose         |                                      Repository                                      |
| ----------------------- | ------------------------------------------------------------------------------------ |
| Human-Machine Interface | [reespirator-beagle-touch](https://gitlab.com/reesistencia/reespirator-beagle-touch) |
| Ventilation Control     | [reespirator-firmware](https://gitlab.com/reesistencia/reespirator)                  |
