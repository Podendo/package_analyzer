#ifndef UDP_H_
#define UDP_H_

#define UDP_CODE_PHRASE "It is udp.h"

#include <inttypes.h>
#include "common.h"

struct protocol_udp{
    uint16_t source_addr;
    uint16_t destination_addr;
    uint16_t length;
    uint16_t checksum;
    uint8_t data[];
};

void udp_say_hi(void);


void udp_conv(struct protocol_udp *raw_udp, struct protocol_udp *conv_udp);


#endif /*UDP_H_*/
/*END OF FILE*/