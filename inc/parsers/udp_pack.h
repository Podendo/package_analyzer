#ifndef UDP_PACK_H_
#define UDP_PACK_H_

#include <inttypes.h>
#include "ethernet.h"
#include "udp.h"
#include "ip.h"

struct udp_pack_data{
    uint32_t size;
    uint8_t *raw_data;
    uint8_t *ntoh_data;
};


int udp_pack_get_size(char *filename);

static int udp_pack_alloc(char *filename, struct udp_pack_data *udp_pack_data);

static int udp_pack_free(struct udp_pack_data *udp_pack_data);

inline  struct ip_protocol *udp_pack_ip_from_eth(struct protocol_eth *eth);

inline struct udp_protocol *udp_pack_udp_from_eth(struct protocol_eth *eth);

void udp_pack_parse(struct udp_pack_data);

void udp_pack_print(struct udp_pack_data *udp_pack_data);

#endif /*UDP_PACK_H_*/
/*END OF FILE*/