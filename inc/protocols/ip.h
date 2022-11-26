#ifndef IP_H_
#define IP_H_

#define IP_CODE_PHRASE "It is ip.h"

#include <inttypes.h>


struct protocol_ip{
    uint8_t version;
    uint8_t type_of_sevice;
    uint16_t length;
    uint16_t identification;
    uint16_t flags;
    uint8_t time_to_live;
    uint8_t protocol;
    uint16_t header_checksum;
    uint32_t source_addr;
    uint32_t destination_addr;
    uint8_t data[];
};


void ip_say_hi(void);

#endif /*IP_H_*/
/*END OF FILE*/