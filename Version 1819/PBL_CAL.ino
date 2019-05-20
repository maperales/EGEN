/*DEFINICIÓN DEL OFFSET DE LA PLACA. 
 ESTE ES EL VALOR QUE HAY QUE CAMBIAR
*/
int OFFSET=-5;

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
		0x0A,	//r    10
		0x3B,	//E    11
		0x3A,	//F    12
		0x00,	//vacio13
                0x9E,   //H    14
                0x13,    //L   15
                0xBE,    //A   16
                0x08    //-    17

};
 byte P_2[]={8,9,10,11,12,13,19,18};
 int T_tab[32]={0, 
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
    DIG[2]=DISPL[17];
    digitalWrite(15,0);
    digitalWrite(14,1);
    
    }
    else{
    saca_d(V_OFF);
    DIG[2]=0;
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
