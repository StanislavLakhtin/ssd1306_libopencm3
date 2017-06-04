/*
 * Copyright (c) 2017, Stanislav Lakhtin.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. No personal names or organizations' names associated with the
 *    Atomthreads project may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SSD1306_LIBRARY_SSD1306_I2C_H
#include <ssd1306_i2c.h>
#endif

#include <string.h>

uint32_t I2C_OLED = I2C2;
uint8_t OLED_ADDRESS = I2C_ADDRESS_SA0_0;
uint8_t WIDTH = 128;
uint8_t HEIGHT = 32;
uint16_t screenBufferLength = DEFAULTBUFFERLENGH;
MODE AddressingMode = Page;

uint8_t screenRAM[DEFAULTBUFFERLENGH] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xc0
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xc0,0x30
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x3c,0x0c
    ,0x00,0x00,0x00,0x00,0x00,0x03,0xf0,0x03,0xe7,0xf6,0x01,0xf0,0x00,0x00,0x07,0x03
    ,0x00,0x08,0x00,0x00,0x00,0x3c,0x10,0x3c,0x78,0x01,0x80,0x0f,0x00,0x00,0x00,0xe0
    ,0x00,0x08,0x00,0x00,0x03,0xc0,0x21,0xc7,0x80,0x00,0x40,0x00,0xe0,0x00,0x00,0x18
    ,0x00,0x08,0x00,0x00,0x3c,0x00,0x46,0x38,0x00,0x00,0x20,0x00,0x18,0x00,0x00,0x06

    ,0x00,0x08,0x00,0x00,0xc7,0xfc,0x48,0x40,0x00,0x00,0x20,0x00,0x04,0x00,0x00,0x01
    ,0x00,0x08,0x00,0x03,0x38,0x03,0x90,0x80,0x00,0x01,0xff,0xe0,0x02,0x00,0x00,0x00
    ,0x00,0x08,0x00,0x05,0xc0,0x00,0x90,0x80,0x00,0x0e,0x10,0x1c,0x01,0x80,0x00,0x00
    ,0x00,0x08,0x00,0x1e,0x00,0x00,0x90,0x80,0x00,0x18,0x10,0x02,0x00,0x80,0x00,0x00
    ,0x00,0x08,0x00,0x28,0x00,0x00,0x88,0x40,0x00,0x18,0x30,0x01,0x00,0x40,0x00,0x00
    ,0x00,0x08,0x00,0x30,0x00,0x00,0x48,0x20,0x00,0x0c,0x20,0x03,0x00,0x40,0x00,0x00
    ,0x00,0x08,0x00,0x60,0x00,0x00,0x44,0x20,0x00,0x00,0x20,0x1c,0x00,0x40,0x00,0x03
    ,0x00,0x08,0x00,0x60,0x00,0x00,0x24,0x10,0x00,0x00,0x41,0xe0,0x00,0x40,0x00,0x0e

    ,0x00,0x00,0x00,0xa0,0x00,0x00,0x32,0x0e,0x00,0x00,0xfe,0x00,0x01,0xc0,0x00,0x30
    ,0x00,0x00,0x00,0xa0,0x00,0x00,0x09,0x81,0xff,0xff,0x80,0x00,0x0e,0x00,0x01,0xc0
    ,0x00,0x00,0x00,0x90,0x00,0x00,0x04,0x40,0x00,0x06,0x00,0x00,0xf0,0x00,0x06,0x00
    ,0x00,0x00,0x00,0x8c,0x00,0x00,0x03,0x30,0x00,0x08,0x00,0x1f,0x00,0x00,0x78,0x01
    ,0x00,0x00,0x00,0x83,0x00,0x00,0x00,0xcc,0x00,0x30,0x07,0xe0,0x00,0x03,0x80,0x1e
    ,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x33,0xff,0xff,0xf8,0x00,0x00,0x7c,0x01,0xe0
    ,0x00,0x21,0x00,0x80,0x38,0x00,0x00,0x0e,0x03,0x00,0x00,0x00,0x3f,0x80,0x3e,0x00
    ,0x00,0x7f,0x80,0x80,0x07,0x00,0x00,0x01,0xec,0x00,0x00,0x1f,0xc0,0x7f,0xc0,0x00

    ,0x00,0x00,0x00,0x40,0x00,0xfc,0x00,0x00,0x3f,0xf0,0x7f,0xef,0xff,0x80,0x00,0x00
    ,0x00,0x33,0x00,0x20,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x1e,0x00,0x06,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x02,0x00,0x01,0xf0,0x01,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x00,0x0f,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xc0
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xc0,0x30
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x3c,0x0c
    ,0x00,0x00,0x00,0x00,0x00,0x03,0xf0,0x03,0xe7,0xf6,0x01,0xf0,0x00,0x00,0x07,0x03
    ,0x00,0x08,0x00,0x00,0x00,0x3c,0x10,0x3c,0x78,0x01,0x80,0x0f,0x00,0x00,0x00,0xe0
    ,0x00,0x08,0x00,0x00,0x03,0xc0,0x21,0xc7,0x80,0x00,0x40,0x00,0xe0,0x00,0x00,0x18
    ,0x00,0x08,0x00,0x00,0x3c,0x00,0x46,0x38,0x00,0x00,0x20,0x00,0x18,0x00,0x00,0x06

    ,0x00,0x08,0x00,0x00,0xc7,0xfc,0x48,0x40,0x00,0x00,0x20,0x00,0x04,0x00,0x00,0x01
    ,0x00,0x08,0x00,0x03,0x38,0x03,0x90,0x80,0x00,0x01,0xff,0xe0,0x02,0x00,0x00,0x00
    ,0x00,0x08,0x00,0x05,0xc0,0x00,0x90,0x80,0x00,0x0e,0x10,0x1c,0x01,0x80,0x00,0x00
    ,0x00,0x08,0x00,0x1e,0x00,0x00,0x90,0x80,0x00,0x18,0x10,0x02,0x00,0x80,0x00,0x00
    ,0x00,0x08,0x00,0x28,0x00,0x00,0x88,0x40,0x00,0x18,0x30,0x01,0x00,0x40,0x00,0x00
    ,0x00,0x08,0x00,0x30,0x00,0x00,0x48,0x20,0x00,0x0c,0x20,0x03,0x00,0x40,0x00,0x00
    ,0x00,0x08,0x00,0x60,0x00,0x00,0x44,0x20,0x00,0x00,0x20,0x1c,0x00,0x40,0x00,0x03
    ,0x00,0x08,0x00,0x60,0x00,0x00,0x24,0x10,0x00,0x00,0x41,0xe0,0x00,0x40,0x00,0x0e

    ,0x00,0x00,0x00,0xa0,0x00,0x00,0x32,0x0e,0x00,0x00,0xfe,0x00,0x01,0xc0,0x00,0x30
    ,0x00,0x00,0x00,0xa0,0x00,0x00,0x09,0x81,0xff,0xff,0x80,0x00,0x0e,0x00,0x01,0xc0
    ,0x00,0x00,0x00,0x90,0x00,0x00,0x04,0x40,0x00,0x06,0x00,0x00,0xf0,0x00,0x06,0x00
    ,0x00,0x00,0x00,0x8c,0x00,0x00,0x03,0x30,0x00,0x08,0x00,0x1f,0x00,0x00,0x78,0x01
    ,0x00,0x00,0x00,0x83,0x00,0x00,0x00,0xcc,0x00,0x30,0x07,0xe0,0x00,0x03,0x80,0x1e
    ,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x33,0xff,0xff,0xf8,0x00,0x00,0x7c,0x01,0xe0
    ,0x00,0x21,0x00,0x80,0x38,0x00,0x00,0x0e,0x03,0x00,0x00,0x00,0x3f,0x80,0x3e,0x00
    ,0x00,0x7f,0x80,0x80,0x07,0x00,0x00,0x01,0xec,0x00,0x00,0x1f,0xc0,0x7f,0xc0,0x00

    ,0x00,0x00,0x00,0x40,0x00,0xfc,0x00,0x00,0x3f,0xf0,0x7f,0xef,0xff,0x80,0x00,0x00
    ,0x00,0x33,0x00,0x20,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x1e,0x00,0x06,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x02,0x00,0x01,0xf0,0x01,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x00,0x0f,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

/* Device memory organised in 128 horizontal pixel and up to 8 rows of byte
 *
	 B  B .............B  -----
	 y  y .............y        \
	 t  t .............t         \
	 e  e .............e          \
	 0  1 .............127         \
	                                \
	 D0 D0.............D0  LSB       \  ROW 0  |
	 D1 D1.............D1            /  ROW 7  V
	 D2 D2.............D2   |       /
	 D3 D3.............D3   |      /
	 D4 D4.............D4   V     /
	 D5 D5.............D5        /
	 D6 D6.............D6  MSB  /
	 D7 D7.............D7  ----

*/

/** I2C bus write data
 *
 * According to datasheet (8.1.5.1) the I2C-bus interface gives access to write data and command into the device. Please refer to Figure for
 * the write mode of I 2 C-bus in chronological order.
 *
 * S
 * [011110(SA)(r/w)] ack
 * [(Co)(D/C)(Control bites(6))] (ack) [Data byte] (ack)   \
 * [(Co)(D/C)(Control bites(6))] (ack) [Data byte] (ack)    - m >= 0 words
 * [(Co)(D/C)(Control bites(6))] (ack) [Data byte] (ack)   /
 * [(Co)(D/C)(Control bites(6))] (ack) [Data byte] (ack)   every [...] -- 1 byte
 * [(Co)(D/C)(Control bites(6))] (ack) [Data byte] (ack)   [Data byte] -- should be n >= 0
 * [(Co)(D/C)(Control bites(6))] (ack) [Data byte] (ack)   MSB.....LSB
 * [Data byte] (ack) [Data byte] (ack) [Data byte] (ack)
 * [Data byte] (ack) [Data byte] (ack) [Data byte] (ack)
 * P
 *
 * [011110(SA)(r/w)]                -- SSD1306 slave address
 * [(Co)(D/C)(Control bites(6))]    -- Control byte
 *
 * 1. The master device initiates the data communication by a start condition.
 *    The start condition is established by pulling the SDA from HIGH to LOW while the SCL stays HIGH.
 * 2. The slave address is following the start condition for recognition use. For the SSD1306, the slave
 *      address is either “b0111100” or “b0111101” by changing the SA0 to LOW or HIGH (D/C pin acts as
 *      SA0).
 * 3. The write mode is established by setting the R/W# bit to logic “0”.
 * 4. An acknowledgement signal will be generated after receiving one byte of data, including the slave
 *      address and the R/W# bit. The acknowledge bit is defined as the SDA line is pulled down during the HIGH
 *      period of the acknowledgement related clock pulse.
 * 5. After the transmission of the slave address, either the control byte or the data byte may be sent across
 *      the SDA. A control byte mainly consists of Co and D/C# bits following by six “0” ‘s.
 *          a. If the Co bit is set as logic “0”, the transmission of the following information will contain
 *             data _bytes_ only.
 *          b. The D/C# bit determines the next data byte is acted as a command or a data. If the D/C# bit is
 *             set to logic “0”, it defines the following data byte as a command. If the D/C# bit is set to
 *             logic “1”, it defines the following data byte as a data which will be stored at the GDDRAM.
 *      The GDDRAM column address pointer will be increased by one automatically after each
 *      data write.
 * 6. Acknowledge bit will be generated after receiving each control byte or data byte.
 * 7. The write mode will be finished when a stop condition is applied. The stop condition is also defined
 *      in Figure 8-8. The stop condition is established by pulling the “SDA in” from LOW to HIGH while
 *      the “SCL” stays HIGH.
 *
 *      @param spec -- should be DATAONLY or COMMAND
 *
 *      Note: if you choose DATAONLY then a few bytes CAN follow that
 */

void ssd1306_start(void) {
  i2c_send_start(I2C_OLED);
  i2c_send_7bit_address(I2C_OLED, OLED_ADDRESS, I2C_WRITE);
}

void ssd1306_stop(void) {
  i2c_send_stop(I2C_OLED);
}

void ssd1306_send(uint8_t spec) {
  i2c_send_data(I2C_OLED, spec);
}

void ssd1306_send_data(uint8_t spec, uint8_t data) {
  i2c_send_data(I2C_OLED, spec);
  i2c_send_data(I2C_OLED, data);
}

/**
  *  According Reset Circuit
  *  When RES# input is LOW, the chip is initialized with the following status:
  *  1. Display is OFF
  *  2. 128 x 64 Display Mode
  *  3. Normal segment and display data column address and row address mapping (SEG0 mapped to
  *      address 00h and COM0 mapped to address 00h)
  *  4. Shift register data clear in serial interface
  *  5. Display start line is set at display RAM address 0
  *  6. Column address counter is set at 0
  *  7. Normal scan direction of the COM outputs
  *  8. Contrast control register is set at 7Fh
  *  9. Normal display mode (Equivalent to A4h command)
  */

/**
  * According libopencm3 constants, i2c should pointed on one of the i2c interfaces such as
  * I2C1, I2C2 etc. Interface MUST be initialized on that moment.
  * @param i2c -- I2C1, I2C2 etc.
  * @param address -- I2C address of the device. It can be 0x3C (or 0x3D)
  * @param width -- width of the display
  * @param height -- height of the display
  */
void ssd1306_init(uint32_t i2c, uint8_t address, uint8_t width, uint8_t height) {
  I2C_OLED = i2c;
  OLED_ADDRESS = address;
  WIDTH = width;
  HEIGHT = height;
  screenBufferLength = (uint16_t) (HEIGHT / 8 * WIDTH);
  // send initial command to the device
  ssd1306_start();
  // now we can and should send a lot commands
  ssd1306_switchOLEDOn(false, false); // 0xae
  ssd1306_setOscillatorFrequency(0x80);  // D5h 0x80
  ssd1306_setInverse(false); // normal display
  ssd1306_setContrast(0x8F);
  ssd1306_setPrecharge(0xf1);
  ssd1306_adjustVcomDeselectLevel();
  ssd1306_setDisplayOn(true);
  ssd1306_switchOLEDOn(true, true);
  ssd1306_refresh();
  ssd1306_stop();
}

/**
  * Set Memory Addressing Mode (20h)
  * 2 byte
  * A[1:0] = 00b, Horizontal Addressing Mode
  * A[1:0] = 01b, Vertical Addressing Mode
  * A[1:0] = 10b, Page Addressing Mode (default after RESET)
  * A[1:0] = 11b, Invalid
  * @param mode -- select Mode
  */

void ssd1306_setMemoryAddressingMode(MODE mode) {
  ssd1306_send_data(COMMAND, 0x20);
  ssd1306_send_data(COMMAND, mode);
}

/** Set Column Address [Space] (21h)
  *
  *  3 byte
  *  Command specifies column start address and end address of the display data RAM. This
  *  command also sets the column address pointer to column start address. This pointer is used to define the
  *  current read/write column address in graphic display data RAM.
  *
  *  It setup column start and end address
  *      A[6:0] : Column start address, range : 0-127d, (RESET=0d)
  *      B[6:0]: Column end address, range : 0-127d, (RESET =127d)
  *
  * @param lower  -- up to 127
  * @param higher -- up to 127
  *
  * Note: This command is only for horizontal or vertical addressing mode!
  */

void ssd1306_setColumnAddressScope(uint8_t lower, uint8_t upper) {
  ssd1306_send_data(COMMAND, 0x21);
  ssd1306_send_data(COMMAND, lower);
  ssd1306_send_data(COMMAND, upper);
}

/** Set Page Address (22h)
  *
  *  This triple byte command specifies page start address and end address of the display data RAM. This
  *  command also sets the page address pointer to page start address. This pointer is used to define the current
  *  read/write page address in graphic display data RAM. If vertical address increment mode is enabled by
  *  command 20h, after finishing read/write one page data, it is incremented automatically to the next page
  *  address. Whenever the page address pointer finishes accessing the end page address, it is reset back to start
  *  page address.
  *
  *  Setup page start and end address
  *      A[2:0] : Page start Address, range : 0-7d, (RESET = 0d)
  *      B[2:0] : Page end Address, range : 0-7d, (RESET = 7d)
  *
  *  @param lower  -- from 0 up to 7
  *  @param higher -- from 0 up to 7
  *
  *  Note: This command is only for horizontal or vertical addressing mode.
  */

void ssd1306_setPageAddressScope(uint8_t lower, uint8_t upper) {
  ssd1306_send_data(COMMAND, 0x22);
  ssd1306_send_data(COMMAND, lower);
  ssd1306_send_data(COMMAND, upper);
}

/** Set Page Start Address For Page Addressing Mode (0xB0-0xB7) command
 *  According the documentation Page MUST be from 0 to 7
 *  @param pageNum -- from 0 to 7
 */
void ssd1306_setPageStartAddressForPageAddressingMode(uint8_t pageNum) {
  ssd1306_send_data(COMMAND, (uint8_t) (0xb0 | (pageNum & 0b00000111)));
}

/** Set Display Start Line (40h~7Fh)
 *  This command sets the Display Start Line register to determine starting address of display RAM, by selecting
 *  a value from 0 to 63. With value equal to 0, RAM row 0 is mapped to COM0. With value equal to 1, RAM
 *  row 1 is mapped to COM0 and so on.
 *  @param startLine -- from 0 to 63
 */

void ssd1306_setDisplayStartLine(uint8_t startLine) {
  ssd1306_send_data(COMMAND, (uint8_t) (0x40 | (startLine & 0b00111111)));
}

/** Set Contrast Control for BANK0 (81h)
 *
 * This command sets the Contrast Setting of the display. The chip has 256 contrast steps from 00h to FFh. The
 * segment output current increases as the contrast step value increases.
 * @param value from 0 to 255
 */
void ssd1306_setContrast(uint8_t value) {
  ssd1306_send_data(COMMAND, 0x81);
  ssd1306_send_data(COMMAND, value);
}

/** Set Pre-charge Period (D9h)
 *
 * This command is used to set the duration of the pre-charge period. The interval is counted in number of
 * DCLK, where RESET equals 2 DCLKs.
 *
 * Note:
 * @param value -- experimental typical value is 0xF1
 */

void ssd1306_setPrecharge(uint8_t value) {
  ssd1306_send_data(COMMAND, 0xd9);
  ssd1306_send_data(COMMAND, value);
}

/**
 * Entire Display ON (A4h/A5h)
 * A4h command enable display outputs according to the GDDRAM contents.
 * If A5h command is issued, then by using A4h command, the display will resume to the GDDRAM contents.
 * In other words, A4h command resumes the display from entire display “ON” stage.
 * A5h command forces the entire display to be “ON”, regardless of the contents of the display data RAM.
 *
 * @param resume -- if it will be true, then DISPLAY will go ON and redraw content from RAM
 */
void ssd1306_setDisplayOn(bool resume) {
  uint8_t cmd = (uint8_t) (resume ? 0xA5 : 0xA4);
  ssd1306_send_data(COMMAND, cmd);
}

/** Set Normal/Inverse Display (A6h/A7h)
 *
 *  This command sets the display to be either normal or inverse. In normal display a RAM data of 1 indicates an
 *  “ON” pixel while in inverse display a RAM data of 0 indicates an “ON” pixel.
 *  @param inverse -- if true display will be inverted
 */
void ssd1306_setInverse(bool inverse) {
  uint8_t cmd = (uint8_t) (inverse ? 0xA7 : 0xA6);
  ssd1306_send_data(COMMAND, cmd);
}

/** Set Display ON/OFF (AEh/AFh)
 *
 * These single byte commands are used to turn the OLED panel display ON or OFF.
 * When the display is ON, the selected circuits by Set Master Configuration command will be turned ON.
 * When the display is OFF, those circuits will be turned OFF and the segment and common output are in V SS
 * tate and high impedance state, respectively. These commands set the display to one of the two states:
 *  AEh : Display OFF
 *  AFh : Display ON
 *
 * Charge Pump Capacitor (8D)
 *
 *  The internal regulator circuit in SSD1306 accompanying only 2 external capacitors can generate a
 *  7.5V voltage supply, V CC, from a low voltage supply input, V BAT . The V CC is the voltage supply to the
 *  OLED driver block. This is a switching capacitor regulator circuit, designed for handheld applications.
 *  This regulator can be turned on/off by software command setting.
 *
 * @param goOn -- if true OLED will going to ON
 * @param enableChargePump -- if On Charge Pump WILL be on when Display ON
 *
 * Note: There are two state in the device: NormalMode <-> SleepMode. If device is in SleepMode then the OLED panel power consumption
 * is close to zero.
 */
void ssd1306_switchOLEDOn(bool goOn, bool enableChargePump) {
  if (goOn) {
    ssd1306_send_data(COMMAND, 0x8d);
    if (enableChargePump)
      ssd1306_send_data(COMMAND, 0x10);
    else
      ssd1306_send_data(COMMAND, 0x14);
    ssd1306_send_data(COMMAND, 0xAF);
  } else
    ssd1306_send_data(COMMAND, 0xAE);
}

/** Set Display Offset (D3h)
 * The command specifies the mapping of the display start line to one of
 * COM0~COM63 (assuming that COM0 is the display start line then the display start line register is equal to 0).
 * @param verticalShift -- from 0 to 63
 */

void ssd1306_setDisplayOffset(uint8_t verticalShift) {
  ssd1306_send_data(COMMAND, 0xd3);
  ssd1306_send_data(COMMAND, verticalShift);
}

/** Set VcomH Deselect Level (DBh)
 * This is a special command to adjust of Vcom regulator output.
 */
void ssd1306_adjustVcomDeselectLevel(void) {
  ssd1306_send_data(COMMAND, 0xdb);
}

/** Set Display Clock Divide Ratio/ Oscillator Frequency (D5h)
 *  This command consists of two functions:
 *  1. Display Clock Divide Ratio (D)(A[3:0])
 *      Set the divide ratio to generate DCLK (Display Clock) from CLK. The divide ratio is from 1 to 16,
 *      with reset value = 1. Please refer to section 8.3 (datasheet ssd1306) for the details relationship of DCLK and CLK.
 *  2. Oscillator Frequency (A[7:4])
 *      Program the oscillator frequency Fosc that is the source of CLK if CLS pin is pulled high. The 4-bit
 *      value results in 16 different frequency settings available as shown below. The default setting is 0b1000
 *
 * WARNING: you should NOT call this function with another parameters if you don't know why you do it
 *
 * @param value -- default value is 0x80
 */
void ssd1306_setOscillatorFrequency(uint8_t value) {
  ssd1306_send_data(COMMAND, 0xd5);
  ssd1306_send_data(COMMAND, value);
}

/**
 * Set the page start address of the target display location by command B0h to B7h
 * @param page -- from 0 to 7
 *
 * NOTE: It command is fit ONLY for Page mode
 */
void ssd1306_setPage(uint8_t page) {
  ssd1306_send_data(COMMAND, (uint8_t) (0xb0 | (0b00000111 & page)));
}

/**
 * Set the lower and the upper column.
 * See note from datasheet:
 *
 * In page addressing mode, after the display RAM is read/written, the column address pointer is increased
 * automatically by 1. If the column address pointer reaches column end address, the column address pointer is
 * reset to column start address and page address pointer is not changed. Users have to set the new page and
 * column addresses in order to access the next page RAM content.
 *
 * In normal display data RAM read or write and page addressing mode, the following steps are required to
 * define the starting RAM access pointer location:
 *  • Set the page start address of the target display location by command B0h to B7h.
 *  • Set the lower start column address of pointer by command 00h~0Fh.
 *  • Set the upper start column address of pointer by command 10h~1Fh.
 * For example, if the page address is set to B2h, lower column address is 03h and upper column address is 10h,
 * then that means the starting column is SEG3 of PAGE2.
 *
 * According that we should send first lower value. Next we send upper value.
 *
 * @param column -- from 0 to 127
 *
 * NOTE: It command is fit ONLY for Page mode
 */
void ssd1306_setColumn(uint8_t column) {
  uint8_t cmd = (uint8_t) (0x0f & column);
  ssd1306_send_data(COMMAND, cmd);
  cmd = (uint8_t) (0x10 | (column >> 4));
  ssd1306_send_data(COMMAND, cmd);
}
// -------------------- Graphics methods ---------------------------

/**
 *
 * @param screenRAMClear -- clear or not MCU screenRAM. If not MCU will store buffer and can repaint it.
 */

void ssd1306_clear(bool screenRAMClear) {
  ssd1306_setMemoryAddressingMode(Horizontal);
  ssd1306_send(DATAONLY);
  for (uint16_t i=0; i < screenBufferLength; i++) {
    i2c_send_data(I2C_OLED, 0x00);
  }
  if (screenRAMClear) {
    memset(screenRAM, 0x00, screenBufferLength); //TODO check if "memset" is safe in our env
  }
}

/**
 * Send (and display if OLED is ON) RAM buffer to device
 */
void ssd1306_refresh(void) {
  ssd1306_setMemoryAddressingMode(Horizontal);
  ssd1306_send(DATAONLY);
  for (uint16_t i=0; i < screenBufferLength; i++) {
    i2c_send_data(I2C_OLED, screenRAM[i]); //todo make it with DMA later
  }
}

/**
 *
 * @param x -- from 0 to dev_width
 * @param y -- from y to dev_height
 * @param c -- white or black
 * @param instantDraw -- if used no RAM data changed, but pixel send direct to device
 * @param op -- and or xor (beware that operation will be with RAM stored)
 */
void ssd1306_drawPixel(uint8_t x, uint8_t y, Color c, bool instantDraw, BOOL_OPER op) {
  if ( x > WIDTH || y > HEIGHT )
    return;

  uint16_t offset = (uint16_t) (x + (y / 8) * WIDTH);
  //draw into memory
  switch (op) {
    case or:
      screenRAM[offset] |= _bit(y%8);
      break;
    case and:
      screenRAM[offset] &= (c == black)? _bit(y%8) : _inverse(y%8);
      break;
    case xor:
      screenRAM[offset] ^= (c == black)? _bit(y%8) : _inverse(y%8);
      break;
  }

  if (!instantDraw) {
    ssd1306_setPageStartAddressForPageAddressingMode(Page);
    ssd1306_setPage(y/8);
    ssd1306_setColumn(x);
    ssd1306_send(DATAONLY);
    i2c_send_data(I2C_OLED, screenRAM[offset]);
  }
}
