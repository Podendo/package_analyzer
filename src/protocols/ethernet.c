#include "ethernet.h"

#include <stdio.h>

void ethernet_say_hi(void)
{
    printf("%s\n", ETHERNET_CODE_PHRASE);
}


void eth_conv(struct protocol_eth *raw_eth, struct protocol_eth *conv_eth)
{
    //TO-DO maybe i should define swap function or unite mac addr uint16_t[3]
    conv_eth->type = NTOHS(raw_eth->type);

    conv_eth->source_addr[0] = raw_eth->source_addr[1];
    conv_eth->source_addr[1] = raw_eth->source_addr[0];

    conv_eth->source_addr[2] = raw_eth->source_addr[3];
    conv_eth->source_addr[3] = raw_eth->source_addr[2];

    conv_eth->source_addr[4] = raw_eth->source_addr[5];
    conv_eth->source_addr[5] = raw_eth->source_addr[4];

    conv_eth->destination_addr[0] = raw_eth->source_addr[1];
    conv_eth->destination_addr[1] = raw_eth->source_addr[0];
    conv_eth->destination_addr[2] = raw_eth->source_addr[3];
    conv_eth->destination_addr[3] = raw_eth->source_addr[2];
    conv_eth->destination_addr[4] = raw_eth->source_addr[5];
    conv_eth->destination_addr[5] = raw_eth->source_addr[4];

}

/*END OF FILE*/