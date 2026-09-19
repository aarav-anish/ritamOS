#include "types.h"
#include "interrupt.h"

#define IDT_NUM_ENTRIES 256

static struct interrupt_descriptor idt_table[IDT_NUM_ENTRIES] __attribute__((aligned(8)));

void set_segement_descriptor(uint8_t index, uint32_t handler, uint16_t segment_selector, uint8_t flags)
{
    struct interrupt_descriptor *idt_entry = &idt_table[index];

    idt_entry->offset_low = (uint16_t)(handler & 0xFFFF);
    idt_entry->offset_high = (uint16_t)((handler >> 16) & 0xFFFF);
    idt_entry->flags = (uint8_t)flags;
    idt_entry->reserved_and_zeros = (uint8_t)0x00000000;
    idt_entry->segment_selector = (uint16_t)segment_selector;
}
