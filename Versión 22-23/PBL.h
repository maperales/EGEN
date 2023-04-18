/*********************************************** 
CODIFICACION DE NUMEROS Y LETRAS EN 7SEGMENTOS, 
CON LA CONEXION DE LA PLACA
************************************************/
byte DISPL[]={
		0x9F,	//0
		0x84,	//1
		0x4F,	//2
		0xCD,	//3
		0xD4,	//4
		0xD9,	//5
		0xDB,	//6
		0x8C,	//7
		0xDF,	//8
		0xDD,	//9
		0x42,	//10:r
		0x5B,	//11:E
		0x5A,	//12:F
		0x00,	//13: vacio
                0xC2,   //14: n        
                0xD6,   //15:H
                0x13,   //16:L
                0xDE,   //17:A
                0x40,    //18:-
                0x9B  //19:G

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
 const int T_tab[33]={
-29, 
-5, 
16, 
37, 
56, 
75, 
93, 
110, 
127, 
144, 
160, 
176, 
192, 
207, 
222, 
238, 
253, 
268, 
283, 
298, 
314, 
329, 
345, 
361, 
377, 
393, 
410, 
427, 
444, 
462, 
480, 
499, 
519};
/*********************************************** 
VECTOR CON LOS PINES DE LOS CATODOS COMUNES: 
K1=PIN 5, K2=PIN 3, K3=PIN 4
************************************************/

byte KK[]={4,3,5};

#define TREPOSO 3000     //TIEMPO PARA ENTRAR EN REPOSO
#define  BOT_PULS 5      //TIEMPO PARA DAR BOTON COMO PULSADO (5*15MS=75MS)
#define BOT_PULS_LARGA 60//TIEMPO PARA PULSACION LENTA: 60*15MS= 0.9S

