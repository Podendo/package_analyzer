#ifndef PACKAGE_H_
#define PACKAGE_H_

#define FILE_READ_SUCCESS 0
#define ERR_FILEREAD -1
#define ERR_CPBUFFER -2


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* this function takes of passed file as an argument
* and returns its size */

int package_get_size(char *f_pack_pointer);

/* this function takes two arguments: pointer to buffer
* and name of passed file. The return of this function
* is int which contains either 0 or error code */

int package_cp_buffer(char *f_pack_pointer, uint8_t *p_pack_buffer);

#endif
/*END OF FILE*/