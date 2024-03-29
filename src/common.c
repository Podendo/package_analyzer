
#include "common.h"

#include <stdio.h>

int package_get_size(char *file_pack_pointer)
{
	int package_size = 0;

	FILE *fp = NULL;
	fp = fopen(file_pack_pointer, "rb");
	if ( fp == NULL ) {
		return ERR_FILEREAD;
	}

	if ( fseek(fp, 0, SEEK_END) == -1 ) {
		return ERR_FILEREAD;
	}

	package_size = ftell(fp);
	if ( package_size == -1 ) {
        return ERR_FILEREAD;
	}

	if ( fclose(fp) != 0 ) {
		return ERR_FILEREAD;
	}

	return package_size;
}

uint8_t package_get_protocol(uint8_t *package_buffer, int buffer_size)
{
	uint8_t transport_protocol;
	if ( buffer_size < 0 ) {
		return 1;
	}
	transport_protocol = package_buffer[PACK_MINLEN - 1];

	return transport_protocol;
}


int package_cp_buffer(char *file_pack_pointer, uint8_t *p_pack_buffer)
{
	int package_size = 0;
	int return_value = 0;

	package_size = package_get_size(file_pack_pointer);
	if ( package_size == ERR_FILEREAD ) {
		return_value = ERR_FILEREAD;
		goto error_point;
	} else if ( package_size < PACK_MINLEN ) {
		return_value = ERR_WRONG_PACK;
		goto error_point;
	}

	FILE *fp;
	fp=fopen(file_pack_pointer, "rb");
	if ( fp == NULL ) {
		return_value = ERR_FILEREAD;
		goto error_point;
	}
	for ( int i = 0; i < package_size; i++ ) {
		p_pack_buffer[i] = (fgetc(fp));
	}

	return_value = FILE_READ_SUCCESS;

	error_point:
	fclose(fp);
	return return_value;
}


void package_buff_alloc(uint8_t **p_pack_buffer, int package_size)
{
	*p_pack_buffer = (uint8_t*)calloc(package_size, sizeof(uint8_t));
	return;
}


void package_buff_free(uint8_t **p_pack_buffer)
{
	free(*p_pack_buffer);
	return;
}

/*END OF FILE*/
