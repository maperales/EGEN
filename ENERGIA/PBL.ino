//COPIAR AQUÍ EL VALOR OBTENIDO EN LA CALIBRACIÓN
//------------------------------
int OFFSET=-9;
//------------------------------

#include "pbl.h"

void setup()         // Programada en Bajo Nivel para que quepa
{
  // for(int i=0;i<8;i++) pinMode(P_2[i],OUTPUT);
  P2DIR=0xFF;        // P2: Salida entero (display)
  P2SEL=0;
  P2SEL2=0;  
  /*pinMode(3,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(14,OUTPUT);
   pinMode(15,OUTPUT);
   pinMode(7,INPUT_PULLDOWN);*/
  P1DIR=0xDE;        // P1: salidas para K1, K2, K3, AA y CAL
  P1OUT&=~BIT5;      // P1.5: entrada con Pull_down
  P1REN=BIT5;
  analogReference(INTERNAL2V5); //Referencia del ADC: 2,5V
}

byte ciclo=0;
byte numero=0;
int t=0;
int T;
byte PER=20;
int TREF=210;
int Vin=0;
int DIG[3];
int BOT[]={
  0,0,0};
int Trep=0;

byte Estado_Display=0;
byte DC=5;


void saca_d(int num)    // Descompone un nº en 3 digitos y guarda la representación en DIG
{
  int i=0;
  while(num>=100) {
    num-=100;
    i++;
  }   // Dividir entre 100 por restas sucesivas
  DIG[2]=DISPL[i]; 
  i=0;
  while(num>=10){
    num-=10;
    i++;
  }      // Dividir entre 10 por restas sucesivas
  DIG[1]=DISPL[i]+0x40; 
  DIG[0]=DISPL[num];  //Punto decimal en el 2º digito
}

void loop()
{
  delay(DC);        //  Tiempo en ON (display anterior). entre 0 y 5ms
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  P2OUT=DIG[ciclo];  
  delay(5-DC);      // Tiempo en OFF, entre 0 y 5 ms
//  P1OUT|=BIT4;      // Comienzo ciclo: se usa para medir tiempo de actividad
  digitalWrite(KK[ciclo],HIGH);  //Enciendo el K correspondiente
  if(digitalRead(7)){            //Miro boton
    BOT[ciclo]++; 
    Trep=0;   
  }
  else{
    BOT[ciclo]=0;
  }

  ciclo++;
  if (ciclo==3){   // Si ya se ha pasado por los tres:
    ciclo=0;
    t++;
    if(!(BOT[0]+BOT[1]+BOT[2]))
    { 
      Estado_Display=0; 
      Trep++; 
      PER=20;
      if(Trep>TREPOSO)    // Si se supera el tiempo de reposo sin pulsaciones 
      {
        Estado_Display=5;    // Entra en reposo
        Trep=TREPOSO;  
      }
    }
    else{
      if(BOT[1]>=5*BOT_PULS_LARGA && (BOT[0]+BOT[2])==0)
      {
        if(Estado_Display<10) Estado_Display=10;
        PER=50;
      }
      if(BOT[2]==BOT_PULS)
      {
        if(BOT[1]>0){
          BOT[1]=1;
          if(DC<5)DC++;                    // Incrementa brillo
          Estado_Display=6;
        }
        else{
          TREF++;
          Estado_Display=1;
        }
      }
      if(BOT[0]==BOT_PULS)
      {
        if(BOT[1]>0){
          BOT[1]=1;
          if(DC>0)DC--;                     // Decrementa brillo
          Estado_Display=6;
        }
        else
        {
          TREF--;
          Estado_Display=1;
        }

      }
      if(BOT[1]==BOT_PULS && (BOT[0]+BOT[2])==0)
      {
        Estado_Display=2; PER=50;
      }
      if(BOT[1]==0){
        if(BOT[0]>=BOT_PULS_LARGA)
        {
          TREF--;
          Estado_Display=1;
          PER=5;
        }
        if(BOT[2]>=BOT_PULS_LARGA)
        {
          TREF++;
          Estado_Display=1;
          PER=5;
        }
      }
    }

    if(t>=PER){       // PER=20 
                      // CADA (20*3*5=300)ms se rehacen las medidas

      Vin=analogRead(A0)-OFFSET;  // Valor medido más error calculado
      int idx=Vin>>5;		// idx: 5MSB del dato (indice para interpolar)
      int resto=Vin-(idx*32);	// resto: 5LSB del dato
      int T=T_tab[idx];		// T: la que sale de la tabla
      // Tlineal: incremento sobre T (interp. lineal)
      int Tlineal=((T_tab[idx+1]-T_tab[idx])*resto)>>5;
      T=T+Tlineal;

      if(T>(TREF+20)) digitalWrite(15,HIGH);
      if(T<(TREF-5))  digitalWrite(15,LOW);
      if(T>(TREF+5))  digitalWrite(14,LOW);
      if(T<(TREF-20)) digitalWrite(14,HIGH);

      switch(Estado_Display){  // Qué se debe mostrar por el display
      case 0:            // 0: la temperatura actual
        saca_d(T);

        break;
      case 1:           // 1:la Temp. de referencia
        saca_d(TREF);

        Estado_Display=0;
        break;
      case 2:          // 2: mensaje REF
        DIG[2]=DISPL[10];
        DIG[1]=DISPL[11];
        DIG[0]=DISPL[12];
        Estado_Display=3;
        break;
      case 3:          // 3: Temperatura de Referencia
        saca_d(TREF);
        Estado_Display=2;

        break;
      case 5:           // 5: Apagar los displays
        DIG[2]=0;
        DIG[1]=0;
        DIG[0]=0;
        break;
      case 6:            // 6: mostrar intensidad luminosa
        DIG[2]=DISPL[1];     // I
        DIG[1]=DISPL[14];    // n
        DIG[0]=DISPL[DC];    // DC (entre 0 y 5)
        break; 
      case 10:
        DIG[2]=DISPL[11]+0x40; ;     // E.
        DIG[1]=DISPL[19];            // G
        DIG[0]=DISPL[11];            // E
        Estado_Display=11;
        break; 
      case 11:
        DIG[2]=DISPL[19];           // G
        DIG[1]=DISPL[11];           // E
        DIG[0]=DISPL[14]+0x40; ;    // n.
        Estado_Display=10;
        break; 


      }

      t=0;

    }     //fin bucle PER

  }    //fin ciclo
//  P1OUT&=~BIT4;// Fin ciclo: se usa para medir tiempo de actividad

}    //Fin LooP




