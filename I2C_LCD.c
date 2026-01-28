/********************************** (C) COPYRIGHT  *******************************
 * File Name          : I2C_LCD.c
 * Author             : Hiranya Keshan
 * Version            : V1.0.0
 * Date               : 2024/10/08
 * Description        : This file provides all the I2C LCD firmware functions.
 *                      Based on PCF8574 i2c controller.
 *                      I2C_LCD.c in Project -> Peripheral -> src
 *********************************************************************************/

#include <I2C_LCD.h>
#include <ch32v00x_i2c.h>
#include <ch32v00x_rcc.h>
#include <stdio.h>
#include <string.h>

dataTypeDef dataStructure = {0};
displayTypeDef displayStructure = {0};
entryTypeDef entryStructure = {0};

uint8_t colmax;
uint8_t rowmax;
uint8_t Txaddr;

/*********************************************************************
 * @fn      i2c_Begin
 *
 * @brief   Initializes the I2C peripheral with the specified clock speed and address.
 *          Configures the necessary GPIO pins and sets up the I2C parameters.
 *
 * @param   bound   - Clock speed for the I2C communication. Should be < 400kHz
 *          address - 7-bit address for the I2C peripheral. Default address -> 0x4E
 *
 * @return  None.
 */
void i2c_Begin(u32 bound, uint8_t address)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    I2C_InitSturcture.I2C_ClockSpeed = bound;
    I2C_InitSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitSturcture.I2C_OwnAddress1 = address;
    I2C_InitSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitSturcture );

    I2C_Cmd( I2C1, ENABLE );
}

/*********************************************************************
 * @fn      clear
 *
 * @brief   Clears the LCD display and returns the cursor to the home position.
 *
 * @param   None.
 *
 * @return  None.
 */
void clear(void)
{
    dataStructure.rs = Instruct_in;

    lcd_Write(0x01 , RESET);
    Delay_Ms(2);
}

/*********************************************************************
 * @fn      home
 *
 * @brief   Moves the cursor to the home position (upper-left corner).
 *
 * @param   None.
 *
 * @return  None.
 */
void home(void)
{
    dataStructure.rs = Instruct_in;

    lcd_Write(0x02 , RESET);
    Delay_Ms(2);
}

/*********************************************************************
 * @fn      display_On
 *
 * @brief   Turns on the LCD display. Combines display state, cursor state, and blink state.
 *
 * @param   None.
 *
 * @return  None.
 */
void display_On(void)
{
    dataStructure.rs = Instruct_in;
    displayStructure.disp_state = SET;

    uint8_t buf = 0x08;
    buf |= displayStructure.blink_state;
    buf |= displayStructure.cur_state << 1;
    buf |= displayStructure.disp_state << 2;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      display_Off
 *
 * @brief   Turns off the LCD display.
 *
 * @param   None.
 *
 * @return  None.
 */
void display_Off(void)
{
    dataStructure.rs = Instruct_in;
    displayStructure.disp_state = RESET;

    uint8_t buf = 0x08;
    buf |= displayStructure.blink_state;
    buf |= displayStructure.cur_state << 1;
    buf &= ~(1 << 2);

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      cursor_On
 *
 * @brief   Enables the cursor on the LCD display.
 *
 * @param   None.
 *
 * @return  None.
 */
void cursor_On(void)
{
    dataStructure.rs = Instruct_in;
    displayStructure.cur_state = SET;

    uint8_t buf = 0x08;
    buf |= displayStructure.blink_state;
    buf |= displayStructure.cur_state << 1;
    buf |= displayStructure.disp_state << 2;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      cursor_Off
 *
 * @brief   Disables the cursor on the LCD display.
 *
 * @param   None.
 *
 * @return  None.
 */
void cursor_Off(void)
{
    dataStructure.rs = Instruct_in;
    displayStructure.cur_state = RESET;

    uint8_t buf = 0x08;
    buf |= displayStructure.blink_state;
    buf &= ~(1 << 1);
    buf |= displayStructure.disp_state << 2;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      blink_On
 *
 * @brief   Enables the blinking cursor on the LCD display.
 *
 * @param   None.
 *
 * @return  None.
 */
void blink_On(void)
{
    dataStructure.rs = Instruct_in;
    displayStructure.blink_state = SET;

    uint8_t buf = 0x08;
    buf |= displayStructure.blink_state;
    buf |= displayStructure.cur_state << 1;
    buf |= displayStructure.disp_state << 2;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      blink_Off
 *
 * @brief   Disables the blinking cursor on the LCD display.
 *
 * @param   None.
 *
 * @return  None.
 */
void blink_Off(void)
{
    dataStructure.rs = Instruct_in;
    displayStructure.blink_state = RESET;

    uint8_t buf = 0x08;
    buf &= ~(1);
    buf |= displayStructure.cur_state << 1;
    buf |= displayStructure.disp_state << 2;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      entry_Right
 *
 * @brief   Sets the entry mode to move the cursor to the right after each character is written.
 *
 * @param   None.
 *
 * @return  None.
 */
void entry_Right(void)
{
    dataStructure.rs = Instruct_in;
    entryStructure.cur_dir = SET;

    uint8_t buf = 0x04;
    buf |= entryStructure.disp_shift;
    buf |= entryStructure.cur_dir << 1;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      entry_Left
 *
 * @brief   Sets the entry mode to move the cursor to the left after each character is written.
 *
 * @param   None.
 *
 * @return  None.
 */
void entry_Left(void)
{
    dataStructure.rs = Instruct_in;
    entryStructure.cur_dir = RESET;

    uint8_t buf = 0x04;
    buf |= entryStructure.disp_shift;
    buf &= ~(1 << 1);

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      display_Shift
 *
 * @brief   Enables display shifting, where the display shifts instead of the cursor moving.
 *
 * @param   None.
 *
 * @return  None.
 */
void display_Shift(void)
{
    dataStructure.rs = Instruct_in;
    entryStructure.disp_shift = SET;

    uint8_t buf = 0x04;
    buf |= entryStructure.disp_shift;
    buf |= entryStructure.cur_dir << 1;

    lcd_Write(buf , RESET);
    Delay_Ms(2);
}

/*********************************************************************
 * @fn      nodisplay_Shift
 *
 * @brief   Disables display shifting, so the cursor moves without shifting the display.
 *
 * @param   None.
 *
 * @return  None.
 */
void nodisplay_Shift(void)
{
    dataStructure.rs = Instruct_in;
    entryStructure.disp_shift = RESET;

    uint8_t buf = 0x04;
    buf &= ~(1);
    buf |= entryStructure.cur_dir << 1;

    lcd_Write(buf , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      shift
 *
 * @brief   Shifts the cursor to the right without changing the display.
 *
 * @param   None.
 *
 * @return  None.
 */
void shift(void)
{
    dataStructure.rs = Instruct_in;

    lcd_Write(0x14 , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      neg_Shift
 *
 * @brief   Shifts the cursor to the left without changing the display.
 *
 * @param   None.
 *
 * @return  None.
 */
void neg_Shift(void)
{
    dataStructure.rs = Instruct_in;

    lcd_Write(0x10 , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      shift_Disp
 *
 * @brief   Shifts the entire display to the right.
 *
 * @param   None.
 *
 * @return  None.
 */
void shift_Disp(void)
{
    dataStructure.rs = Instruct_in;

    lcd_Write(0x1c , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      negshift_Disp
 *
 * @brief   Shifts the entire display to the left.
 *
 * @param   None.
 *
 * @return  None.
 */
void negshift_Disp(void)
{
    dataStructure.rs = Instruct_in;

    lcd_Write(0x18 , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      bclight_On
 *
 * @brief   Turns on the LCD backlight.
 *
 * @param   None.
 *
 * @return  None.
 */
void bclight_On(void)
{
    dataStructure.rs = Instruct_in;
    dataStructure.Led = SET;

    lcd_Write(0x00 , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      bclight_Off
 *
 * @brief   Turns off the LCD backlight.
 *
 * @param   None.
 *
 * @return  None.
 */
void bclight_Off(void)
{
    dataStructure.rs = Instruct_in;
    dataStructure.Led = RESET;

    lcd_Write(0x00 , RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      lcd_Begin
 *
 * @brief   Initializes the LCD display with the specified row and column limits.
 *
 * @param   row_limit - Maximum number of rows the LCD can display.
 *          col_limit - Maximum number of columns the LCD can display.
 *
 * @return  None.
 */
void lcd_Begin(uint8_t row_limit , uint8_t col_limit)
{
    colmax = col_limit;
    rowmax = row_limit;

    uint8_t TextData[5] = { 30 , 30 , 30 , 20 , 40 };

    for (int i = 0 ; i < 5 ; i++)
    {
        lcd_Write(TextData[i], SET);
        Delay_Ms(5);
    }
    display_On();
    clear();
    entry_Right();
    home();
}

/*********************************************************************
 * @fn      convert
 *
 * @brief   Converts a string into individual characters and writes them to the LCD.
 *
 * @param   sentence - The string to be written to the LCD.
 *
 * @return  None.
 */
void convert(const char *sentence)
{
    dataStructure.rs = Data_in;

    for (int i = 0; i < strlen(sentence); i++) {
        lcd_Write((uint8_t)sentence[i], RESET);
    }
}

/*********************************************************************
 * @fn      set_Cursor
 *
 * @brief   Sets the cursor position to the specified row and column.
 *
 * @param   row - Row number (0-based).
 *          col - Column number (0-based).
 *
 * @return  None.
 */
void set_Cursor(uint8_t row , uint8_t col)
{
    home();

    uint8_t multi[4] = { 0x00 , 0x40 , 0x14 , 0x54 };
    dataStructure.rs = Instruct_in;

    if(col < colmax)
    {
        if(row < rowmax)
        {
            uint8_t buf = 0x80;
            buf |= multi[row] + col;

            lcd_Write(buf, RESET);
            Delay_Us(37);
        }
    }
}

/*********************************************************************
 * @fn      custom_Char
 *
 * @brief   Defines a custom character and stores it in the LCD's CGRAM.
 *          (Currently does not work properly.)
 *
 * @param   location - CGRAM location to store the custom character (0-7).
 *          charmap  - Array representing the character pixel pattern (8 bytes).
 *
 * @return  None.
 */
void custom_Char(uint8_t location, uint8_t charmap[]) {
    location &= 0x07;

    dataStructure.rs = Instruct_in;
    lcd_Write(0x40 | (location << 3), RESET);
    Delay_Us(37);

    dataStructure.rs = Data_in;
    for (int i = 0; i < 8; i++) {
        lcd_Write(charmap[i], RESET);
        Delay_Us(37);
    }

    dataStructure.rs = Instruct_in;
    lcd_Write(0x80, RESET);
    Delay_Us(37);
}

/*********************************************************************
 * @fn      i2c_Write
 *
 * @brief   Sends a byte of data to the LCD via the I2C interface.
 *
 * @param   packet - Data byte to be transmitted.
 *
 * @return  None.
 */
void i2c_Write(uint8_t packet )
{
    while( I2C_GetFlagStatus( I2C1, I2C_FLAG_BUSY ) != RESET );
    I2C_GenerateSTART( I2C1, ENABLE );
    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress(I2C1, TxAdderss, I2C_Direction_Transmitter);

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );
    if( I2C_GetFlagStatus( I2C1, I2C_FLAG_TXE ) !=  RESET )
    {
        Delay_Us(40);
        I2C_SendData( I2C1 , packet );
        while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));

    }

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) );
    I2C_GenerateSTOP( I2C1, ENABLE );
}

/*********************************************************************
 * @fn      lcd_Write
 *
 * @brief   Writes a byte to the LCD and manages the high and low nibbles.
 *
 * @param   packet - Data byte to be sent.
 *          init   - Flag indicating whether this is an initialization command.
 *
 * @return  None.
 */
void lcd_Write(uint8_t packet , uint8_t init )
{
    dataStructure.datapack = packet;

    dataStructure.E = SET;
    i2c_Write(high_Data());
    Delay_Us(1);

    dataStructure.E = RESET;
    i2c_Write(high_Data());

        if (!init)
        {
            Delay_Us(37);

            dataStructure.E = SET;
            i2c_Write(low_Data());
            Delay_Us(1);

            dataStructure.E = RESET;
            i2c_Write(low_Data());
        }
}

/*********************************************************************
 * @fn      low_Data
 *
 * @brief   Prepares the low nibble of the data byte for transmission over I2C.
 *
 * @param   None.
 *
 * @return  The low nibble of the data byte.
 */
uint8_t low_Data(void)
{

    uint8_t buf = dataStructure.rs;
    buf |= 0 << 1;
    buf |= dataStructure.E << 2;
    buf |= dataStructure.Led << 3;
    buf |= ((dataStructure.datapack & 0x0F) << 4);

    return buf;
}

/*********************************************************************
 * @fn      high_Data
 *
 * @brief   Prepares the high nibble of the data byte for transmission over I2C.
 *
 * @param   None.
 *
 * @return  The high nibble of the data byte.
 */
uint8_t high_Data(void)
{

    uint8_t buf = dataStructure.rs;
    buf |= 0 << 1;
    buf |= dataStructure.E << 2;
    buf |= dataStructure.Led << 3;
    buf |= dataStructure.datapack & 0xF0;

    return buf;
}
