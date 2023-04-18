Nuevas versiones de la placa y del sw
=====================================
En este directorio encontraréis los ficheros del diseño realizado el curso 2022/23.

Básicamente, el cambio fundamental respecto al curso pasado es el valor (y el nombre) de las resistencias de la adaptación analógica, para ajustar al nuevo valor de la NTC utilizada (con un valor de B diferente de la de cursos anteriores). Igualmente, se han cambiado los valores de la tabla precalculada de temperatura en función del valor de ADC, para ajustar la nueva recta. Los cambios son pequeños, pero significativos.

A modo de resumen:
  - **placa2caras_23.brd**: trazado de pistas del diseño
  - **placa2caras_23.sch**: esquema del diseño realizado
  - **placa2caras_CTO4_2023.json**: trazado de pistas definitivo, en EasyEDA, con los logos y demás.
  - **PBL_CAL.INO**: programa para calibrar la placa
  - ++PBL.INO / PBL.h**: programa y librería para programar finalmente la placa


**Muy Importante: recuerda que para poder programar la placa deberás seguir los pasos que se indican en el directorio [https://github.com/maperales/EGEN/tree/master/ENERGIA]**
