#include "udp_pack.h"

static int udp_pack_get_size(char *filename)
{
    int size = package_get_size(filename);
    return size;
}


static inline struct protocol_eth *udp_pack_eth_from_raw(struct udp_pack_data *udp_pack_data)
{
    struct protocol_eth *eth;
    eth = (struct protocol_eth*)udp_pack_data->raw_data;
    return eth;
}



static inline struct protocol_ip *udp_pack_ip_from_eth(struct protocol_eth *eth)
{
    struct protocol_ip *ip;
    ip = (struct protocol_ip*)eth->data;    
    return ip;
}


static inline struct protocol_udp *udp_pack_udp_from_eth(struct protocol_eth *eth)
{
    struct protocol_udp *udp;
    struct protocol_ip *ip;

    ip = udp_pack_ip_from_eth(eth);
    
    udp = (struct protocol_udp*)ip->data;

    return udp;
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

//TO-DO Error flags do not work
int udp_pack_deinit(struct udp_pack_data *udp_pack_data)
{
    int return_value = ERR_NO_ALLOC;

    udp_pack_data->size = 0;
    free(udp_pack_data->ntoh_data);
    free(udp_pack_data->raw_data);

    return_value = PACK_FREE_SUCCESS;
    
    return return_value;
}


void udp_pack_parse(struct udp_pack_data *udp_pack_data)
{

    //segfault will be here: unitialized memory

    struct protocol_eth *raw_eth;
    struct protocol_eth *conv_eth;

    struct protocol_ip *raw_ip;
    struct protocol_ip *conv_ip;

    struct protocol_udp *raw_udp;
    struct protocol_udp *conv_udp;

    //Setting address to conv protocols for ntoh data array addr
    //TO-DO - Here protocols should be covered with conv functions:

    raw_eth = udp_pack_eth_from_raw(udp_pack_data);

    raw_ip = udp_pack_ip_from_eth(raw_eth);

    raw_udp = udp_pack_udp_from_eth(raw_eth);

    //taking addresses of package to convertion pointers:
    conv_eth = (struct protocol_eth*)udp_pack_data->ntoh_data;
    conv_ip =  udp_pack_ip_from_eth(conv_eth);
    conv_udp = udp_pack_udp_from_eth(conv_eth);

    eth_conv(raw_eth, conv_eth);
    ip_conv(raw_ip, conv_ip);
    udp_conv(raw_udp, conv_udp);

}


void udp_pack_print(struct udp_pack_data *udp_pack_data)
{
    struct protocol_eth *eth;
    struct protocol_ip *ip;
    struct protocol_udp *udp;

    eth = (struct protocol_eth*)udp_pack_data->ntoh_data;
    ip = udp_pack_ip_from_eth(eth);
    udp = udp_pack_udp_from_eth(eth);


    printf("\n______________ U D P ______________\n");

    printf("\n\nNTOH DATA:\n");
    for(uint32_t i = 0; i < udp_pack_data->size; i++){
        if(i % 8 == 0) printf("\n");
        printf("%02x ", udp_pack_data->ntoh_data[i]);
    }

    printf("\n\nEthernet protocol:\n");

    printf("source address:\n");

    for(int i = 0; i < ETH_ADDR_LEN; i++){
            printf(" %02x ",eth->source_addr[i]);
    } printf("\n");
        
    printf("destination address:\n");
    for(int i = 0; i < ETH_ADDR_LEN; i++){
                printf(" %02x ",eth->destination_addr[i]);
    } printf("\n");

    printf("type: %04x\n ",eth->type);


    printf("Ip version:  %02x\n", ip->version);
    printf("Ip Type of service:  %02x\n", ip->type_of_sevice);
    printf("Ip Length:  %04x\n", ip->length);
    printf("Ip identification:  %04x\n", ip->identification);
    printf("Ip flags:  %04x\n", ip->flags);
    printf("Ip time to live:  %02x\n", ip->time_to_live);
    printf("Ip protocol:  %02x\n", ip->protocol);
    printf("checksum ip:  %02x\n", ip->header_checksum);
    printf("Source address:\n");
    for(int i = 0; i < IP_ADDR_LEN; i++){
        printf("%02x ", ip->source_addr[i]);
    }printf("\n");
    printf("Destination address:\n");
    for(int i = 0; i < IP_ADDR_LEN; i++){
        printf("%02x ", ip->destination_addr[i]);
    }printf("\n");

    printf("\nUdp source address %04x ", udp->source_addr);
    printf("\nUdp destination address %04x", udp->destination_addr);
    printf("\nUdp length %04x", udp->length);
    printf("\nUdp Checksum %04x", udp->checksum);

}



/*END OF FILE*/
