#ifndef COMMON_H_
#define COMMON_H_

#define COMMON_CODE_PHRASE "It is common.h"

#define SWAP_BYTE(BITS_8)						\
									\
	 BITS_8 = ((BITS_8 & 0x01) << 7) | ((BITS_8 & 0x02) << 5) |	\
		((BITS_8 & 0x04) << 3) | ((BITS_8 & 0x08) << 1) |	\
		((BITS_8 & 0x80) >> 7) | ((BITS_8 & 0x40) >> 5) |	\
		((BITS_8 & 0x20) >> 3) | ((BITS_8 & 0x10) >> 1)		\


#define NTOHS(BITS_16)							\
									\
	BITS_16 = ((BITS_16 & 0xFF00) >> 8) |				\
		((BITS_16 & 0x00FF) << 8)				\


#define NTOHL(BITS_32)							\
									\
	BITS_32 = ((BITS_32 & 0xFF000000) >> 24) |			\
		((BITS_32 & 0x00FF0000) >> 8) |				\
		((BITS_32 & 0x0000FF00) << 8) |				\
		((BITS_32 & 0x000000FF) << 24)				\


#define PACK_16(VALUE, R_BYTE, L_BYTE)					\
	VALUE = (R_BYTE << 8) | (L_BYTE)				\


#define PACK_32(VALUE, R_BYTE, RC_BYTE, LC_BYTE, L_BYTE)		\
									\
	VALUE = (R_BYTE << 24) | (RC_BYTE << 16) |			\
		(LC_BYTE << 8) | (L_BYTE)				\


#define FILE_READ_SUCCESS		0
#define PACK_FREE_SUCCESS		2
#define PACK_ALLOC_SUCCESS		4

#define ERR_FILEREAD			-1
#define ERR_CPBUFFER			-2
#define ERR_NO_ALLOC			-3
#define ERR_WRONG_PACK			-4

#define PACK_MINLEN			0x18
#define PACK_HOPOPT			0x00
#define PACK_ICMP			0x01
#define PACK_IGMP			0x02
#define PACK_GGP			0x03
#define PACK_TCP			0x06
#define PACK_UDP			0x11
#define PACK_RDP			0x1B
#define PACK_DCCP			0x33
#define PACK_IPV6			0x29
#define PACK_UDPLite			0x88
#define PACK_ENCAP			0x29
#define PACK_OSPF			0x59
#define PACK_SCTP			0x84

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * this function takes of passed file as an argument
 * and returns its size
 */
int package_get_size(char *file_pack_pointer);

/**
 * this function indicates the transport layer
 * protocol: package must be >24 bytes length
 * for identification (ip address protocol frag)
 */
uint8_t package_get_protocol(uint8_t *package_buffer, int buffer_size);

/**
 * this function takes two arguments: pointer to buffer
 * and name of passed file. The return of this function
 * is int which contains either 0 or error code
 *
 * this function works with file, reads it, and
 * allocates memory for buffer
 */
int package_cp_buffer(char *file_pack_pointer, uint8_t *p_pack_buffer);

/**
 * Allocate memory for buffer according to package size
 */
void package_buff_alloc(uint8_t **p_pack_buffer, int package_size);

/**
 * Free allocated memory
 */
void package_buff_free(uint8_t **p_pack_buffer);
#endif /* COMMON_H_ */
