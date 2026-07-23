#pragma once

#include "types.h"

#define FRAMEBUFFER 0x000B8000

#define CRTC_COMMAND_PORT 0x3D4
#define CRTC_DATA_PORT 0x3D5
#define CURSOR_POS_HIGH_BYTE_CMD 0x0E
#define CURSOR_POS_LOW_BYTE_CMD 0x0F
#define SCREEN_START_POS_HIGH_BYTE_CMD 0x0C
#define SCREEN_START_POS_LOW_BYTE_CMD 0x0D
#define CURSOR_STYLE_START_CMD 0x0A
#define CURSOR_STYLE_END_CMD 0x0B

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

typedef enum {SMALL, BIG, ENABLE, DISABLE} CursorStyle;

void write_letter_to_framebuffer(uint8_t letter, uint16_t row, uint16_t col, uint8_t text_color, uint8_t bg_color);

void move_cursor(uint16_t position);

void scroll(uint16_t line);

void write_letter_to_screen(const char c, uint16_t pos);

void write_to_screen(const char *buf, uint16_t len);

void print_byte(uint8_t *pbyte, uint32_t pos);

void style_cursor(CursorStyle cstyle);
