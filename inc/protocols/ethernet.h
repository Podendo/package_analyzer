#ifndef ETHERNET_H_
#define ETHERNET_H_

#define ETHERNET_CODE_PHRASE "It is ethernet.h"
#define ETH_IPV4    0x0800
#define ETH_IPV6    0x86DD

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

    uint16_t type;

    uint8_t data[];
};

void ethernet_say_hi(void);

/**
 * Convert raw data from protocol field to the one
 * which can be read by host via NTOHS NTOHL macro
*/
void eth_conv(struct protocol_eth *raw_eth, struct protocol_eth *conv_eth);


#endif /*ETHERNET_H_*/
/*END OF FILE*/