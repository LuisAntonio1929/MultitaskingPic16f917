#include <16f917.h>
#device *=16
#device adc = 10
#use delay(clock = 8M)

#fuses nowdt
#fuses intrc_io
#fuses mclr
#fuses nobrownout
#fuses noprotect
#fuses noput
#fuses nocpd
#fuses ieso
#fuses fcmen
#fuses nodebug

#byte ansel = 0x91
#byte trisa = 0x85
#byte portb = 0x06
#byte trisb = 0x86
#byte portd = 0x08
#byte trisd = 0x88
#byte PORTC = 0x07
#byte TRISC = 0x87

#byte ADCON0 = 0x1F
#byte ADCON1 = 0x9F
#byte CMCON0 = 0x9C
#byte ADRESH = 0x1E
#byte ADRESL = 0x9E

#byte CCP2CON = 0x1D
#byte CCPR2L = 0x1B
#byte CCPR2H = 0x1C

#BYTE INTCON = 0x0B              // Registro de control de interrupciones
#BYTE PIE1 = 0x8C                // Registro de habilitación de interrupciones perif?ricas
#byte PIR1 = 0x0C
#byte PIR2 = 0x0D
#BYTE T1CON = 0x10               // Registro de control del temporizador 1

#byte T2CON = 0x12 
#byte PR2 = 0x92

#BYTE OSCCON = 0x8F