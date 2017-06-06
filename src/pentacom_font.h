//
// Created by sl on 06.06.17.
//

#ifndef SSD1306_LIBRARY_PENTACOM_FONT_H
#define SSD1306_LIBRARY_PENTACOM_FONT_H

#include <crimea_font.h>

const FontChar_t *getCharacter(uint16_t s);
uint16_t FontChar_getPixelTextLength(wchar_t *text);

#endif //SSD1306_LIBRARY_PENTACOM_FONT_H
