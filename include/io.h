#pragma once

#include "types.h"

#define FRAMEBUFFER 0x000B8000

/* Standard VGA 16-color palette (4 bit: 0-15) */
#define COLOR_BLACK 0x00
#define COLOR_BLUE 0x01
#define COLOR_GREEN 0x02
#define COLOR_CYAN 0x03
#define COLOR_RED 0x04
#define COLOR_MAGENTA 0x05
#define COLOR_BROWN 0x06
#define COLOR_LIGHTGRAY 0x07
#define COLOR_DARKGRAY 0x08
#define COLOR_LIGHTBLUE 0x09
#define COLOR_LIGHTGREEN 0x0A
#define COLOR_LIGHTCYAN 0x0B
#define COLOR_LIGHTRED 0x0C
#define COLOR_LIGHTMAGENTA 0x0D
#define COLOR_LIGHTBROWN 0x0E
#define COLOR_WHITE 0x0F

void write_letter_to_framebuffer(uint8_t letter, uint16_t row, uint16_t col, uint8_t text_color, uint8_t bg_color);
