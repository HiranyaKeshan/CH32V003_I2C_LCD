/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/25
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *USART Print debugging routine:
 *USART1_Tx(PD5).
 *This example demonstrates the use of USART1(PD5) as a print debug port output.
 *
 */

#include "debug.h"
#include "I2C_LCD.h"                //Or you can include <I2C_LCD.h> in ch32c00x_conf.h

int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();

    i2c_Begin(400000 , TxAdderss);   //Bound < 400kHz ; Default address -> 0x4E
    lcd_Begin(2 , 16);               //Row count ; Column count
    display_Off();
    clear();

    while(1){
        clear();
        display_On();
        bclight_On();
        set_Cursor(0, 0);
        convert("1602 LCD Demo by");
        set_Cursor(1,1);
        convert("Hiranya Keshan");
        Delay_Ms(3000);
        clear();

        set_Cursor(0, 5);
        convert("Letters");
        set_Cursor(1,0);
        convert("ABCDEFG  abcdefg");
        Delay_Ms(2000);
        clear();

        set_Cursor(0, 3);
        convert("And numbers");
        set_Cursor(1,3);
        convert("1234567890");
        Delay_Ms(2000);
        clear();

        set_Cursor(0, 2);
        convert("Also symbols");
        set_Cursor(1,0);
        convert(".,?;'[]-+=!@#$%&");
        Delay_Ms(2000);
        clear();

        set_Cursor(0, 1);
        convert("Want to blink?");
        Delay_Ms(2000);
        for (int i = 0; i < 10; ++i) {
            bclight_Off();
            Delay_Ms(100);
            bclight_On();
            Delay_Ms(100);
        }
        Delay_Ms(500);
        clear();

        set_Cursor(0, 1);
        convert("Display off in");
        Delay_Ms(1000);
        set_Cursor(1, 7);
        convert("05");
        Delay_Ms(1000);
        set_Cursor(1, 7);
        convert("04");
        Delay_Ms(1000);
        set_Cursor(1, 7);
        convert("03");
        Delay_Ms(1000);
        set_Cursor(1, 7);
        convert("02");
        Delay_Ms(1000);
        set_Cursor(1, 7);
        convert("01");
        Delay_Ms(1000);

        display_Off();
        Delay_Ms(1000);
        bclight_Off();
        Delay_Ms(5000);
    }
}
