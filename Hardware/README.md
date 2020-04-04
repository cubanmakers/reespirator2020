# Especificaciones Hardware

- Tensión entrada 24Vdc.
- Tensión secundaria: 5V.
- Salida a clema a 3,3V.
- Salida de alimentación 5V gestionada.
- Tamaño: TBD


# Comunicación
- I2C:
  * Sensor caudal SFM3300
  * Sensor de presión diferencial ABPLANT
  * adaptador de nivel a 3,3V
- UART TTL para comunicación con agente externo de interfaz de usuario y otras features
  * adaptador de tension a 3,3V.
- SPI con 2 CS

# Entradas digitales
- Alarma driver motor con interrupción
- Final de carrera motor (inducción magnética) sn04-n
- Entrada digital de libre potencial para SAI externo
- 1 encoder

# Salidas
- Reset driver motor NC
- Control heater sensor
- Control de electroválvula (con regulación/proporcional o no) de salida (ON/OFF o PWM)
  * diametro superior a 15mm.
- Control de electroválvula (con regulación/proporcional o no) de entrada (ON/OFF o PWM). Rango médico. Rango presión de entrada: de 2 a 5bar.
  * diametro superior a 15mm.
- Driver motor (enable, dirección y posición)
- zumbador
- 2 salidas para LED externo

# Opcional
- Driver motor secundario
- 4 entradas de pulsador
- 1 encoder


