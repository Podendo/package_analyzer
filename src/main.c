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
    int package_size = 0;
    package_size = package_get_size(argv[1]);
    if(package_size < 0){
        printf("\nError! Can't read this file!\n");
        return 1;
    }

    printf("package size is: %i bytes\n", package_get_size(argv[1]));
    uint8_t *package = 0;
    package_cp_buffer(argv[1], package);

    printf("\n\nSUCCESS!\n\n");
    uint32_t byte = 0xAABBCCDD;
    printf("This is out: 0x%08x\n\n", NTOHL(byte));
    return 0;
}

/*END OF FILE*/