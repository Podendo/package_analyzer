#include "main.h"

void v_check_heads(void)
{
    ethernet_say_hi();
    ip_say_hi();
    udp_say_hi();
    img_reader_say_hi();
}

int tmp_func_check(char **argv)
{
    int package_size = 0;
     uint8_t package_protocol = 0;

    package_size = package_get_size(argv[1]);
    if(package_size < 0){
        printf("\nError! Can't read this file!\n");
        return 1;
    }
    uint8_t *buffer;
    
    package_buff_alloc(&buffer, package_size);
    int rvalue  = package_cp_buffer(argv[1], buffer);
    printf("\n\n");
    for(int i = 0; i < package_size; i++){
        if((i)%8 == 0) printf("\n");
        printf("%02x ", buffer[i]);
    }

    package_protocol = package_get_protocol(buffer, package_size);
    printf("\npackage size is: %i bytes\n", package_size);
    printf("\n\n Package protocol is: %02x", package_protocol);
    printf("\n\nSUCCESS!\n\n");

    package_buff_free(&buffer);
    return rvalue;
}

int main(int argc, char **argv)
{
    v_check_heads();

    if(argv[1] == NULL){
        printf("Error, give me a file path\n");
        printf("Given parameters: %i\n", argc);
        return 1;
    }
    int tmp = tmp_func_check(argv);

    return tmp;
}

/*END OF FILE*/