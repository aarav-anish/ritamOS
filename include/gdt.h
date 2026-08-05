#pragma once

#include "types.h"

struct segment_descriptor
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flags_limit;
    uint8_t base_high;
} __attribute__((packed));
// without __attribute__((packed)) compiler may add padding (empty space between the data)
// and CPU expects data to be contiguous.
