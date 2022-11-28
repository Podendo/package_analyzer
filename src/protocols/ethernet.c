#include "ethernet.h"

#include <stdio.h>

void ethernet_say_hi(void)
{
    printf("%s\n", ETHERNET_CODE_PHRASE);
}


void eth_conv(struct protocol_eth *raw_eth, struct protocol_eth *conv_eth)
{
    conv_eth->type = NTOHS(raw_eth->type);

    for(int byte = 0; byte < ETH_ADDR_LEN; byte++){
        conv_eth->source_addr[byte] = raw_eth->source_addr[byte];
        conv_eth->destination_addr[ETH_ADDR_LEN + byte] = raw_eth->destination_addr[ETH_ADDR_LEN + byte];
    }
    conv_eth->data[0] = raw_eth->data[0];

}

/*END OF FILE*/