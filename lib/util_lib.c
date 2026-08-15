#include "types.h"
#include "util_lib.h"

int64_t strlen(const char *str)
{
    if (str == NULL)
        return -1;

    const char *start = str;
    while (*str != '\0')
    {
        str++;
    }
    return (int64_t)(str - start);
}

void *memcpy(void *dest, const void *src, uint32_t size)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    for (uint32_t i = 0; i < size; i++)
    {
        d[i] = s[i];
    }
    return d;
}
