/*
**calucate the time of encode_method
**
**
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

#include "ec-gf.h"
#include "ec-method.h"

#define LOOPTIME 1000	//to calculate the average result of the encoding

int main()
{
//	struct timeval start, end;
	struct timespec tpstart;
        struct timespec tpend;
	double interval;
	FILE* tmpf;
	int size_ref = 0;
	unsigned int expand_size = 0;

	uint32_t fragments = 3;		//number of fragments
	uint32_t idx = 0;		//the idx of bricks

	uint8_t* ptr_in = malloc(1);
	uint8_t* ptr_out = malloc(1);

	tmpf = fopen("time1000.txt", "a");

	//the size to calculate
	while(size_ref++ <= 10)
	{
		fragments = 2;
		expand_size = (128 * 1024) * pow(2, size_ref);
		fprintf(tmpf, "\n");

		//the fragments between 3 to 15
		while(fragments++ < 6)
		{
			int i=0;
			interval = 0.0;
			while(i++ < LOOPTIME)
			{
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
				
				idx = i % (fragments + 1);
 
				clock_gettime(CLOCK_MONOTONIC, &tpstart);
			//	gettimeofday(&start, NULL);
				ec_method_encode(expand_size, fragments, idx, ptr_in, ptr_out);
			//	gettimeofday(&end, NULL);
        			clock_gettime(CLOCK_MONOTONIC, &tpend);

				interval += (1000000*(tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec)/1000);
			}
			fprintf(tmpf, "%f\t", interval/LOOPTIME/1000.0);
		}
	}
out:
	fclose(tmpf);

	free(ptr_in);
	free(ptr_out);

	return 0;
}
