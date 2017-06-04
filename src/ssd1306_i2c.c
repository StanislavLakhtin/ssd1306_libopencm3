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

#include <ssd1306_i2c.h>
#include <string.h>

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
  I2C_channel = i2c;
  dev_address = address;
  dev_width = width;
  dev_height = height;
  dataLength = (uint16_t) (dev_height / 8 * dev_width);
  //todo set Higher Column Start Address for Page Addressing Mode (10h~1Fh) according 10.1.2 [Datasheet]
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
  i2c_send_data(I2C_channel, 0x20);
  i2c_send_data(I2C_channel, mode);
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
  i2c_send_data(I2C_channel, 0x21);
  i2c_send_data(I2C_channel, lower);
  i2c_send_data(I2C_channel, upper);
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
  i2c_send_data(I2C_channel, 0x22);
  i2c_send_data(I2C_channel, lower);
  i2c_send_data(I2C_channel, upper);
}

/** Set Page Start Address For Page Addressing Mode (0xB0-0xB7) command
 *  According the documentation Page MUST be from 0 to 7
 *  @param pageNum -- from 0 to 7
 */
void ssd1306_setPageStartAddressForPageAddressingMode(uint8_t pageNum) {
  i2c_send_data(I2C_channel, (uint8_t) (0xb0 | (pageNum & 0b00000111)));
}

/** Set Display Start Line (40h~7Fh)
 *  This command sets the Display Start Line register to determine starting address of display RAM, by selecting
 *  a value from 0 to 63. With value equal to 0, RAM row 0 is mapped to COM0. With value equal to 1, RAM
 *  row 1 is mapped to COM0 and so on.
 *  @param startLine -- from 0 to 63
 */

void ssd1306_setDisplayStartLine(uint8_t startLine) {
  i2c_send_data(I2C_channel, (uint8_t) (0x40 | (startLine & 0b00111111)));
}

/** Set Contrast Control for BANK0 (81h)
 *
 * This command sets the Contrast Setting of the display. The chip has 256 contrast steps from 00h to FFh. The
 * segment output current increases as the contrast step value increases.
 * @param value from 0 to 255
 */
void ssd1306_setContrast(uint8_t value) {
  i2c_send_data(I2C_channel, 0x81);
  i2c_send_data(I2C_channel, value);
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
  i2c_send_data(I2C_channel, cmd);
}

/** Set Normal/Inverse Display (A6h/A7h)
 *
 *  This command sets the display to be either normal or inverse. In normal display a RAM data of 1 indicates an
 *  “ON” pixel while in inverse display a RAM data of 0 indicates an “ON” pixel.
 *  @param inverse -- if true display will be inverted
 */
void ssd1306_setInverse(bool inverse) {
  uint8_t cmd = (uint8_t) (inverse ? 0xA7 : 0xA6);
  i2c_send_data(I2C_channel, cmd);
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
 * @param goOn -- if true OLED will going to ON
 *
 * Note: There are two state in the device: NormalMode <-> SleepMode. If device is in SleepMode then the OLED panel power consumption
 * is close to zero. Device almost completely switched off in electrically meaning (sorry for my poor English).
 */
void ssd1306_setOLEDPanelOn(bool goOn) {
  uint8_t cmd = (uint8_t) (goOn ? 0xAF : 0xAE);
  i2c_send_data(I2C_channel, cmd);
}

/** Set Display Offset (D3h)
 * The command specifies the mapping of the display start line to one of
 * COM0~COM63 (assuming that COM0 is the display start line then the display start line register is equal to 0).
 * @param verticalShift -- from 0 to 63
 */

void ssd1306_setDisplayOffset(uint8_t verticalShift) {
  i2c_send_data(I2C_channel, 0xd3);
  i2c_send_data(I2C_channel, verticalShift);
}

/** Set VcomH Deselect Level (DBh)
 * This is a special command to adjust of Vcom regulator output.
 */
void ssd1306_adjustVcomDeselectLevel() {
  i2c_send_data(I2C_channel, 0xdb);
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
  i2c_send_data(I2C_channel, 0xd5);
  i2c_send_data(I2C_channel, value);
}

/**
 * Set the page start address of the target display location by command B0h to B7h
 * @param page -- from 0 to 7
 *
 * NOTE: It command is fit ONLY for Page mode
 */
void ssd1306_setPage(uint8_t page) {
  i2c_send_data(I2C_channel, (uint8_t) (0xb0 | (0b00000111 & page)));
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
  i2c_send_data(I2C_channel, cmd);
  cmd = (uint8_t) (0x10 | (column >> 4));
  i2c_send_data(I2C_channel, cmd);
}
// -------------------- Graphics methods ---------------------------

/**
 *
 * @param screenRAMClear -- clear or not MCU screenRAM. If not MCU will store buffer and can repaint it.
 */

void ssd1306_clear(bool screenRAMClear) {
  ssd1306_setMemoryAddressingMode(Horizontal);
  for (uint16_t i=0; i < dataLength; i++) {
    i2c_send_data(I2C_channel, 0x00);
  }
  if (screenRAMClear) {
    memset(screenRAM, 0x00, dataLength); //TODO check if memset is safe
  }
}

/**
 * Send (and display if OLED is ON) RAM buffer to device
 */
void ssd1306_displayRAM(void) {
  ssd1306_setMemoryAddressingMode(Horizontal);
  for (uint16_t i=0; i < dataLength; i++) {
    i2c_send_data(I2C_channel, screenRAM[i]); //todo make it with DMA later
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
  if ( x > dev_width || y > dev_height )
    return;

  uint16_t offset = (uint16_t) (x + (y / 8) * dev_width);
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
    i2c_send_data(I2C_channel, screenRAM[offset]);
  }
}
