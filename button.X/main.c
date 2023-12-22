/*
 * File:   main.c
 * Author: José Manuel Torres Rivera
 *
 * Created on 21 de diciembre de 2023, 11:56 PM
 * In this program a LED is turned ON if a push button is pressed
 *  */


#include <xc.h>

#pragma config FOSC = HS
#pragma config WDT = OFF
#pragma config PWRT = ON
#pragma config BOR = ON
#pragma config MCLRE = OFF
#pragma config PBADEN = OFF

#define _XTAL_FREQ 20000000
#define BOTON1 LATBbits.LATB4
#define LED1   LATDbits.LATD0

void pinConfig()
{
    TRISBbits.RB4 = 1;
    TRISDbits.RD0 = 0;
}

void main(void) {
    pinConfig();
    while(1)
    {
        LED1 = BOTON1;
    }
    return;
}
