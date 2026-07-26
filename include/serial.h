#pragma once

#define COM1_BASE_ADDR 0x3F8
#define COM2_BASE_ADDR 0x2F8

#define SERIAL_DATA_PORT(base_addr) (base_addr)
#define SERIAL_INTERRUPT_PORT(base_addr) (base_addr + 1)
#define SERIAL_FIFO_CMD_PORT(base_addr) (base_addr + 2)
#define SERIAL_LINE_CMD_PORT(base_addr) (base_addr + 3)
#define SERIAL_MODEM_CMD_PORT(base_addr) (base_addr + 4)
#define SERIAL_LINE_STATUS_PORT(base_addr) (base_addr + 5)
#define SERIAL_MODEM_STATUS_PORT(base_addr) (base_addr + 6)
