/*
 * File:   main.c
 * Author: José Manuel Torres Rivera
 *
 * Created on 21 de diciembre de 2023, 11:56 PM
 * In this program a led is togle once a push button is pressed
 *  */


#include <xc.h>

#pragma config FOSC = HS
#pragma config WDT = OFF
#pragma config PWRT = ON
#pragma config BOR = ON
#pragma config MCLRE = OFF
#pragma config PBADEN = OFF

#define _XTAL_FREQ 20000000
#define BOTON1 PORTBbits.RB4
#define LED1   LATDbits.LATD0

unsigned char led1Status = 0;

void pinConfig()
{
    TRISBbits.TRISB4 = 1;
    TRISDbits.TRISD0 = 0;
    PORTDbits.RD0 = 0;
    LED1 = 0;
}

void main(void) {
    pinConfig();
    while(1)
    {
        if(BOTON1 == 0)
        {
            __delay_ms(300);
            LED1 = ~LED1;
        }
    }
        
    return;
}
