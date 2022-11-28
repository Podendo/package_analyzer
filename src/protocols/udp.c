#include "udp.h"

#include <stdio.h>

void udp_say_hi(void)
{
    printf("%s\n", UDP_CODE_PHRASE);
}


void udp_conv(struct protocol_udp *raw_udp, struct protocol_udp *conv_udp)
{
    //TO-DO - wireshark byte order MSB->LSB ??? no convertion is needed??
    conv_udp->source_addr = NTOHS(raw_udp->source_addr);
    conv_udp->destination_addr =  NTOHS(raw_udp->destination_addr);

    conv_udp->length = NTOHS(raw_udp->length);
    conv_udp->checksum = NTOHS(raw_udp->checksum);
    
    conv_udp->data[0] = raw_udp->data[0];

}

/*END OF FILE*/