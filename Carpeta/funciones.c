#include "source.h"

#define LCD_ENABLE_PIN  PIN_D3                                    ////
#define LCD_RS_PIN      PIN_D1                                    ////
#define LCD_RW_PIN      PIN_D2                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 

#include <lcd.c>

int cont1 = 0, cont2 = 0;

void configuracion(){
   //Configuracion del oscilador
   bit_set(OSCCON,6);bit_set(OSCCON,5);bit_set(OSCCON,4);	//8 MHz
   bit_clear(OSCCON,3);		//Device is running from the internal system clock
   bit_set(OSCCON,2);		//HFINTOSC is stable
   bit_set(OSCCON,0);		//Internal oscillator is used for system clock
   //Configuracion de los pines
   TRISD = 0x00;		//Puerto D (pines de la LCD) como salida
   TRISB = 0b00000001;		//RB0 como entrada y los demas como salida
   bit_clear(PORTB,2);		//RB2 en 0
   bit_clear(PORTB,3);		//RB3 en 0
   bit_set(ANSEL,0);		//RA0 como pin analogico
   bit_set(ANSEL,3);		//RA3 como pin analogico
   bit_set(TRISA,0);		//RA0 como entrada
   bit_set(TRISA,3);		//RA3 como entrada
   //Configuracion analogica
   bit_set(ADCON0,7);		//Right justified
   bit_clear(ADCON0,6);		//Voltage Reference VSS
   bit_clear(ADCON0,5);		//Voltage Reference VDD
   bit_clear(ADCON0,4);bit_clear(ADCON0,3);bit_clear(ADCON0,2);		//AN0 es el canal analogico
   bit_clear(ADCON1,6);bit_clear(ADCON1,5);bit_set(ADCON1,4);		//FOSC/8
   bit_set(ADCON0,0);		//A/D converter module is operating
   //Configuracion del comparador analógico
   bit_clear(CMCON0,4);		//C1 Output not inverted
   bit_set(CMCON0,2);bit_clear(CMCON0,1);bit_clear(CMCON0,0);		//Configuracion normal
   //Configuracion CCP2
   bit_set(CCP2CON,3);bit_clear(CCP2CON,2);bit_set(CCP2CON,1);bit_set(CCP2CON,0);//sets TMR1 and starts an A/D conversion
   //Para alcanzar una interrupcion cada 100ms = 4*4*(CCPR2)/(8MHz)
   //Se llega a que el valor de CCPR2 = 50000
   CCPR2H = 50000 >> 8;
   CCPR2L = 50000 & 0xFF;
   //Configuracion TMR1
   bit_set(T1CON,5);bit_clear(T1CON,4);		//1:4 Prescale Value
   bit_clear(T1CON,1);		//Internal clock (F OSC/4)
   bit_set(T1CON,0);		//Timer1 On
   //Configuracion TMR2
   T2CON = 0b01111011;		//Precaler 1:16 y postcaler 1:16
   //TMR2 debe llegar al match en 27.776ms repitiendose esto 18 veces lo que da 499.968ms (muy cercano a 500ms)
  //Esto se llega al aplicar la formula 0.027776 = 4*16*16*217/8M 
   PR2 = 216;	//Porque 217 = PR2 + 1  
   //Configuracion Interrupciones
   bit_set(INTCON,7);		//Enables all unmasked interrupts
   bit_set(INTCON,6);		//Enables all unmasked peripheral interrupts
   bit_set(PIE1,1);		//TMR2 Interrupt Enable bit
   //Inicializacion de la LCD
   lcd_init();			
   delay_ms(10);
}

void comparador(){
   lcd_gotoxy(1, 2);		//Posicionamiento en la segunda fila
   if(!((CMCON0>>6)&1)){
      lcd_putc("Bajar Tension   ");//Mensaje
      PORTB|=(1<<3);
      }else{
	 PORTB &=~(1<<3);
	 lcd_putc("Aumentar Tension");//Mensaje
      }
}

void mensaje(){ 
   if((PIR1>>6)&1){
      PIR1 &= ~(1<<6);
      int16 x = ADRESH;
      x = x<<8;
      x = x + ADRESL;
      x = (x>>1)-(x>>6)+(x>>8);//Equivalente a la operacion x*500/1023
      char u = x/100 + '0';
      int d = x%100;   
      lcd_gotoxy(1,1);
      lcd_putc("Tension: ");
      lcd_putc(u);
      lcd_putc('.');
      lcd_putc(d/10 + '0');
      lcd_putc(d%10+'0');
      lcd_putc(" V");
   }
   if((PIR2>>5)&1){
      PIR2 &= ~(1<<5);
      comparador();
   }
}
   
#int_timer2
void Int_TMR2(){
   cont1++;
   if(cont1==18){	//Repetir 18 veces para llegar a 500ms
      cont1=0;
      cont2++;
      PORTB ^= (1<<2);	//Parpadeo
      if(cont2==5){	
	 cont2=0;
	 T2CON &= ~(1<<2);
	 }
      }
}