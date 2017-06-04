/*
 * Copyright (c) 2017, Stanislav Lakhtin. All rights reserved.
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

#ifndef SSD1306_LIBRARY_SSD1306_I2C_H_H
#define SSD1306_LIBRARY_SSD1306_I2C_H_H

#include <libopencm3/stm32/i2c.h>

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

// address is // 011110+SA0+RW - 0x3C or 0x3D

#define I2C_ADDRESS_SA0_0 0b0111100
#define I2C_ADDRESS_SA0_1 0b0111101
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

// Fundamental Command Table
#define SSD1306_SET_CONTROL     0x81  // Double byte command to select 1 out of 256 contrast steps. Contrast increases as the value increases.
#define SSD1306_RESET           0x7F
#define SSD1306_DISPLAY_ON_RAM  0xA4  // Resume to RAM content display (RESET)
#define SSD1306_DISPLAY_NO_RAM  0xA5  // Output ignores RAM content
#define SSD1306_SET_NORMAL      0xA6  // Normal display (RESET)
#define SSD1306_SET_INVERSE     0xA7  // Inverse display
#define SSD1306_SET_DISPLAY_OFF 0xAE  // Display OFF (sleep mode)
#define SSD1306_SET_DISPLAY_ON  0xAF  // Display ON in normal mode

// Addressing mode



uint32_t I2C_channel = I2C2;
uint8_t dev_address = I2C_ADDRESS_SA0_0;
uint8_t dev_width = 128;
uint8_t dev_height = 32;

enum SSD1306_AddressingMode {
  Horizontal  = 0b00,
  Vertical    = 0b01,
  Page        = 0b10, // RESET
  INVALID     = 0b11  // You MUST NOT USE IT
} AddressingMode;

void ssd1306_init(uint32_t i2c, uint8_t address, uint8_t width, uint8_t height);

// hardware commands
void ssd1306_setMemoryAddressingMode(enum SSD1306_AddressingMode mode);
void ssd1306_setColumnAddressScope(uint8_t lower, uint8_t upper);
void ssd1306_setPageAddressScope(uint8_t lower, uint8_t upper);
void ssd1306_setPageStartAddressForPageAddressingMode(uint8_t pageNum);
void ssd1306_setDisplayStartLine(uint8_t startLine);
void ssd1306_setContrast(uint8_t value);
void ssd1306_setDisplayOn(bool resume); // switch ON/OFF MCU of display
void ssd1306_setInverse(bool inverse);
void ssd1306_setOLEDPanelOn(bool goOn); //switch ON/OFF power switch of the OLED panel
void ssd1306_setDisplayOffset(uint8_t verticalShift);
void ssd1306_adjustVcomDeselectLevel();
void ssd1306_setOscillatorFrequency(uint8_t value); // you SHOULD use default value (0x80)



#endif //SSD1306_LIBRARY_SSD1306_I2C_H_H
