#ifndef IP_H_
#define IP_H_

#define IP_CODE_PHRASE		"It is ip.h"
#define IP_IPV4			(0x04)
#define IP_ST			(0x05)
#define IP_SIP			(0x06)
#define IP_IPV6			(0x06)
#define IP_IPV7			(0x07)
#define IP_PIP			(0x08)
#define IP_TUBA			(0x09)


#define IP_ADDR_LEN		(4)

#include <inttypes.h>
#include "common.h"

struct protocol_ip {
	uint8_t		version;
	uint8_t		type_of_sevice;
	uint16_t	length;
	uint16_t	identification;
	uint16_t	flags;
	uint8_t		time_to_live;
	uint8_t		protocol;
	uint16_t	header_checksum;
	uint8_t		source_addr[IP_ADDR_LEN];
	uint8_t		destination_addr[IP_ADDR_LEN];

	uint8_t		data[];
};


void ip_say_hi(void);


void ip_conv(struct protocol_ip *raw_ip, struct protocol_ip *conv_ip);
#endif /*IP_H_*/
