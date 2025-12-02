 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <util/delay.h>
#include <stdio.h>
// FILAS
#define FA_port PINB
#define FA_bit PB5
#define FB_port PINB
#define FB_bit PB4
#define FC_port PINB
#define FC_bit PB3
#define FD_port PINB
#define FD_bit PB2
// COLUMNAS
#define C1_port PORTB
#define C1_bit PB1
#define C2_port PORTB
#define C2_bit PB0
#define C3_port PORTD
#define C3_bit PD7
#define C4_port PORTD
#define C4_bit PD6

/*
    Main application
*/
void USART0_SendChar(char c);
void USART0_SendString(const char *str);

int main(void)
{
    SYSTEM_Initialize();
    bool FA=0;
    bool FB=0;
    bool FC=0;
    bool FD=0;
    int contador=0;
    bool flag = false; 
    char buffer[30];
    
    USART0_SendString("Hola Mundo\r\n");
    
    sprintf(buffer, "%d", 15);
    USART0_SendString(buffer);
    
    while(1)
    {
        
        C1_port &= ~(1<<C1_bit);// 0
        C2_port |= (1<<C2_bit);// 1
        C3_port |= (1<<C3_bit);// 1
        C4_port |= (1<<C4_bit);// 1
        _delay_ms(10);
        FC = FC_port & (1 << FC_bit);
        
        if(FC==false | contador == 1){
            PORTD |= (1<<PD5);
            _delay_ms(100);
            PORTD &= ~(1<<PD5);
            _delay_ms(100);
        }
        
        C1_port |= (1<<C1_bit);// 1
        C2_port &= ~(1<<C2_bit);// 0
        C3_port |= (1<<C3_bit);// 1
        C4_port |= (1<<C4_bit);// 1
        _delay_ms(10);
        FC = FC_port & (1 << FC_bit);
        
        if(FC==false |  contador == 2 ){
            PORTD |= (1<<PD5);
            _delay_ms(500);
            PORTD &= ~(1<<PD5);
            _delay_ms(500);
        }
        
        C1_port |= (1<<C1_bit);// 1
        C2_port |= (1<<C2_bit);// 0
        C3_port |= (1<<C3_bit);// 1
        C4_port &= ~(1<<C4_bit);// 1
        _delay_ms(10);
        FA = FA_port & (1 << FA_bit);
        
        if(FA==false & flag == false){
            flag = true;
            contador=contador + 1;
            //while(FA == false){
            //    FA = FA_port & (1 << FA_bit);
            //};
        }else{
            if(FA==true & flag ==true)
                flag =false;
        }
    }    
}


void USART0_SendChar(char c)
{
    // Espera a que el buffer esté vacío
    while (!(UCSR0A & (1 << UDRE0)));

    // Envía el dato
    UDR0 = c;
}

void USART0_SendString(const char *str)
{
    while (*str)
    {
        USART0_SendChar(*str);
        str++;
    }
}