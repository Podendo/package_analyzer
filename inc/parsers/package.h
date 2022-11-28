#ifndef PACKAGE_H_
#define PACKAGE_H_

#define FILE_READ_SUCCESS   0
#define PACK_FREE_SUCCESS   2
#define PACK_ALLOC_SUCCESS  4

#define ERR_FILEREAD    -1
#define ERR_CPBUFFER    -2
#define ERR_NO_ALLOC    -3
#define ERR_WRONG_PACK  -4

#define PACK_MINLEN      0x18
#define PACK_HOPOPT      0x00
#define PACK_ICMP        0x01
#define PACK_IGMP        0x02
#define PACK_GGP         0x03
#define PACK_TCP         0x06
#define PACK_UDP         0x11
#define PACK_RDP         0x1B
#define PACK_DCCP        0x33
#define PACK_IPV6        0x29
#define PACK_UDPLite     0x88
#define PACK_ENCAP       0x29
#define PACK_OSPF        0x59
#define PACK_SCTP        0x84

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


/* this function takes of passed file as an argument
* and returns its size 
*/
int package_get_size(char *file_pack_pointer);

/** this function indicates the transport layer 
 *  protocol: package must be >24 bytes length
 *  for identification (ip address protocol frag)
*/
uint8_t package_get_protocol(uint8_t *package_buffer, int buffer_size);

/* this function takes two arguments: pointer to buffer
* and name of passed file. The return of this function
* is int which contains either 0 or error code
*
* this function works with file, reads it, and
* allocates memory for buffer 
*/
int package_cp_buffer(char *file_pack_pointer, uint8_t *p_pack_buffer);

/** Allocate memory for buffer according to package size
*/
void package_buff_alloc(uint8_t **p_pack_buffer, int package_size);

/** Free allocated memory
*/
void package_buff_free(uint8_t **p_pack_buffer);
#endif
/*END OF FILE*/