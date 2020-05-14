/*********************************************** 
CODIFICACION DE NUMEROS Y LETRAS EN 7SEGMENTOS, 
CON LA CONEXION DE LA PLACA
************************************************/
/*byte DISPL[]={
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

};*/

byte DISPL[]={
		0x7E,	//0
		0x60,	//1
		0xCE,	//2
		0xEA,	//3
		0xF0,	//4
		0xBA,	//5
		0xB6,	//6
		0x68,	//7
		0xFE,	//8
		0xF8,	//9
		0x84,	//10:r
		0x9E,	//11:E
		0x9C,	//12:F
		0x00,	//13: vacio
                0xA4,   //14: n        
                0xF4,   //15:H
                0x16,   //16:L
                0xFC,   //17:A
                0x80,    //18:-
                0xBE  //19:G

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
 const int T_tab[33]={0, 
19, 
39, 
58, 
76, 
93, 
110, 
126, 
141, 
156, 
171, 
186, 
200, 
214, 
229, 
243, 
256, 
270, 
284, 
298, 
312, 
326, 
341, 
355, 
370, 
385, 
400, 
415, 
431, 
448, 
465, 
482, 
500
};
/*********************************************** 
VECTOR CON LOS PINES DE LOS CATODOS COMUNES: 
K1=PIN 5, K2=PIN 3, K3=PIN 4
************************************************/

byte KK[]={3,4,5};

#define TREPOSO 3000     //TIEMPO PARA ENTRAR EN REPOSO
#define  BOT_PULS 5      //TIEMPO PARA DAR BOTON COMO PULSADO (5*15MS=75MS)
#define BOT_PULS_LARGA 60//TIEMPO PARA PULSACION LENTA: 60*15MS= 0.9S

