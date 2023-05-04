#include "ethernet.h"

#include <stdio.h>

void ethernet_say_hi(void)
{
	printf("%s\n", ETHERNET_CODE_PHRASE);
	return;
}


void eth_conv(struct protocol_eth *raw_eth, struct protocol_eth *conv_eth)
{
	for ( int i = 0; i < ETH_ADDR_LEN; i++ ) {
		conv_eth->source_addr[i]=raw_eth->source_addr[i];
		conv_eth->destination_addr[i] = raw_eth->destination_addr[i];
	}

	conv_eth->type = NTOHS(raw_eth->type);
	return;
}

/*END OF FILE*/
