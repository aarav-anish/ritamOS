#include "include/types.h"
#include "include/io.h"

int kernel_main()
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            write_letter_to_framebuffer('X', i, j, COLOR_GREEN, COLOR_WHITE);
        }
    }
    move_cursor(500);
    scroll(4);
    return 0;
}
