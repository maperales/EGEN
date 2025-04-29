/*********************************************** 
CODIFICACION DE NUMEROS Y LETRAS EN 7SEGMENTOS, 
CON LA CONEXION DE LA PLACA
************************************************/
const char DISPL[]={
		0x5f,	//0
		0x44,	//1
		0x2F,	//2
		0x6D,	//3
		0x74,	//4
		0x79,	//5
		0x7b,	//6
		0x4c,	//7
		0x7f,	//8
		0x7C,	//9
		0x22,	//10:r
		0x3B,	//11:E
		0x3A,	//12:F
		0x00,	//13: vacio
                0x62,   //14: n
                0x76,   //15:H
                0x13,   //16:L
                0x7E,   //17:A
                0x20,    //18:-
                0x5b,  //19:G
                0x33    //20:t
};


/*********************************************** 
VECTOR CON LAS DIRECCIONES DE LOS PINES DEL P2,
ORDENADAS, PARA USARLO DE MANERA ITERATIVA
P1.3: g
P1.4: c
P1.5: dp
P2.0: d
P2.1: e
P2.2: b
P2.3: a
P2.4: f
P1.0: K1
P1.1: K2
P1.2: K3
************************************************/


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

char KK[]={BIT2,BIT1,BIT0};

#define TREPOSO 3000 //3000    //TIEMPO PARA ENTRAR EN REPOSO 15ms*3000=45s
#define BOT_PULS 4      //TIEMPO PARA DAR BOTON COMO PULSADO (4*15MS=60MS)
#define BOT_PULS_LARGA 70//TIEMPO PARA PULSACION LENTA: 70*15MS= 1.05 S
#define BOT_PULS_MUY_LARGA 340 //340*15ms=5s

