#include "io.h"
#include "types.h"
#include "asm.h"

void write_letter_to_framebuffer(uint8_t letter, uint16_t row, uint16_t col, uint8_t text_color, uint8_t bg_color)
{
    volatile uint16_t *framebuffer = (volatile uint16_t *)FRAMEBUFFER;

    uint16_t letter_framebuffer = 0x00FF & letter;
    uint16_t text_color_framebuffer = (0x000F & text_color) << 8;
    uint16_t bg_color_framebuffer = (0x000F & bg_color) << 12;

    framebuffer[row * 80 + col] = bg_color_framebuffer | text_color_framebuffer | letter_framebuffer;
    return;
}

void move_cursor(uint16_t position)
{
    uint8_t high_byte_pos = (position >> 8) & 0xFF;
    uint8_t low_byte_pos = position & 0xFF;

    outb(CRTC_COMMAND_PORT, CURSOR_POS_HIGH_BYTE_CMD);
    outb(CRTC_DATA_PORT, high_byte_pos);
    outb(CRTC_COMMAND_PORT, CURSOR_POS_LOW_BYTE_CMD);
    outb(CRTC_DATA_PORT, low_byte_pos);
}

void scroll(uint16_t line)
{
    uint16_t offset = line * 80;
    uint8_t high_byte_offset = (offset >> 8) & 0xFF;
    uint8_t low_byte_offset = offset & 0xFF;

    outb(CRTC_COMMAND_PORT, SCREEN_START_POS_HIGH_BYTE_CMD);
    outb(CRTC_DATA_PORT, high_byte_offset);
    outb(CRTC_COMMAND_PORT, SCREEN_START_POS_LOW_BYTE_CMD);
    outb(CRTC_DATA_PORT, low_byte_offset);
}

void write_letter_to_screen(const char c, uint16_t pos)
{
    write_letter_to_framebuffer(c, 0, pos, COLOR_WHITE, COLOR_BLACK);
}

void write_to_screen(const char *buf, uint16_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        write_letter_to_framebuffer(buf[i], 0, i, COLOR_WHITE, COLOR_BLACK);
    }
    move_cursor(len);
}

void print_byte(uint8_t *pbyte, uint32_t pos)
{
    for (int16_t bit = 0; bit < 8; bit++)
    {
        uint8_t mask = (uint8_t)0x1 << (7 - bit);
        if (*pbyte & mask)
        {
            write_letter_to_screen('1', pos + bit);
        }
        else
        {
            write_letter_to_screen('0', pos + bit);
        }
    }
}

void style_cursor(CursorStyle cstyle)
{
    uint8_t start;
    switch (cstyle)
    {
    case (BIG):
        outb(CRTC_COMMAND_PORT, CURSOR_STYLE_START_CMD);
        outb(CRTC_DATA_PORT, 0x00);
        break;
    case (SMALL):
        outb(CRTC_COMMAND_PORT, CURSOR_STYLE_START_CMD);
        outb(CRTC_DATA_PORT, 0x0C);
        break;
    case (DISABLE):
        outb(CRTC_COMMAND_PORT, CURSOR_STYLE_START_CMD);
        start = inb(CRTC_DATA_PORT);
        outb(CRTC_DATA_PORT, start | 0x20);
        break;
    case (ENABLE):
        outb(CRTC_COMMAND_PORT, CURSOR_STYLE_START_CMD);
        start = inb(CRTC_DATA_PORT);
        outb(CRTC_DATA_PORT, start & 0xDF);
        break;
    default:
    }
}
