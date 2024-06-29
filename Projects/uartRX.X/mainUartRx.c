/*
 * File:   mainUartRx.c
 * Author: torre
 *
 * Created on 19 de diciembre de 2023, 03:22 PM
 */
#include <xc.h>
#pragma config FOSC = HS        // Oscilador de alta velocidad
#pragma config WDT = OFF        // Watchdog Timer desactivado
#pragma config LVP = ON        // Programación de bajo voltaje desactivada
#pragma config PBADEN = OFF     // Puerto B como E/S digitales
#define _XTAL_FREQ 20000000 //20MHz

void uartInit()
{
    //Configuración de Pines 
    TRISCbits.RC6 = 1; //TX como salida
    TRISCbits.RC7 = 1; //RX como entrada
    
    //Configuración de Velocidad de transmicion
    TXSTA = 0x24; //TX deshabilitada, USART modo asíncrono (sync = 0), BRGH = 1
    BAUDCONbits.BRG16 = 0; // 8 bit 
    SPBRG = 129; //BaudRate = 9600    
    //Habilitar el modulo UART y la recepción continua
    RCSTA = 0x90;

}

char readData()
{
    while(!RCIF);
    return RCREG;
}


void main(void) {
   
    TRISD = 0x00;
    uartInit();
    while(1)
    {
        PORTD = readData();
    }       
    return;
}
