/*
 * File:   main.c
 * Author: torre
 *
 * Created on 23 de diciembre de 2023, 10:45 PM
 */


#include <xc.h>
#pragma config FOSC = HS  // Oscilador de alta velocidad externo
#pragma config WDT = OFF  // Desactiva el watchdog timer
#pragma config PWRT = ON  // Activa el Power-up Timer   -> Permite que la frecuencia del oscilador y el voltaje alcancen sus valores adecuados antes de ejecutar el programa (65ms es el valor nominal para el 18f4550)
#pragma config BOR = ON // Activa el Brown-out Reset (si VDD cae entonces el micro se reinicia para evitar malos funcionamientos)
#pragma config PBADEN = OFF // Desactiva el conversor A/D en los pines PORTB
#pragma config MCLRE = OFF // Para desactivar el mclr y usar el RE3 como I/O (si se activa, colocar un resistencia de pull-up para evitar reinicios no deseados)

#define _XTAL_FREQ 20000000
#define Rojo        LATDbits.LATD7
#define Amarillo    LATDbits.LATD6
#define Verde       LATDbits.LATD5

void pinConfig()
{
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    PORTD = 0x00;
}

void timer0Config()
{
    T0CONbits.T08BIT = 0;  //Timer0 a 16 bits
    T0CONbits.T0CS = 0; //se configura como temporizador
    //T0CONbits.PSA = 0; //se habilita el preescaler
    //T0CONbits.T0PS = 0x7; //preescaler de 256
    TMR0H = 0x3C;
    TMR0L = 0xC4;  //Limpiamos el registro del contador
}

void miDelay(unsigned int miliSegundos)
{
    unsigned int desbordes;
    desbordes = miliSegundos/10;
    while(desbordes)
    {
        T0CONbits.TMR0ON = 1;
        while(!INTCONbits.TMR0IF);
        INTCONbits.TMR0IF = 0;
        T0CONbits.TMR0ON = 0;
        TMR0H = 0x3C;
        TMR0L = 0xC4;
        desbordes--;
    }
}

void flashing(unsigned char luz)
{
    switch(luz)
    {
        case 'r':
            Rojo = 0;
            miDelay(500);
            Rojo = 1;
            miDelay(500);
            Rojo = 0;
            miDelay(500);
            Rojo = 1;
            miDelay(500);
            Rojo = 0;
            miDelay(500);
            Rojo = 1;
            miDelay(500);
            Rojo = 0;
            miDelay(500);
            break;
        case 'a':
            Amarillo = 0;
            miDelay(500);
            Amarillo = 1;
            miDelay(500);
            Amarillo = 0;
            miDelay(500);
            Amarillo = 1;
            miDelay(500);
            Amarillo = 0;
            miDelay(500);
            Amarillo = 1;
            miDelay(500);
            Amarillo = 0;
            miDelay(1000);
            break;
        case 'v':
            Verde = 0;
            miDelay(500);
            Verde = 1;
            miDelay(500);
            Verde = 0;
            miDelay(500);
            Verde = 1;
            miDelay(500);
            Verde = 0;
            miDelay(500);
            Verde = 1;
            miDelay(500);
            Verde = 0;
            miDelay(500);
            break;
        default:
            Amarillo = 0;
            miDelay(500);
            Amarillo = 1;
            miDelay(500);
            Amarillo = 0;
            miDelay(500);
            Amarillo = 1;
            miDelay(500);
            Amarillo = 0;
            miDelay(500);
            Amarillo = 1;
            miDelay(500);
            Amarillo = 0;
            miDelay(1000);    
    }
}

void semaforo()
{
    Rojo = 1;
    miDelay(10000);
    Rojo = 0;
    Verde = 1;
    miDelay(10000);
    Verde = 0;
    Amarillo = 1;
    miDelay(10000);
    flashing('a');
}
void main(void) {
    pinConfig();
    timer0Config();
    
    while(1)
    {
        semaforo();
    }
    return;
}