#include "package.h"
#include "common.h"

int package_get_size(char *f_pack_pointer)
{
    int package_size = 0;
    char package_data = 0;

    FILE *fp;
    fp=fopen(f_pack_pointer, "rb");
    if(fp == NULL){
        return ERR_FILEREAD;
    }

    while(package_data != EOF){
        package_data = fgetc(fp);
        package_size += 1;
    }
    fclose(fp);

    return package_size;
}


int package_cp_buffer(char *f_pack_pointer, uint8_t *p_pack_buffer)
{
    int package_size = 0;
    int return_value = 0;

    package_size = package_get_size(f_pack_pointer);
    if(package_size == ERR_FILEREAD){
        return_value = ERR_FILEREAD;
        goto error_point;
    }
    
    p_pack_buffer = (uint8_t*)calloc(package_size, sizeof(uint8_t));
    FILE *fp;
    fp=fopen(f_pack_pointer, "rb");
    if(fp == NULL){
        return_value = ERR_FILEREAD;
    }

    for(int i = 0; i < package_size - 1; i++){
        p_pack_buffer[i] = (fgetc(fp));
        printf("%x", p_pack_buffer[i]);
    }

    error_point:
    fclose(fp);
    free(p_pack_buffer);
    return_value = FILE_READ_SUCCESS;
    return return_value;
}

/*END OF FILE*/