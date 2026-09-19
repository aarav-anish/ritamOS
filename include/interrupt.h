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
