#include "rit_shell.h"
#include "io.h"
#include "util_lib.h"

void draw_header()
{
    const char *name = "R I T S H E L L";
    uint16_t len = strlen(name);

    for (uint32_t i = 0; i < RS_COLS; i++)
    {
        write_letter_to_framebuffer(' ', 0, i, COLOR_WHITE, COLOR_GREEN);
        write_letter_to_framebuffer(' ', RS_ROWS - 1, i, COLOR_WHITE, COLOR_GREEN);
    }

    uint32_t text_start = (RS_COLS - len) / 2;
    for (uint32_t i = 0; i < len; i++)
    {
        write_letter_to_framebuffer(name[i], 0, text_start + i, COLOR_WHITE, COLOR_GREEN);
    }

    move_cursor(RS_COLS * 2 + 2);
}

void rit_shell()
{
    draw_header();

    uint16_t CURSOR_POS = RS_COLS * 2 + 2;

    while (1)
    {
        uint8_t scan_code = read_scan_code();
        write_letter_to_screen(scan_code, CURSOR_POS);

        CURSOR_POS++;
        if (CURSOR_POS >= RS_ROWS * RS_COLS)
            break;
    }
}
