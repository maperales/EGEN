/*DEFINICIÓN DEL OFFSET DE LA PLACA. 
 ESTE ES EL VALOR QUE HAY QUE CAMBIAR
*/
int OFFSET=-35; //-27;

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
		0xDC,	//9
		0x42,	//10:r
		0x5B,	//11:E
		0x5A,	//12:F
		0x00,	//13: vacio
                0xC2,   //14: n        
                0xD6,   //15:H
                0x13,   //16:L
                0xDE,   //17:A
                0x40,    //18:-
                0xC4  //19:+

};

 byte P_2[]={8,9,10,11,12,13,19,18};
const int T_tab[33]={0, 
15, 
36, 
55, 
74, 
91, 
108, 
124, 
140, 
156, 
171, 
185, 
200, 
214, 
229, 
243, 
257, 
271, 
285, 
299, 
314, 
328, 
343, 
357, 
372, 
387, 
403, 
419, 
435, 
452, 
469, 
487,  
500
};
byte KK[]={4,3,5};

byte ciclo=0;
byte numero=0;
int t=0;
int T;
int PER=20;
int TREF=210;
int Vin=0;
int DIG[3];
int BOT[]={0,0,0};
int Trep=0;
#define TREPOSO 1000
#define  BOT_PULS 10
#define BOT_PULS_LARGA 50
short muestra_ref=0;


int V_OFF;
void calibra(){
  int i;
int  medida=0;
  for(i=0;i<64;i++){
    delay(20);
    medida+=analogRead(A0)-OFFSET;
  }
  medida=medida>>6;
  V_OFF=medida-495;
  if (V_OFF>90 || V_OFF<-90){
    DIG[2]=DISPL[11];
    DIG[1]=DISPL[10];
    DIG[0]=DISPL[10];
     digitalWrite(15,1);
    digitalWrite(14,1);
    
    
  }
  else if(V_OFF<0){
    saca_d(-V_OFF);
    DIG[2]=DISPL[18];
    digitalWrite(15,0);
    digitalWrite(14,1);
    
    }
    else{
    saca_d(V_OFF);
    DIG[2]=DISPL[19];
       digitalWrite(15,1);
    digitalWrite(14,0);
    
    }
}
void setup()
{
  P2DIR=0xFF;
  P2SEL=0;P2SEL2=0;
  P1DIR=0xCE;
  P1OUT&=~BIT5;
  P1REN=BIT5;

  analogReference(INTERNAL2V5);
   
  // put your setup code here, to run once:
  calibra();
}






void saca_d(int num){
    int i=0;
  while(num>=100) {num-=100;i++;}
   DIG[2]=DISPL[i]; i=0;
   while(num>=10){num-=10;i++;}
   DIG[1]=DISPL[i]; DIG[0]=DISPL[num];
   
 }

void loop()
{
  delay(5);
P2OUT=DIG[ciclo];
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(KK[ciclo],HIGH);
  if(digitalRead(7)){
    BOT[ciclo]++; Trep=0;
  }
  else{BOT[ciclo]=0;
  }
  if(BOT[ciclo]==BOT_PULS){
    /*switch(ciclo){
      case 0:
      TREF--;
      muestra_ref=1;
      break;
      case 2:
      TREF++;
      muestra_ref=1;
      break;
      case 1:
      muestra_ref=2;
      //BOT[ciclo]=0;
      break;
    }*/
    calibra();
  }
  

      
 

  ciclo++;
  if (ciclo==3) ciclo=0;
}
