Nuevas versiones de la placa y del sw
=====================================
En este directorio encontraréis los ficheros del diseño realizado el curso 2019/20. 
Como recordaréis, se ha cambiado el circuito de lectura de botones, realizando la lectura ahora como una señal analógica. Esto simplifica el programa, aclarando el manejo de los botones e independizándolo de las señales K1, K2, K3 lo que permite leerlos a la velocidad que se desee. El circuito de adaptación se mantiene como en el curso pasado (circuito 2).
Por otro lado, los ficheros para la placa se han realizado en Kicad a partir de la versión en Eagle, y se incluyen en un fichero ZIP que contiene todo lo necesario (espero) para poder hacer la placa. 
A modo de resumen:
  - **PBL_1920_KiKad.zip**: Carpeta comprimida con todos los ficheros para el desarrollo del prototipo
  - **Pbl.ino**: fichero Energia para programar el microcontrolador. Igual al del año pasado
  - **Pbl.h**: fichero de librería. Contiene la nueva tabla de valores. Éste sí ha cambiado
  - **PBL_CAL.ino**: fichero de calibración de la placa. Cambia porque incorpora en sí mismo la tabla de valores 

**Muy Importante: recuerda que para poder programar la placa deberás seguir los pasos que se indican en el directorio [https://github.com/maperales/EGEN/tree/master/ENERGIA]**

