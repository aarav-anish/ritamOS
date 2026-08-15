#include "types.h"
#include "grub_mod.h"

void run_module(uint32_t entry_point)
{
    entry_fn entry = (entry_fn) entry_point;
    entry();
}
