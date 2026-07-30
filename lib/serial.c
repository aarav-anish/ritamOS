#include "types.h"
#include "asm.h"
#include "serial.h"

void setup_serial(uint16_t com)
{
    // disable interrupts
    outb(SERIAL_INTERRUPT_PORT(com), 0x00);

    // set baudrate
    uint16_t divisor = 1;
    outb(SERIAL_LINE_CMD_PORT(com), 0x80);                  // DLAB to 1
    outb(SERIAL_DATA_PORT(com), divisor & 0xFF);            // send least significant byte of divisor
    outb(SERIAL_DATA_PORT(com) + 1, (divisor >> 8) & 0xFF); // send most significant byte of divisor

    // configure line
    outb(SERIAL_LINE_CMD_PORT(com), 0x03);

    // configure FIFO
    outb(SERIAL_FIFO_CMD_PORT(com), 0xC7);

    // configure modem
    outb(SERIAL_MODEM_CMD_PORT(com), 0x03);
}

int8_t is_transit_buffer_empty(uint16_t com)
{
    return (inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20) == 0x20;
}

void serial_write(uint16_t com, uint8_t data)
{
    while (!is_transit_buffer_empty(com))
    {
    }
    outb(SERIAL_DATA_PORT(com), data);
}

void serial_write_string(uint16_t com, const char *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        serial_write(com, buf[i]);
    }
}
