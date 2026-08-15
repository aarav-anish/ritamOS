#include "../include/io.h"
#include "../include/util_lib.h"

void start()
{
    char *msg = "SECRET DATA: 123456789";
    write_to_screen(msg, strlen(msg));
}
