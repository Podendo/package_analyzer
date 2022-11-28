#include "udp_pack.h"

static int udp_pack_get_size(char *filename)
{
    int size = package_get_size(filename);
    return size;
}


int udp_pack_init(char *filename, struct udp_pack_data *udp_pack_data)
{
    int return_value, package_size;

    package_size = udp_pack_get_size(filename);
    if(package_size == ERR_FILEREAD){
        return_value = ERR_NO_ALLOC;
        goto error_force_out;
    }
    
    udp_pack_data->size = package_size;
    udp_pack_data->raw_data = calloc(package_size, sizeof(uint8_t));
    udp_pack_data->ntoh_data = calloc(package_size, sizeof(uint8_t));
    
    package_cp_buffer(filename, udp_pack_data->raw_data);
    package_get_protocol(udp_pack_data->raw_data, package_size);

    return_value = PACK_ALLOC_SUCCESS;

    error_force_out:
    return return_value;
}


int udp_pack_deinit(struct udp_pack_data *udp_pack_data)
{
    udp_pack_data->size = 0;
    free(udp_pack_data->ntoh_data);
    free(udp_pack_data->raw_data);
    
    return PACK_FREE_SUCCESS;
}


//TO-DO: should i add this function or work without it? don't know how then:

static inline struct protocol_eth *udp_pack_eth_from_raw(struct udp_pack_data *udp_pack_data)
{
    struct protocol_eth *eth;
    eth = (struct protocol_eth*)&udp_pack_data->raw_data[0];
    //TO-DO: are you  sure about that?
    for(int byte = 0; byte < ETH_ADDR_LEN; byte++){
        eth->source_addr[byte] = udp_pack_data->raw_data[byte];
        eth->source_addr[byte] = udp_pack_data->raw_data[ETH_ADDR_LEN + byte];
    }
    
    PACK_16(eth->type, udp_pack_data->raw_data[12], udp_pack_data->raw_data[13]);
    eth->data[0] = udp_pack_data->raw_data[14];

    return eth;
}

static inline struct protocol_ip *udp_pack_ip_from_eth(struct protocol_eth *eth)
{
    struct protocol_ip *ip;

    ip = (struct protocol_ip*)&eth->data[0];

    ip->version = eth->data[0];
    ip->type_of_sevice = eth->data[1];
    ip->time_to_live = eth->data[2];

    //TO-DO - how to work with more-than-one bytes variables?
    PACK_32(ip->source_addr, eth->data[3], eth->data[4], eth->data[5], eth->data[6]);

    ip->protocol = eth->data[7];

    PACK_16(ip->length, eth->data[8], eth->data[9]);
    PACK_16(ip->identification, eth->data[10], eth->data[11]);
    PACK_16(ip->header_checksum, eth->data[12], eth->data[13]);
    PACK_16(ip->flags, eth->data[14], eth->data[15]);

    PACK_32(ip->destination_addr, eth->data[16], eth->data[17],
                                 eth->data[18], eth->data[19]);

    //ip->data[0] = &eth->data[20];
    //ip->data = &eth->data[20];
    ip->data[0] = eth->data[20];
    
    return ip;
}


static inline struct protocol_udp *udp_pack_udp_from_eth(struct protocol_eth *eth)
{
    struct protocol_ip *ip;
    struct protocol_udp *udp;

    ip = udp_pack_ip_from_eth(eth);
    udp = (struct protocol_udp*)&ip->data[0];

    PACK_16(udp->source_addr, ip->data[0], ip->data[1]);
    PACK_16(udp->length, ip->data[2], ip->data[3]);
    PACK_16(udp->checksum, ip->data[4], ip->data[5]);

    //udp->data[0] = &ip->data[6];
    //udp->data = &ip->data[6];
    udp->data[0] = ip->data[6];

    return udp;
}


void udp_pack_parse(struct udp_pack_data *udp_pack_data)
{
    struct protocol_eth *eth;
    struct protocol_ip *ip;
    struct protocol_udp *udp;

    //TO-DO - Here protocols should be covered with conv functions:
    eth = udp_pack_eth_from_raw(udp_pack_data);
    ip = udp_pack_ip_from_eth(eth);
    udp = udp_pack_udp_from_eth(eth);

}


void udp_pack_print(struct udp_pack_data *udp_pack_data);



/*END OF FILE*/
