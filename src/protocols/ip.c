#include "ip.h"

#include <stdio.h>

void ip_say_hi(void)
{
    printf("%s\n", IP_CODE_PHRASE);
}


void ip_conv(struct protocol_ip *raw_ip, struct protocol_ip *conv_ip)
{
    conv_ip->version = raw_ip->version;
    conv_ip->type_of_sevice = raw_ip->type_of_sevice;
    conv_ip->length = NTOHS(raw_ip->length);

    conv_ip->identification = NTOHS(raw_ip->identification);
    conv_ip->flags = NTOHS (raw_ip->flags);

    conv_ip->time_to_live = raw_ip->type_of_sevice;
    conv_ip->protocol = raw_ip->protocol;
    conv_ip->header_checksum = NTOHS(raw_ip->header_checksum);

    //conv_ip->source_addr = NTOHL(raw_ip->source_addr);
    //conv_ip->destination_addr = NTOHL(raw_ip->destination_addr);
    conv_ip->source_addr = raw_ip->source_addr;
    conv_ip->destination_addr = raw_ip->destination_addr;

    conv_ip->data[0] = raw_ip->data[0];
}

/*END OF FILE*/