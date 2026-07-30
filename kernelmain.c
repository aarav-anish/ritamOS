#include "types.h"
#include "io.h"
#include "asm.h"
#include "util_lib.h"
#include "serial.h"

#define DELAY_SHORT 4000000U
#define DELAY_MEDIUM 30000000U
#define DELAY_LONG 150000000U

#define SCREEN_COLS 80
#define SCREEN_ROWS 25

static void wait(uint32_t count)
{
    for (volatile uint32_t i = 0; i < count; i++)
        ;
}

void draw_border(uint16_t row, uint8_t color)
{
    for (uint16_t col = 0; col < SCREEN_COLS / 2; col++)
    {
        write_letter_to_framebuffer('=', row, col, color, COLOR_BLACK);
        write_letter_to_framebuffer('=', row, SCREEN_COLS - col - 1, color, COLOR_BLACK);
        wait(DELAY_SHORT);
    }
}

void draw_letter(const char *str, uint16_t row, uint16_t col, uint8_t foreground_color, uint8_t background_color)
{
    for (uint16_t i = 0; str[i] != '\0'; i++)
    {
        write_letter_to_framebuffer(str[i], row, col + i, foreground_color, background_color);
        wait(DELAY_MEDIUM);
    }
}

void print_message(const char *message, const char *subtitle)
{
    const uint16_t msg_len = strlen(message);
    const uint16_t sub_len = strlen(subtitle);

    const uint16_t msg_row = 11;
    const uint16_t msg_col = (SCREEN_COLS - msg_len) / 2;
    const uint16_t sub_col = (SCREEN_COLS - sub_len) / 2;

    draw_border(msg_row - 3, COLOR_GREEN);
    wait(DELAY_LONG);

    draw_letter(subtitle, msg_row - 1, sub_col, COLOR_GREEN, COLOR_BLACK);
    wait(DELAY_LONG);

    draw_letter(message, msg_row, msg_col, COLOR_GREEN, COLOR_BLACK);
    wait(DELAY_LONG);

    draw_letter(subtitle, msg_row + 1, sub_col, COLOR_GREEN, COLOR_BLACK);
    wait(DELAY_LONG);

    draw_border(msg_row + 3, COLOR_GREEN);
    wait(DELAY_LONG);
}

int kernel_main()
{
    // style_cursor(DISABLE);

    // const char *message = "[ Welcome to RitamOS! ]";
    // const char *subtitle = "* * *";

    // print_message(message, subtitle);

    setup_serial(COM1_BASE_ADDR);

    // serial_write_string(COM1_BASE_ADDR, message, strlen(message));

    uint32_t position = 0;
    while (1)
    {
        char input = serial_read(COM1_BASE_ADDR);

        write_letter_to_screen(input, position);
        move_cursor(++position);
    }
    return 0;
}
