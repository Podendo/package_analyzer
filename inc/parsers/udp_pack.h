#ifndef UDP_PACK_H_
#define UDP_PACK_H_

#include <inttypes.h>
#include <sys/stat.h>
#include "common.h"
#include "ethernet.h"
#include "udp.h"
#include "ip.h"

struct udp_pack_data {
	uint32_t	size;
	void		*raw_data;
	void		*ntoh_data;
};

/** Returns size of package
 *
 * static int udp_pack_get_size(char *filename);
 *
 * Use udp_pack get size to determine how much memory
 * is required for udp_pack_data->raw_data/convdata
 * to storedumped package. Results store in size
 * allocates heap memory for raw/conv data, add check
 */
int udp_pack_init(char *filename, struct udp_pack_data *udp_pack_data);


/* Frees everything allocated in heap */
int udp_pack_deinit(struct udp_pack_data *udp_pack_data);

/**
 * main parser logic is implemented here. Stage by stage parse raw
 * datainto conv_data. Use inline functions to get offset to needed
 * structure in order to pass them to XXX_conv functions
*/
void udp_pack_parse(struct udp_pack_data *udp_pack_data);


/**
 * Based on conv data, prints all the fileds of ethernet, ip, udp
 * structs with filed name. Converted UDP data should be printed
 */
void udp_pack_print(struct udp_pack_data *udp_pack_data);

#endif /*UDP_PACK_H_*/
