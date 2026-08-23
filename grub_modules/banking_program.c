#include "../include/io.h"
#include "../include/util_lib.h"
#include "../include/serial.h"

void start()
{
    char *screen_msg = "SECRET DATA: 123456789";
    // write_to_screen(msg, strlen(msg));

    setup_serial(COM1_BASE_ADDR);

    const char *msg = "Banking program ran successfully\n\n\n";
    serial_write_string(COM1_BASE_ADDR, msg, strlen(msg));
}
