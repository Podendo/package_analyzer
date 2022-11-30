#include "main.h"

void v_check_heads(void)
{
    ethernet_say_hi();
    ip_say_hi();
    udp_say_hi();
    img_reader_say_hi();
}


int main(int argc, char **argv)
{
    v_check_heads();

    if(argv[1] == NULL){
        printf("Error, give me a file path\n");
        printf("Given parameters: %i\n", argc);
        return 1;
    }

    printf("___________________________UDP PACK PARSE___________________________\n\n");
    struct udp_pack_data my_udp;
    int tmp = udp_pack_init(argv[1], &my_udp);
    if(tmp == PACK_ALLOC_SUCCESS){
        printf("\n tmp udp_pack_init result is: %d\n", tmp);
    }
    printf("udp_pack_size: %d\n", my_udp.size);

    udp_pack_parse(&my_udp);

    //udp_pack_print(&my_udp);

    tmp = udp_pack_deinit(&my_udp);
    if(tmp == PACK_FREE_SUCCESS){
        printf("\n tmp udp_pack_deinit result is: %d\n", tmp);
    }


    
    printf("\n\nSUCCESS!\n\n");

    return 0;
}

/*END OF FILE*/