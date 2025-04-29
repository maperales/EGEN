#include <msp430.h> 


/**
 * main.c
 */

int  OFFSET = -5;  //Variable de calibracion
//------------------------------

#include "constantes.h"

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
P2.6: LEDG
P2.7: LEDR
DIG:[p15, p14,p13, p24, p23, p22, p21, p20]
************************************************/



void Set_clk(void){
    BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;
    if (CALBC1_16MHZ != 0xFF) {
                __delay_cycles(100000);
                DCOCTL = 0x00;
                BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
                DCOCTL = CALDCO_16MHZ;
            }
    BCSCTL1 |= XT2OFF | DIVA_0;
    BCSCTL3 = XT2S_0 | LFXT1S_2 | XCAP_1;
}


char ciclo=0;
char numero=0;
int t=0;
int T;
char PER=20;
int TREF=210;
int Vin=0;
int DIG[3];
int BOT[]={ 0,0,0};
int Trep=0;

char Estado_Display=0;
char DC=9;


void saca_d(int num)    // Descompone un nº en 3 digitos y guarda la representación en DIG
{
  int i=0;
  if(num<0)
    {
      num=-num;
      DIG[2]=DISPL[18];
    }
  else
      {
      while(num>=100) {

    num-=100;
    i++;
  }   // Dividir entre 100 por restas sucesivas
  DIG[2]=DISPL[i];
      }
  i=0;
  while(num>=10){
    num-=10;
    i++;
  }      // Dividir entre 10 por restas sucesivas
  DIG[1]=DISPL[i]+0x80;
  DIG[0]=DISPL[num];  //Punto decimal en el 2Âº digito
}




int lee_ch(char canal){
    ADC10CTL0 &= ~ENC;                  //deshabilita el ADC
    ADC10CTL1&=(0x0fff);                //Borra canal anterior
    ADC10CTL1|=canal<<12;               //selecciona nuevo canal
    ADC10CTL0|= ENC;                    //Habilita el ADC
    ADC10CTL0|=ADC10SC;                 //Empieza la conversión
while(ADC10CTL1&ADC10BUSY);
return(ADC10MEM);                   //Devuelve valor leido
    }

int valor;

void lee_botones(void)
{
    valor=lee_ch(7);
    if(valor>480) //Mirar si BOT1 está apretado
    {
        BOT[2]++;
        if(valor>605) //Mirar si B1+B2
        {
            BOT[1]++;
            if(valor>640)
            {
                BOT[0]++; //Mirar si B1+B2+B3
            }
            else
            {
                BOT[0]=0;
            }
        }
        else
        {
            BOT[1]=0;
            if(valor>550)
            {
                BOT[0]++; //Mirar si B1+B3
            }
            else
            {
                BOT[0]=0;
            }
        }
    }
    else  //B1=0
    {
        BOT[2]=0;
        if(valor>320) //Mirar si B2
        {
            BOT[1]++;
            if(valor>420){
                BOT[0]++; //Mirar si B2+B3
            }
            else
            {
                BOT[0]=0;
            }
        }
        else
        {
            BOT[1]=0;
            if(valor>200)
            {
                BOT[0]++; //Mirar si B3
            }
            else
            {
                BOT[0]=0;
            }

        }
    }

}

char t_bot=0;
unsigned char bot_s=0;
int main(void)
{
    unsigned char idx;       // idx: 5MSB del dato (indice para interpolar)
    unsigned char resto;   // resto: 5LSB del dato
    int T;     // T: la que sale de la tabla
    int  Tlineal;

    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    Set_clk();

    P2DIR=0xFF;        // P2: Salida entero: a, b, d, e, f, LR, LV.
    P2OUT =0;           //Todo apagado
    P2SEL=0;
    P2SEL2=0;
    P1DIR=0x3F;        // P1: salidas para K1, K2, K3, g,c,dp.


    ADC10CTL0 &= ~ENC;      //deshabilita ADC
    ADC10CTL0 = ADC10ON | ADC10SHT_3 | REFON |REF2_5V |SREF_1; //enciende ADC, S/H lento, REF:2.5V, SIN INT
    ADC10CTL1 = CONSEQ_0 | ADC10SSEL_0 | ADC10DIV_7 | SHS_0 | INCH_0;
    //Modo simple, reloj ADC, sin subdivision, Disparo soft, Canal 0
    ADC10AE0 = BIT6+BIT7; //habilita los canales indicados
    ADC10CTL0 |= ENC; //Habilita el ADC
    TACTL= MC_1|TASSEL_2|ID_3; //2MHz
    TACCTL0=CCIE;
    TACCR0=10000;    //5ms
    TACCR1=9990;
    TACCTL1=CCIE;

    __bis_SR_register(GIE);


    while(1)
    {
        LPM0;
        P1OUT &=0Xf8; // ~(BIT1+BIT2+BIT0);
        P2OUT &=0xE0;  //borra pines 0 a 4
        P2OUT |=DIG[ciclo]&0x1F;
        P1OUT &=0xC7; //borra pines 3, 4, 5
        P1OUT |=(DIG[ciclo]&0xE0)>>2;
        P1OUT |=KK[ciclo];
        ciclo++;
        if (ciclo==3)
        {   // Si ya se ha pasado por los tres:
            ciclo=0;
            t++;   //cada 15ms
            lee_botones();
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
            else
            {
                Trep=0;
                if(!(BOT[1]))  //B2 no pulsado
                {
                    if(BOT[0]==BOT_PULS)   //B1 solo
                    {
                        if(TREF>0)TREF--;
                        Estado_Display=1;
                    }
                    if(BOT[0]>BOT_PULS_LARGA)  //B1 puls. larga
                    {
                        if(TREF>0)TREF--;
                        PER=5;
                        Estado_Display=1;
                    }

                    if(BOT[2]==BOT_PULS)   //B3 solo
                    {
                        if(TREF<500)TREF++;
                        Estado_Display=1;
                    }
                    if(BOT[2]>BOT_PULS_LARGA)  //B3 puls. larga
                    {
                        if(TREF<500)TREF++;
                        PER=5;
                        Estado_Display=1;
                    }
                }
                if(BOT[1]>=BOT_PULS)   //B2 pulsado
                {
                    if(BOT[0]==BOT_PULS && Estado_Display!=6)    //B1+B2: decrementa brillo
                    {
                        if(DC>1)DC--;                     // Decrementa brillo
                        TA0CCR1=DC*999;
                        Estado_Display=6;
                    }
                    else if(BOT[2]==BOT_PULS && Estado_Display!=6)    //B3+B2: incrementa brillo
                    {
                        if(DC<9)DC++;                     // Decrementa brillo
                        TA0CCR1=DC*999;
                        Estado_Display=6;
                    }
                    else if(BOT[1]>BOT_PULS_MUY_LARGA && (!(BOT[0]+BOT[2])))   //B2 puls muy larga (E2GITI)
                    {
                        if(Estado_Display<10) Estado_Display=10;
                        PER=70;
                    }
                    else if(BOT[1]==BOT_PULS)
                    {
                        Estado_Display=2; PER=70;
                    }
                }
            }
            if(t>=PER)
            {       // PER=20
                // CADA (20*3*5=300)ms se rehacen las medidas

                Vin+=lee_ch(6);  // Valor medido mÃ¡s error calculado
                Vin=Vin>>1;
                Vin=lee_ch(6);
                Vin=Vin-OFFSET;
                if(Vin<0)Vin=0;
                idx=Vin>>5;       // idx: 5MSB del dato (indice para interpolar)
                resto=Vin-(idx*32);   // resto: 5LSB del dato
                T=T_tab[idx];     // T: la que sale de la tabla
                // Tlineal: incremento sobre T (interp. lineal)
                Tlineal=((T_tab[idx+1]-T_tab[idx])*resto)>>5;
                T=T+Tlineal;

                if(T>(TREF+10))  P2OUT |=BIT7;     //Enciende LedV
                if(T<(TREF-5))   P2OUT &=~BIT7;    //Apaga LedV
                if(T>(TREF+5))   P2OUT  &=~BIT6;   //Apaga LedR
                if(T<(TREF-10))  P2OUT |=BIT6;     //Enciende LedR


                switch(Estado_Display)
                {  // Qué se debe mostrar por el display
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
                    DIG[0]=DISPL[DC];    // DC (entre 0 y 9)
                    break;
                case 10:   //E.2G
                    DIG[2]=DISPL[11]+0x80; ;     // E.
                    DIG[1]=DISPL[2];            // 2
                    DIG[0]=DISPL[19];            // G
                    Estado_Display=11;
                    break;

                case 11: // 2GI
                    DIG[2]=DISPL[2];    // 2
                    DIG[1]=DISPL[19];   // G
                    DIG[0]=DISPL[1];    // I
                    Estado_Display=12;
                    break;
                case 12:   //GIt
                    DIG[2]=DISPL[19];           // G
                    DIG[1]=DISPL[1];           // I
                    DIG[0]=DISPL[20];   // t
                    Estado_Display=13;
                    break;

                case 13:   //ItI.
                    DIG[2]=DISPL[1];           // I
                    DIG[1]=DISPL[20];           // t
                    DIG[0]=DISPL[1]+0x80; ;    // I
                    Estado_Display=10;
                    break;

                }
                t=0;
            }     //fin bucle PER
        }
    }    //fin ciclo
}    //Fin LooP





#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_5ms(void)
{
    LPM0_EXIT;

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void pwm_manual(void)
{
    P1OUT &=~(BIT1+BIT2+BIT0);
    TAIV=0;
}


