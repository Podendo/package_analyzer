#include "udp_pack.h"

static int udp_pack_get_size(char *filename)
{
    int package_size = 0;

    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if(fp == NULL){
        return ERR_FILEREAD;
    }

    if(fseek(fp, 0, SEEK_END) == -1){
        return ERR_FILEREAD;
    }

    package_size = ftell(fp);
    if(package_size == -1){
        return ERR_FILEREAD;
    }

    if(fclose(fp) != 0){
        return ERR_FILEREAD;
    }

    return package_size;
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
    int return_value, package_size, protocol_type;

    udp_pack_data->raw_data = NULL;
    udp_pack_data->ntoh_data = NULL;

    package_size = udp_pack_get_size(filename);

    if(package_size == ERR_FILEREAD){
        return_value = ERR_FILEREAD;
        return return_value;
    }
    
    udp_pack_data->size = package_size;

    udp_pack_data->raw_data = calloc(package_size, sizeof(uint8_t));
    udp_pack_data->ntoh_data = calloc(package_size, sizeof(uint8_t));
    
    if((udp_pack_data->raw_data == NULL) && (udp_pack_data->ntoh_data == NULL)){
        return_value = ERR_NO_ALLOC;
        return return_value;
    }
    if(package_cp_buffer(filename, udp_pack_data->raw_data) != 0){
        return_value = ERR_CPBUFFER;
        return return_value;
    }
    
    protocol_type = package_get_protocol(udp_pack_data->raw_data, package_size);
    if(protocol_type == 0x11){
        return_value = ERR_WRONG_PACK;
        return return_value;
    }
    
    return_value = PACK_ALLOC_SUCCESS;

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
    struct protocol_eth *raw_eth;
    struct protocol_eth *conv_eth;

    struct protocol_ip *raw_ip;
    struct protocol_ip *conv_ip;

    struct protocol_udp *raw_udp;
    struct protocol_udp *conv_udp;

    raw_eth = udp_pack_eth_from_raw(udp_pack_data);

    raw_ip = udp_pack_ip_from_eth(raw_eth);

    if(raw_ip->protocol != 0x11){
        printf("\nerror, this is not udp\n");
        return;
    }

    raw_udp = udp_pack_udp_from_eth(raw_eth);

    conv_eth = (struct protocol_eth*)udp_pack_data->ntoh_data;

    conv_ip =  udp_pack_ip_from_eth(conv_eth);
    conv_udp = udp_pack_udp_from_eth(conv_eth);

    eth_conv(raw_eth, conv_eth);
    ip_conv(raw_ip, conv_ip);
    udp_conv(raw_udp, conv_udp);

    udp_pack_print(udp_pack_data);

    return;
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

    printf("\nPackage total size: %d bytes\n\n", udp_pack_data->size);
/*
    printf("\n\nNTOH DATA:\n");
    printf("\nPackage size: %d\n", udp_pack_data->size);
    for(uint32_t i = 0; i < udp_pack_data->size; i++){
        if(i % 8 == 0) printf("\t");
        if(i % 16 == 0) printf("\n");
        printf("%02x ", udp_pack_data->raw_data[i]);
    }
*/
    printf("\n\nEthernet protocol:\n");

    printf("ethernet source address:\t");

    for(int i = 0; i < ETH_ADDR_LEN; i++){
            printf("%02x:",eth->source_addr[i]);
    } printf("\n");
        
    printf("ethernet destination address:\t");

    for(int i = 0; i < ETH_ADDR_LEN; i++){
                printf("%02x:",eth->destination_addr[i]);
    } printf("\n");

    printf("Ethernet type: 0x%04x\n ",eth->type);


    printf("\nIP protocol: \n");

    printf("ip version:  0x%02x\n", ip->version);
    printf("ip Type of service:  0x%02x\n", ip->type_of_sevice);

    printf("ip Length:  %d\n", ip->length);
    printf("ip identification:  0x%04x\n", ip->identification);

    printf("ip flags:  0x%04x\n", ip->flags);
    printf("ip time to live:  0x%02x\n", ip->time_to_live);

    printf("ip protocol:  0x%02x\n", ip->protocol);
    printf("checksum ip:  0x%02x\n", ip->header_checksum);
    
    printf("\nip source address:\t");
    for(int i = 0; i < IP_ADDR_LEN; i++){
        printf("%d:", ip->source_addr[i]);
    }printf("\n");

    printf("ip destination address:\t");
    for(int i = 0; i < IP_ADDR_LEN; i++){
        printf("%d:", ip->destination_addr[i]);
    }printf("\n\n");

    printf("\nUDP Protocol:\n");

    printf("\nudp source address: 0x%04x ", udp->source_addr);
    printf("\nudp destination address: 0x%04x", udp->destination_addr);
    printf("\nudp length: %d (bytes)", udp->length);
    printf("\nudp checksum: 0x%04x", udp->checksum);

    printf("\nudp data:\n");
    for(int i = 0; i < udp->length - UDP_HEADER_SIZE; i++){
        if(i % 8 == 0) printf("\t");
        if(i % 16 == 0) printf("\n");
        printf("%02x ", udp->data[i]);
    }

}

/*END OF FILE*/
