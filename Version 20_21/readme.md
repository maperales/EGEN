
Nuevas versiones de la placa y del sw
=====================================
En este directorio encontraréis los ficheros del diseño realizado el curso 2020/21. 
Como recordaréis, se ha cambiado el circuito de adaptación, usando ahora el llamado "circuito 4" desarrollado en la "tarea extra.Esto tiene una serie de
ventajas, como que se usa un único amplificador, y que éste está en modo amplificador no inversor, además de ahorrar una resistencia y simplificar el cálculo frente al circuito II. 
Por otro lado, se ha situado la NTC en la parte superior del divisor resistivo, para que el cambio de signo debido a usar un amplificador no inversor se compense. El efecto es que las ecuaciones son prácticamente iguales, y en cualquier caso al crecer la temperatura crece la tensión en el ADC. Lo único que habrá que cambiar, por tanto, es la tabla de valores de T en función de la tensión (fichero pbl.h). A modo de resumen:
  - **Placa2caras_CTO2_4.brd**: trazado de pistas del diseño
  - **Placa2caras_CTO2_4.sch**: esquema del diseño realizado
  - **Pbl.ino**: fichero Energia para programar el microcontrolador. Igual al del año pasado
  - **Pbl.h**: fichero de librería. Contiene la nueva tabla de valores. Éste sí ha cambiado
  - **PBL_CAL.ino**: fichero de calibración de la placa. Cambia porque incorpora en sí mismo la tabla de valores 

**Muy Importante: recuerda que para poder programar la placa deberás seguir los pasos que se indican en el directorio [https://github.com/maperales/EGEN/tree/master/ENERGIA]**
--
**Otra nota igual de importante: los ficheros de Eagle que se muestran aquí YA ESTÁN CORREGIDOS. Al fabricar la placa, sin embargo, se deslizó un fallo en la serigrafía y los valores de R2 y RD aparecen cambiados entre sí.** 
