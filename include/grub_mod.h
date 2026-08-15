#pragma once

#include "types.h"

typedef struct
{
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmd_line;
    uint32_t mods_cnt;  // number of modules loaded
    uint32_t mods_addr; // physical address of the module list
    // more fields for memory map, etc.
} multiboot_info_t;

typedef struct
{
    uint32_t mod_start; // physical address where module was loaded
    uint32_t mod_end;   // end address (exclusive)
    uint32_t string;    // pointer to the command-line string ("banking_program.bin")
    uint32_t reserved;
} multiboot_module_t;

// entry_fn is a pointer to a function that takes no arguments and returns nothing.
typedef void (*entry_fn)(void);

void run_module(uint32_t entry_point);
