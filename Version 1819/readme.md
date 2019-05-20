Nuevas versiones de la placa y del sw
=====================================
En este directorio encontraréis los ficheros del diseño realizado el curso 2018/19. 
Como recordaréis, se ha cambiado el circuito de adaptación, usando ahora el llamado "circuito 2" en los apuntes. Esto tiene una serie de
ventajas, como que se usa un único amplificador, y que éste está en modo amplificador no inversor. El inconveniente fundamental
es que necesita una resistencia más. 
Por otro lado, se ha situado la NTC en la parte superior del divisor resistivo, para que el cambio de signo debido a usar un amplificador no inversor se compense. El efecto es que las ecuaciones son prácticamente iguales, y en cualquier caso al crecer la temperatura crece la tensión en el ADC. Lo único que habrá que cambiar, por tanto, es la tabla de valores de T en función de la tensión (fichero pbl.h)


