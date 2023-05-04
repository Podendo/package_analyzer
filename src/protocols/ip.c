#include "ip.h"

#include <stdio.h>

void ip_say_hi(void)
{
	printf("%s\n", IP_CODE_PHRASE);
	return;
}


void ip_conv(struct protocol_ip *raw_ip, struct protocol_ip *conv_ip)
{
	conv_ip->version = raw_ip->version;
	conv_ip->type_of_sevice = raw_ip->type_of_sevice;

	conv_ip->length = NTOHS(raw_ip->length);

	conv_ip->identification = NTOHS(raw_ip->identification);

	conv_ip->flags = NTOHS(raw_ip->flags);

	conv_ip->time_to_live = conv_ip->time_to_live;
	conv_ip->protocol = raw_ip->protocol;

	conv_ip->header_checksum = NTOHS(raw_ip->header_checksum);

	for ( int i =0; i < IP_ADDR_LEN; i++ ) {
		conv_ip->source_addr[i] = raw_ip->source_addr[i];
		conv_ip->destination_addr[i] = raw_ip->destination_addr[i];
	}

	return;
}

/*END OF FILE*/
