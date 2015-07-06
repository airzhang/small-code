#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

#include "ec-gf.h"
#include "ec-method.h"

#if 0
int encode_mem(uint8_t** p_in, uint8_t** p_out, unsigned int size)
{
	p2 = realloc(*p_in, size);
	p1 = realloc(*p_out, size);

//	memset(*p_out, 1, size);

	return 0;
}
#endif


int main()
{
	struct timeval start, end;
	double interval;
	FILE* tmpf;
	int size_ref = 0;
	unsigned int expand_size = 0;

	uint32_t fragments = 3;
	uint32_t idx = 0;

	uint8_t* ptr_in = malloc(1);
	uint8_t* ptr_out = malloc(1);

	tmpf = fopen("e_time.txt", "a");
	while(fragments++ < 15)
	{
		size_ref = 0;
		fprintf(tmpf, "\n---------------fragments = %d ----------------\n", fragments);

		while(size_ref <= 10)
		{
			expand_size = (128 * 1024) * pow(2, size_ref);
	//		encode_mem(&ptr_in, &ptr_out, expand_size);

			ptr_in = realloc(ptr_in, expand_size);
			if(NULL == ptr_in)
			{
				printf("alloc ptr_in failed!!");
				goto out;
			}

			ptr_out = realloc(ptr_out, expand_size);
			if(NULL == ptr_out)
			{
				printf("alloc ptr_out failed!!");
				goto out;
			}

			gettimeofday(&start, NULL);
			ec_method_encode(expand_size, fragments, 0, ptr_in, ptr_out);
			gettimeofday(&end, NULL);

			interval = 1000000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
			fprintf(tmpf, "128K*(2^%d) = %f\n", size_ref, interval/1000.0);

			size_ref++;
		}
	}
out:
	fclose(tmpf);

	free(ptr_in);
	free(ptr_out);

	return 0;
}
