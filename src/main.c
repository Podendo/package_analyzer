#include "main.h"



int main(int argc, char **argv)
{
	struct udp_pack_data my_udp;
	int pack = 0;

	if ( argv[1] == NULL ) {
		printf("Error, give me a file path\n");
		printf("Given parameters: %i\n", argc);
		return 1;
	}

	pack = udp_pack_init(argv[1], &my_udp);
	if ( pack == PACK_ALLOC_SUCCESS) {
		printf("\n tmp udp_pack_init result is: %d\n", pack);
	}
	printf("udp_pack_size: %d\n", my_udp.size);

	udp_pack_parse(&my_udp);

	pack = udp_pack_deinit(&my_udp);
	if ( pack == PACK_FREE_SUCCESS ) {
		printf("\n tmp udp_pack_deinit result is: %d\n", pack);
	}

	return 0;
}

/*END OF FILE*/
