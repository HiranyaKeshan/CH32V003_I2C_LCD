# CH32V003 I2C LCD Library

[![Version](https://img.shields.io/badge/version-V1.0.0-blue.svg)](https://github.com/yourusername/yourrepository/releases/tag/V1.0.0)
[![Author](https://img.shields.io/badge/author-Hiranya%20Keshan-green.svg)](https://github.com/yourusername)

This project provides a firmware library for controlling a segment LCD using I2C with the PCF8574 controller. It is designed for the CH32V003 microcontroller and leverages native tools for optimal performance. Existing solutions often rely on Arduino based I2C LCD control (which may not be hardware optimized) or PlatformIO based libraries. This library enables users to control I2C LCDs directly within the native MounRiver Studio IDE. It incorporates HAL-based functions alongside direct register addressing to enhance optimization and efficiency.

## Features

- **Easy Integration**: Simplifies communication with the LCD using the PCF8574 I2C controller.
- **Customizable**: Offers flexibility to adjust and expand based on your project's specific requirements.
- **Efficient Communication**: Optimized I2C routines for smooth and fast data transfer.
- **Support for Standard LCD Operations**: Includes functions for writing text, clearing the display, setting the cursor position, and more.

## Installation

To integrate this library into your project:

1. Place `I2C_LCD.c` in `Project -> Peripheral -> src`.
2. Place `I2C_LCD.h` in `Project -> Peripheral -> inc`.
3. Include the header in your code:
   - Add `#include <I2C_LCD.h>` to `Project -> User -> ch32v00x_conf.h`, or
   - Add `#include "I2C_LCD.h"` to `main.c`.

## Usage

After installation, you can use the library functions in your main application. Refer to the header file (`I2C_LCD.h`) for detailed function prototypes and documentation.

Example usage in `main.c`:
```c
#include "I2C_LCD.h"

int main(void)
{
    i2c_Begin(400000 , TxAdderss);   //Bound < 400kHz ; Default address -> 0x4E
    lcd_Begin(2 , 16);               //Row count ; Column count
    bclight_On();
    convert("Hello");

    while(1);
}
```

## See it in action!

[![🎬 YouTube Demo](https://img.youtube.com/vi/jMtBdHXiuzo/0.jpg)](https://youtu.be/jMtBdHXiuzo)


## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

---

For contributions, issues, or questions, feel free to open a pull request or issue on the GitHub repository.
