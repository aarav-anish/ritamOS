#include "types.h"
#include "io.h"
#include "gdt.h"

#define GDT_NUM_ENTRIES 3

static struct segment_descriptor gdt_table[GDT_NUM_ENTRIES];

void set_segment_selector(uint16_t index, uint32_t base_address, uint32_t limit, uint8_t access, uint8_t flags)
{
    struct segment_descriptor *gdt_entry = &gdt_table[index];

    // base address
    gdt_entry->base_low = (uint16_t)(base_address & 0xFFFF);
    gdt_entry->base_mid = (uint8_t)((base_address >> 16) & 0xFF);
    gdt_entry->base_high = (uint8_t)((base_address >> 24) & 0xFF);

    // segment limit
    gdt_entry->limit_low = (uint16_t)(limit & 0xFFFF);

    // access byte
    gdt_entry->access = (uint8_t)access;

    // flags limit
    gdt_entry->flags_limit = (uint8_t)(((flags << 4) & 0xF0) | ((limit >> 16) & 0x0F));
}
