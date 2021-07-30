#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "../inc/funcs.h"
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
int main()
{
	int check;
	char filename[50] = "test/in4.txt";
	sm_matr_t *sm_matrix = NULL;
	sm_matr_t *sm_matrix_copy = NULL;
	int a_city, b_city;
	uint64_t start, stop;
	int edge_connection = 0;


	check = input_data(filename, &sm_matrix);
	if (check == 1)
	{
		return 1;
	}
	matr_copy(sm_matrix, &sm_matrix_copy);
	graph_viz(sm_matrix_copy);
	destroy_matr(&sm_matrix_copy);
	printf("Input a and b cities\n");
	if (input_a_b_cities(&a_city, &b_city))	
	{
		return 1;
	}
	if (a_city >= sm_matrix->size || b_city >= sm_matrix->size)
	{
		printf("Incorrect input of cities\n");
		return 1;
	}
	matr_copy(sm_matrix, &sm_matrix_copy);
	if (!route_exists_classic(sm_matrix_copy, a_city, b_city))
	{
		printf("There is no way from a to b\n");
		return 1;
	}
	int **bridges = malloc(sizeof(int *) * 3);
	destroy_matr(&sm_matrix_copy);
	for (int i = 0; i < 3; i ++)
	{
		bridges[i] = malloc(sizeof(int) * 2);
		if (!bridges[i])
		{
			printf("Error in alloc\n");
			return 1;
		}
	}

	start = tick();
	check = big_perebor(sm_matrix, bridges, a_city, b_city);
	stop = tick();
	if (check == 1)
	{
		printf("Time for this operation %ju\n", stop - start);
		final_graph_viz(sm_matrix, bridges, 3);
	}
	else
		printf("It's impossible\n");
	return 0;
}
