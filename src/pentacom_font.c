//
// Created by sl on 06.06.17.
//

#include <pentacom_font.h>

const FontChar_t *getCharacter(uint16_t s) {
  int i = 0;
  for (; i < charTableSize; ++i) {
    if (charTable[i] == s)
      return chars[i];
  }
  return &spaceChar;
}

uint16_t FontChar_getPixelTextLength(wchar_t *text) {
  uint16_t length = 0;
  uint16_t index = 0;
  uint16_t symbol;
  do {
    symbol = text[index];
    FontChar_t *charCur = getCharacter(symbol);
    length += charCur->size;
    index += 1;
  } while (symbol != 0x00);
  return length;
}

void FontChar_drawInt(uint8_t x, uint8_t y, uint8_t color, int num, wchar_t *format) {
  if (format==NULL)
    format = L"%d";
  wchar_t buffer[30];
  swprintf(buffer, 30, format, num);
  ks0108_drawText(x,y,color,buffer);
}

/*void ks0108_drawText(uint8_t x, uint8_t y, uint8_t color, wchar_t *text) { //x и y -- верхний правый угол выводимого текста
  gpio_clear(GPIOA, GPIO_ALL);
  //использовать x и y для настройки на чип, страницу и адрес
  int charPos = 0;
  uint16_t symbol = 0x00;
  do {
    symbol = text[charPos];
    uint8_t curCS = ks0108_chipByAddress(x);
    Ks0108Char_t *charCur = getCharacter(symbol);
    uint8_t cBites = (uint8_t) (y % 8);

    int i = 0;
    for (; i < charCur->size; i++) {
      if (x > 127)
        break;
      uint8_t calcSymLine = ks0108_readMemoryAt(x, y);
      ks0108_GoTo(x, y);
      if (color)
        calcSymLine |= charCur->l[i] << cBites;
      else
        calcSymLine &= ~(charCur->l[i] << cBites);
      ks0108_sendCmdOrData(curCS, 1, 0, calcSymLine);
      if (y < 57 && cBites>0) {
        calcSymLine = ks0108_readMemoryAt(x, y + 8);
        ks0108_GoTo(x, y + 8);
        if (color)
          calcSymLine |= charCur->l[i] >> (8 - cBites);
        else
          calcSymLine &= ~(charCur->l[i] >> (8 - cBites));
        ks0108_sendCmdOrData(curCS, 1, 0, calcSymLine);
      }
      x += 1;
      uint8_t tmpCS = ks0108_chipByAddress(x);
      if (tmpCS != curCS) {
        curCS = tmpCS;
      }
    }

    charPos += 1;
  } while (symbol != 0x00);
}*/