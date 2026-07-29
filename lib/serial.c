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
