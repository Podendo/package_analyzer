#include "main.h"



int main(int argc, char **argv)
{
    
    if(argv[1] == NULL){
        printf("Error, give me a file path\n");
        printf("Given parameters: %i\n", argc);
        return 1;
    }

    struct udp_pack_data my_udp;
    int tmp = udp_pack_init(argv[1], &my_udp);
    if(tmp == PACK_ALLOC_SUCCESS){
        printf("\n tmp udp_pack_init result is: %d\n", tmp);
    }
    printf("udp_pack_size: %d\n", my_udp.size);

    udp_pack_parse(&my_udp);

    tmp = udp_pack_deinit(&my_udp);
    if(tmp == PACK_FREE_SUCCESS){
        printf("\n tmp udp_pack_deinit result is: %d\n", tmp);
    }


    return 0;
}

/*END OF FILE*/