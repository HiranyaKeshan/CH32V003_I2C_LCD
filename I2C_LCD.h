/********************************** (C) COPYRIGHT  *******************************
 * File Name          : I2C_LCD.h
 * Author             : Hiranya Keshan
 * Version            : V1.0.0
 * Date               : 2024/10/08
 * Description        : This file contains all the function prototypes for the
 *                      I2C LCD firmware library.
 *                      Based on PCF8574 i2c controller.
 *                      I2C_LCD.h in Project -> Peripheral -> src
 *                      #include <I2C_LCD.h> in Project -> User -> ch32v00x_conf.h
 *********************************************************************************/

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x.h>
#include <ch32v00x_i2c.h>
#include <ch32v00x_rcc.h>

#define TxAdderss   0x4E

typedef struct
{
    uint8_t rs;
    uint8_t E;
    uint8_t Led;
    uint8_t datapack;

} dataTypeDef;

typedef struct
{
    uint8_t disp_state;
    uint8_t cur_state;
    uint8_t blink_state;

} displayTypeDef;

typedef struct
{
    uint8_t cur_dir;
    uint8_t disp_shift;

} entryTypeDef;

extern dataTypeDef dataStructure;
extern displayTypeDef displayStructure;
extern entryTypeDef entryStructure;

#define Data_in                     ((uint8_t)0x01)
#define Instruct_in                 ((uint8_t)0x00)

#define read_bit                    ((uint8_t)0x01)
#define write_bit                   ((uint8_t)0x00)

#define cur_right                   ((uint8_t)0x01)
#define cur_left                    ((uint8_t)0x00)

void i2c_Begin(u32 bound, uint8_t address);
void clear(void);
void home(void);
void display_On(void);
void display_Off(void);
void cursor_On(void);
void cursor_Off(void);
void blink_On(void);
void blink_Off(void);
void entry_Right(void);
void entry_Left(void);
void display_Shift(void);
void nodisplay_Shift(void);
void shift(void);
void neg_Shift(void);
void shift_Disp(void);
void negshift_Disp(void);
void bclight_On(void);
void bclight_Off(void);
void lcd_Begin(uint8_t row_limit, uint8_t col_limit);
void convert(const char *sentence);
void set_Cursor(uint8_t row, uint8_t col);
void custom_Char(uint8_t location, uint8_t charmap[]);
void i2c_Write(uint8_t packet);
void lcd_Write(uint8_t packet, uint8_t init);
uint8_t low_Data(void);
uint8_t high_Data(void);

#endif /* INC_I2C_LCD_H_ */
