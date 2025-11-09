#include "source.h"
#include "funciones.h"

int main(){
   configuracion();
   comparador();
   while(1){
      if(!(PORTB&1)){
	 delay_ms(20);
	 while(!(PORTB&1));
	 PORTB ^= (1<<2);
	 T2CON |= (1<<2);
	 }
      mensaje();
      }
   return 0;
}
