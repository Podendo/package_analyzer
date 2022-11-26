#ifndef ETHERNET_H_
#define ETHERNET_H_

#define ETHERNET_CODE_PHRASE "It is ethernet.h"

#define ETH_ADDR_LEN 6


#include <inttypes.h>
#include "common.h"

/** 
 * IEEE 802.3 Ethernet frame format. Preamble and CRC
 * - first 8 bytes and last 4 bytes are not included in
 * our raw package data,so we have 14 bytes header and
 * 46 to 1500 bytes of data field
 *
*/
struct protocol_eth{
    uint8_t destination_addr[ETH_ADDR_LEN];
    uint8_t source_addr[ETH_ADDR_LEN];
    //TO-DO: type or length?? Wiresharks - type
    uint16_t type;
    uint8_t data[];
};



void ethernet_say_hi(void);

#endif /*ETHERNET_H_*/
/*END OF FILE*/