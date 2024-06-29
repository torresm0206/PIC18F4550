/*
 * File:   main.c
 * Author: José Manuel Torres Rivera
 *
 * Created on 20 de diciembre de 2023, 12:38 AM
 */


#include <xc.h>
#define _XTAL_FREQ     20000000
#include "LCD_I2C.h"

#pragma config FOSC = HS // Oscilador de alta velocidad (HS)
#pragma config WDT = OFF // Watchdog Timer desactivado
#pragma config PWRT = ON // Power-up Timer activado
#pragma config BOR = ON // Brown-out Reset activado
#pragma config LVP = OFF // Low Voltage Programming desactivado
#pragma config MCLRE = OFF // MCLR Pin activado, RE3 desactivado
#pragma config PBADEN = OFF

void main(void) {
    __delay_ms(3000);
    I2C_Init();
    LCD_Init();
    
    LCD_Data('T');
    LCD_Data('O');
    LCD_Data('C');
    LCD_Data('H');
    LCD_Data('I');
    LCD_Data('M');
    LCD_Data('I');
    LCD_Data('Z');
    LCD_Data('O');
    LCD_Data('L');
    LCD_Data('C');
    LCD_Data('O');
    
    
    while(1){
        SLEEP();
    }
    return;
}