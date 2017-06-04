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


uint32_t I2C_channel = I2C2;
uint8_t dev_address = I2C_ADDRESS_SA0_0;
uint8_t dev_width = 128;
uint8_t dev_height = 32;

void ssd1306_init(uint32_t i2c, uint8_t address, uint8_t width, uint8_t height);

#endif //SSD1306_LIBRARY_SSD1306_I2C_H_H
