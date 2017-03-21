/*********************************************** 
CODIFICACION DE NUMEROS Y LETRAS EN 7SEGMENTOS, 
CON LA CONEXION DE LA PLACA
************************************************/
byte DISPL[]={
		0xB7,	//0
		0x84,	//1
		0x2F,	//2
		0xAD,	//3
		0x9C,	//4
		0xB9,	//5
		0x9B,	//6
		0xA4,	//7
		0xBF,	//8
		0xBC,	//9
		0x0A,	//10:r
		0x3B,	//11:E
		0x3A,	//12:F
		0x00,	//13: vacio
                0x8A,   //14: n        
                0x9E,   //15:H
                0x13,   //16:L
                0xBE,   //17:A
                0x08,    //18:-
                0xB3  //19:G

};

/*********************************************** 
VECTOR CON LAS DIRECCIONES DE LOS PINES DEL P2,
ORDENADAS, PARA USARLO DE MANERA ITERATIVA
************************************************/
 byte P_2[]={8,9,10,11,12,13,19,18};

/*********************************************** 
TABLA DE 32 COEFICIENTES (5BITS) CALCULADA EN 
MATLAB, PARA PASAR DE MEDIDA DEL ADC (0..1024) 
A TEMPERATURA*10 (0..500)
************************************************/
 int T_tab[32]={0,
8, 
29, 
49, 
68, 
86, 
104, 
121, 
137, 
153, 
168, 
183, 
198, 
213, 
228, 
242, 
257, 
271, 
285, 
300, 
314, 
329, 
344, 
359, 
374, 
390, 
406, 
422, 
439, 
456, 
474, 
492, 
};

/*********************************************** 
VECTOR CON LOS PINES DE LOS CATODOS COMUNES: 
K1=PIN 5, K2=PIN 3, K3=PIN 4
************************************************/

byte KK[]={4,3,5};

#define TREPOSO 3000     //TIEMPO PARA ENTRAR EN REPOSO
#define  BOT_PULS 5      //TIEMPO PARA DAR BOTON COMO PULSADO (5*15MS=75MS)
#define BOT_PULS_LARGA 60//TIEMPO PARA PULSACION LENTA: 60*15MS= 0.9S

