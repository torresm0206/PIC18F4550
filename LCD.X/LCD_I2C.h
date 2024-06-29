/*
 * File:   LCD_I2C.h
 * Author: Jose Manuel Torres Rivera
 * Esta libreria permite la comunicacion con un LCD utilizando el protocolo I2C
 * Created on 01 de enero de 2023, 23:48
 */

#define I2C_BAUD       100000	//Change this value as needed 
#define I2C_MODULE_ADD 0x27		//I2C addapter Address, change this acording your device (this address works fine for )
#define WRITE          0x00
#define READ           0x01
#define RS             0b00000001   //Usar RS para enviar caracteres
#define RW             0b00000010   //Usar RW para Leer
#define ENABLE         0b00000100
#define BACKLIGHT      0b00001000

void I2C_Init()
{
    TRISBbits.TRISB0 = 1; //SDA
    TRISBbits.TRISB1 = 1; //SCL
    
    SSPCON1 = 0X28; //Habilita el I2C y en modo maestro
    SSPCON2 = 0x00;  //Valor por default
    SSPSTAT = 0x00;
    SSPADD = (_XTAL_FREQ /(4 * I2C_BAUD)) - 1;
}

void I2C_Start()
{
    SSPCON2bits.SEN = 1; //Envia la condición de inicio, se limpia por HW
    while(!PIR1bits.SSPIF);
    PIR1 = 0x00;
}

void I2C_Stop()
{
    SSPCON2bits.PEN = 1;
    while(!PIR1bits.SSPIF);
    PIR1 = 0x00;
}

void I2C_Write(unsigned char dato)
{
    SSPBUF = dato; //Cargamos el dato en el buffer
    //while(!SSPSTATbits.BF); //Espera a que la transiision se complete
    while(!PIR1bits.SSPIF);
    while(SSPCON2bits.ACKSTAT); //Espera el ACK 
    PIR1 = 0x00;
    
}

void LCD_Command( unsigned char command)
{
    I2C_Start();
    I2C_Write(I2C_MODULE_ADD<<1);
    
    //Enviamos los 4 bits mas significativos
    I2C_Write((command & 0xF0) | BACKLIGHT);
    I2C_Write(((command & 0xF0) | ENABLE) | BACKLIGHT);
    __delay_ms(1);
    I2C_Write((command & 0xF0) | BACKLIGHT);
    
    //Ahora los menos significativos
    I2C_Write((command << 4) | BACKLIGHT);
    I2C_Write(((command << 4) | BACKLIGHT) | ENABLE);
    __delay_ms(1);
    I2C_Write((command << 4) | BACKLIGHT);
    I2C_Stop();
    __delay_ms(5);
}

void LCD_Init()
{   
    //Secuancia estandar para inicializar LCD
    __delay_ms(50);
    LCD_Command(0x03);
    __delay_ms(5);
    LCD_Command(0x03);
    __delay_us(150);
    LCD_Command(0x03);
    __delay_ms(5);
    LCD_Command(0x02);
    
    //Secuencia preferida, se puede cambiar segun las necesidades
    LCD_Command(0x28); //4 bits, 2 lineas, matriz 5x8
    LCD_Command(0x0C); // Display encendido, cursor apagado
    LCD_Command(0x06); // Incremento automático del Cursor
    LCD_Command(0x01); // Limpiar el Display
    __delay_ms(5);
    LCD_Command(0x0F);
}

LCD_Data(unsigned char letra)
{
    I2C_Start();
    I2C_Write(I2C_MODULE_ADD<<1);
    
    //Enviamos los 4 bits mas significativos
    I2C_Write(((letra & 0xF0) | BACKLIGHT) | RS);
    I2C_Write((((letra & 0xF0) | ENABLE) | BACKLIGHT) | RS);
    __delay_ms(1);
    I2C_Write(((letra & 0xF0) | BACKLIGHT) | RS);
    
    //Ahora los menos significativos
    I2C_Write((((letra << 4)) | BACKLIGHT) | RS );
    I2C_Write((((letra << 4) | BACKLIGHT) | ENABLE) | RS);
    __delay_ms(1);
    I2C_Write(((letra << 4) | BACKLIGHT) | RS);
    I2C_Stop();
    __delay_ms(5);
}