# Reespirator Docs - Manual de montaje

Este fork pretende documentar y organizar la forma de construcción del Reespirator 24, un respirador open-source de bajo coste basado en el sistema de ventilación mecánica Jackson-Rees, para todas aquellas personas, organizaciones o empresas que quieran fabricarlo.

A collection of resources for Reespirator, an open-source low-cost Jackson-Rees-based mechanical ventilator.

## Disclaimer
Recuerde que un respirador es un dispositivo médico que sólo puede ser utilizado por personal cualificado y que un mal respirador o un respirador mal utilizado puede matar.


## Info
¿Qué es Reespirator 23?

El dispositivo Reespirator 23 es un sistema respirador de emergencia con elementos disponibles por la mayoría de las personas en cualquier parte del mundo, de rápida construcción y con la capacidad para mantener constantes ventilatorias aceptables en un paciente afecto de Síndrome de Distrés Respiratorio Agudo o SDRA.

## Primeros pasos
Antes de montar un respirador lea toda la documentación posible e infórmese bien.

## Estructura básica
Reespirator 23 consta de una caja diseñada para fabricarse mediante corte láser que contiene casi todos elementos del respirador en su interior.

Las siguientes piezas del prototipo se han diseñado para su corte por láser en metacrilato de 10mm de grosor.

**![](https://lh4.googleusercontent.com/Rw_BoGAOtlgW_iJPXKSboZ_phwh_bFgpRYRIgVJQMQPlqopViYdBvEJlTBs2Jf4IKGeqSFo7HWUwPOuHRUW-O--tx-CfoybJuYr24uFZXqtUsO-ckM-EhM07qhvl56rM1nOGuWrH)**

**![](https://lh4.googleusercontent.com/XCe4fOHAmTvzVQrEcwOv18ccI64T8sXgwTiUNa5SS0kmM8FAN4vYJbNEZREp6uOqvye0GBPQNNL9Yuw_O40Pl8xyd-r03B-fVv2P6H0wofnnRMHY7NDnA3H1W5ZAcZVEZ6bTvtv-)**

**![](https://lh4.googleusercontent.com/3ZPv7TCWPBBi96qQapIw5sOFxL2CvffsMk0U8JEKxL5zV0e5es2PmDdP0FSrVxt8wk4kMz0L58uvNUveCUNkZJtpVtMeNUkiAej620MWAFZfxeNr21v_8H6Lz915uK5yt0OwHZ9C)**

**![](https://lh5.googleusercontent.com/L0N-ppMmLpxlN2YfT_ebNa048y5cwsbxE-y0ux4FTQMNQguw-hpAd3it6jWYv3bRP5tOx8UMiXWH2vEL5eEWqprVB-hGC6kNWp1IdgWD_dvKk_cNLit71CTwUU0A7WFhHiiX_Uuk)**

**![](https://lh5.googleusercontent.com/qY0vFH0W5UO7bKFsUn1E3QBJMlAASbVJqcki84IhO8FfLQUUTGyaDjp1d42nQJRFyhInAHx5c47shrIzz-3Q36Fe0TTPA3Bz7DxSdVLYcbu9WS10ctSC5wvXHG88QQAmqDMajKSJ)**

**![](https://lh5.googleusercontent.com/sxTzoRf1EvIexqKSA2le70w-NmfiLCdZIIfZ6m3NQ3IuG_ttCmHNx8LSiZZVGH3QEF_B2VXYkNTGsDRU1eueFUbhjA4SeWEwXz6cke5gZY6GLZV-eu2RBdUg4ogrZrWsc48u-_NX)**

**![](https://lh6.googleusercontent.com/BNDNVwnBvkhSnpN9zf1XQfJKQQ2XQRJgPSk4vR61QYHcO6NS2HJpTwdGhKmdUkL0pAfWPgUAraw3OHokpWzF9R8yfl_ZC_MnOjLEagmBp__jl14xqvdkuucSgLVKQnQZ-452XtI4)**

**![](https://lh6.googleusercontent.com/nfbuPcVmvR7ehU4mSyaowDeSwp3DMSmCcAbxsTvxJY6zGiyzZ9BCN0xIdjvNYedU0xZ2TDdypSYlNdS7eWef8lLHNz4HiiHS6ZzIK9psJ0aNX4KvaYlDGsUBIznbhSj9n3xrDnWz)**

**![](https://lh6.googleusercontent.com/LlCSm-bFxqQt6LxwusWUtt2JN65otXJwxfJNZz3yvZopwRkAemfxm0JU9Sp1ehk1DP03boxx5sB7cDtSNFKZhuJvjWnxJuWts4H6KIQSPHmkeRcpszLSD3LPPiqnDD95E67EJMgD)**

**![](https://lh3.googleusercontent.com/xruP8yjz8uzkz0ZCEFlxYvH735SlxLY48w-1farFrBMoPoUWUwldtimaiQuycdZZZ0pSxTrzO_SajjRAxNKcw_vZyF7W3iCNSKQbXL5BgcsiVkOpEvMkkZRAxEmJDR-2S6EE4vgf)**

**![](https://lh6.googleusercontent.com/dhdhGPt7kWFuY6w82dX3QZBrO3eC6hOD1q7Yaf14-yLMN3yz7ofPO-w0ZQmLIwbdqoiMF6w1uzy0W5qdrDarwh5-mfR5U6mDl2fsKLTW85tEQi7qSAy5tx-1MFE-vKubh_peMuks)**

## Sistema neumático
Basado en un sistema Jackson-Rees 

## Mecánica
El sistema mecánico pretende realizar los movimientos necesarios para realizar las maniobras de inspiración y espiración forzada del paciente mediante elementos mecánicos sustituyendo al personal humano que utilizaría el sistema de ventilación.

## Electrónica
La electrónica de control gestiona el movimiento del motor y los sensores que permiten realizar un control de lazo cerrado automatizado del sistema. Además se emplea una electrónica adicional de interfaz de usuario que permite monitorizar diferentes señales del respirador y modificar en tiempo real diferentes configuraciones del mismo.


## Programación
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
