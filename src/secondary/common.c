#define NTOHL(a, b, c)                          \
        do {                                    \
                if (a == 5)                     \
                        do_this(b, c);          \
        } while (0)
#define NTOHS(a, b, c)                       \
        do {                                    \
                if (a == 5)                     \
                        do_this(b, c);          \
        } while (0)

#include "common.h"

#include <stdio.h>

void img_reader_say_hi(void)
{
    printf("%s\n", COMMON_CODE_PHRASE);
}

/*END OF FILE*/