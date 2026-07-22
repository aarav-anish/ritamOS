#include "include/types.h"
#include "include/io.h"
#include "util_lib.h"

int kernel_main()
{
    // char *str = "Welcome to RitamOS!";
    // write_to_screen(str, strlen(str));

    uint8_t num = 14;
    print_byte(&num, 8);

    return 0;
}
