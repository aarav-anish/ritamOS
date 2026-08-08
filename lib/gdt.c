#include "types.h"
#include "io.h"
#include "gdt.h"

#define GDT_NUM_ENTRIES 3

static struct segment_descriptor gdt_table[GDT_NUM_ENTRIES];
static struct gdtr gdtr;

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

void gdt_init()
{
    set_segment_selector(0, 0, 0, 0, 0);             // null descriptor
    set_segment_selector(1, 0x0, 0xFFFF, 0x9A, 0xC); // code segment
    set_segment_selector(2, 0x0, 0xFFFF, 0x92, 0xC); // data segment

    gdtr.limit = (uint16_t)(sizeof(struct segment_descriptor) * GDT_NUM_ENTRIES) - 1;
    gdtr.address = (uint32_t)gdt_table;

    gdt_flush(&gdtr);
}
