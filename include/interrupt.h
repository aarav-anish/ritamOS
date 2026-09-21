#pragma once

#include "types.h"

struct interrupt_descriptor
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved_and_zeros;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

struct idtr
{
    uint16_t limit;
    uint32_t address;
} __attribute__((packed));

void set_segement_descriptor(uint8_t index, uint32_t handler, uint16_t segment_selector, uint8_t flags);

void idt_init();

extern void load_idt(struct idtr *idtr);
