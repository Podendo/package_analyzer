#include "udp.h"

#include <stdio.h>

void udp_say_hi(void)
{
	printf("%s\n", UDP_CODE_PHRASE);

	return;
}


void udp_conv(struct protocol_udp *raw_udp, struct protocol_udp *conv_udp)
{
	conv_udp->destination_addr = NTOHS(raw_udp->destination_addr);
	conv_udp->source_addr = NTOHS(raw_udp->source_addr);
	conv_udp->length = NTOHS(raw_udp->length);
	conv_udp->checksum = NTOHS(raw_udp->checksum);

	for ( int i = 0; i <= conv_udp->length - UDP_HEADER_SIZE; i++ ) {
		conv_udp->data[i] = raw_udp->data[i];
	}

	return;
}

/*END OF FILE*/
