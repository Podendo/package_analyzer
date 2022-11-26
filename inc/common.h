#ifndef COMMON_H_
#define COMMON_H_

#define COMMON_CODE_PHRASE "It is common.h"

#define SWAP_BYTE(BITS_8)                                           \
        BYTE = ((BITS_8 & 0x01) << 7) | ((BITS_8 & 0x02) << 5) |    \
            ((BITS_8 & 0x04) << 3) | ((BITS_8 & 0x08) << 1) |       \
            ((BITS_8 & 0x80) >> 7) | ((BITS_8 & 0x40) >> 5) |       \
            ((BITS_8 & 0x20) >> 3) | ((BITS_8 & 0x10) >> 1)         \


#define NTOHS(BITS_16)                                          \
        BITS_16 = ((BITS_16 & 0xFF00) >> 8) |                   \
            ((BITS_16 & 0x00FF) << 8)                           \


#define NTOHL(BITS_32)                                          \
        BITS_32 = ((BITS_32 & 0xFF000000) >> 24) |              \
            ((BITS_32 & 0x00FF0000) >> 8) |                     \
            ((BITS_32 & 0x0000FF00) << 8) |                     \
            ((BITS_32 & 0x000000FF) << 24)                      \


#include <inttypes.h>

void img_reader_say_hi(void);

#endif /*COMMON_H_*/
/*END OF FILE*/