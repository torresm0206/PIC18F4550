/*
 * File:   main.c
 * Author: torre
 *
 * Created on 21 de diciembre de 2023, 05:20 PM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

#pragma config FOSC = HS  //Porque se usa un cristal a >3.5MHz
#pragma config WDT = OFF
#pragma config PWRT = ON
#pragma config BOR = ON
#pragma config PBADEN = OFF
#pragma config MCLRE = OFF

#define LED1 LATDbits.LATD0

void pinConfig()
{
    TRISD = 0x00;
    LATD = 0x00;
}

void main(void) {
    
    pinConfig();
    
    while(1)
    {
        LED1 = 1;
        __delay_ms(500);
        LED1 = 0;
        __delay_ms(500);
    }
    return;
}
