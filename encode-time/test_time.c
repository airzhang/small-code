/*******************************************************************************
 * *   文件名称 : test_time.c 
 * *   作    者 : 郭家勇
 * *   创建时间 : 2015/06/01
 * *   文件描述 : 测试 ec_method_encode 函数在不同数据块的大小时的执行时间
 * *   版权声明 : Copyright (C) 2015-2016 湖南安存科技有限公司
 * *   修改历史 : 2015/06/01 1.01 通过循环多次再得到函数执行时间的平均值
 * *******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>

#include "ec-gf.h"
#include "ec-method.h"

#define LOOPNUM  1000

int main() {
	size_t size = 0;
	uint32_t columns = 4;
	uint32_t row = 0;
	uint8_t * in = NULL;
	uint8_t * out = NULL;
        uint64_t time_val = 0;

	struct timeval tv_start;
	struct timeval tv_end;
	
	//for(uint32_t i = (1024 * 128); i >= 128; i /= 2) {
	//数据块的大小从128K到128M，按2倍的关系递增
	for(uint32_t i = 128; i <= (128 * 1024); i *= 2) {
		for(uint32_t j = 0; j < LOOPNUM; j++) {
		        in = (uint8_t *)calloc((i * 1024), 1); 	
		        out = (uint8_t *)calloc((i * 1024), 1); 	
                        
			row = j % 5;
			size = i * 1024;

			gettimeofday(&tv_start, NULL);
        
			ec_method_encode(size, columns, row, in, out);
	
			gettimeofday(&tv_end, NULL);
			
			if(tv_end.tv_usec <= tv_start.tv_usec) {
				j--;
				free(in);
				free(out);
				continue;
			}

			time_val +=  (tv_end.tv_usec - tv_start.tv_usec); 

			free(in);
			free(out);
		}

                if( i >= (1024)) {
			printf("data-bricks=%dM\nfunction ec_method_encode Executive time : %d μs\n\n", (i/1024), (time_val/LOOPNUM));
			}
		else {
			printf("data-bricks=%dk\nfunction ec_method_encode Executive time : %d μs\n\n", i, (time_val/LOOPNUM));
		}
		
		time_val = 0;

	} 

	return 0;
}
