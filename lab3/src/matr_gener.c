#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"
#include "matr_gener.h"
#define MAX_MULT_FIG 100
int check_random(int *array, int current_ind, int elem)
{
	int flag = 0;
	for (int i = 0; i < current_ind; i ++)
	{
		if (array[i] == elem)
		{
			return -1;
		}
	}
	return 0;
}
int input_gener_vect(int vect_size, int vect_percent, char filename[], int *non_zero_els, int *len_v)
{
	FILE *f;
	*len_v = vect_size;
	int index;
	int *index_array; 
	if (vect_size < 100)
	{
		*non_zero_els = (double)vect_size / 100 * vect_percent;
	}
	else
	{
		*non_zero_els = vect_size / 100 * vect_percent;
	}
	index_array = malloc(sizeof(int) * (*non_zero_els + 2));
	if (!index_array)
	{
		printf("ERROR IN MEMORY\n");
		return 1;
	}
	index_array[0] = -1;
	int *arr = calloc(*len_v, sizeof(int));
	if (arr == NULL)
	{
		printf("MEMORY ERROR\n");
		return 1;
	}
	f = fopen(filename,"w");
	fprintf(f, "%d\n", *len_v); 
	for (int i = 0; i < *non_zero_els; i ++)
	{
		index = (int)fabs(rand() % *len_v);
		while (1)
		{
			if (check_random(index_array, i + 1, index) == 0)
			{
				index_array[i + 1] = index;
				break;
			}
			index = (int)fabs(rand() % *len_v);
		} 
		arr[index] = rand()  % MAX_MULT_FIG + 1;
	}
	for (int i = 0; i < *len_v; i ++)
	{
		fprintf(f, "%d ", arr[i]);
	}
	free(arr);
	free(index_array);
	fclose(f);
	return 0;
}
int input_gener_usual_vect(int vect_size, int vect_percent, usual_matr_t *vector)
{
	vector->cols = vect_size;
	vector->rows = 1;
	int non_zero_els;
	int index;
	int *index_array;
	if (vect_size < 100)
	{
		non_zero_els = (double)vect_size / 100 * vect_percent;
	}
	else
	{
		non_zero_els = vect_size / 100 * vect_percent;
	}
	index_array = malloc(sizeof(int) * (non_zero_els + 2));
	if (!index_array)
	{
		printf("ERROR IN MEMORY\n");
		return 1;
	}
	index_array[0] = -1;
	int *arr = calloc(vect_size, sizeof(int));
	if (arr == NULL)
	{
		printf("MEMORY ERROR\n");
		return 1;
	}
	for (int i = 0; i < non_zero_els; i ++)
	{
		index = (int)fabs(rand() % vect_size);
		while (1)
		{
			if (check_random(index_array, i + 1, index) == 0)
			{
				index_array[i + 1] = index;
				break;
			}
			index = (int)fabs(rand() % vect_size);
		}
		arr[index] = rand() % MAX_MULT_FIG + 1;
	}
	for (int i = 0; i < vect_size; i ++)
	{
		vector->matrix[0][i] = arr[i];
	}
	free(arr);
	return 0;	
}
int input_gener_matr(int matr_size, int matr_percent, char filename[], int *non_zero_els, int *rows, int *cols)
{
	FILE *f;
	*rows = matr_size;
	*cols = matr_size;
	*non_zero_els = matr_size * matr_size / 100 * matr_percent;
	int *arr = NULL;
	int index;
	int *index_array = NULL;
	if  (matr_percent == 100)
	{
		f = fopen(filename, "w");
		fprintf(f, "%d\n%d\n", matr_size, matr_size);
		for (int i = 0; i < matr_size; i ++)
		{
			for (int j = 0; j < matr_size; j ++)
			{
				fprintf(f, "%d ", rand()  % MAX_MULT_FIG + 1);
			}
			fprintf(f, "\n");
		}
	}
	else
	{

		arr = calloc(matr_size * matr_size, sizeof(int));
		if (!arr)
		{
			printf("ERROR IN MEMORY\n");
			return 1;
		}
		index_array = malloc(sizeof(int) * (*non_zero_els + 2));
		if (!index_array)
		{
			free(arr);
			printf("ERROR IN MEMORY\n");
			return 1;
		}
		index_array[0] = -1;
		for (int j = 0; j < *non_zero_els; j ++)
		{
			index = (int)fabs(rand() % (matr_size * matr_size));
			while (1)
			{
				if (check_random(index_array, j + 1, index) == 0)
				{
					index_array[j + 1] = index;
					break;
				}
				index = (int)fabs(rand() % (matr_size * matr_size));
			}
			arr[index] = rand()  % MAX_MULT_FIG + 1;
		}
		printf("SUCCESS GENERATED\n");
		f = fopen(filename, "w");
		fprintf(f, "%d\n%d\n", matr_size, matr_size);
		for (int i = 0; i < matr_size; i ++)
		{
			for (int j = 0; j < matr_size; j ++)
			{
				fprintf(f, "%d ", arr[i * matr_size + j]);
			}
			fprintf(f, "\n");
		}
	}
	free(arr);
	fclose(f);
	return 0;
}
int input_gener_usual_matrix(int matr_size, int matr_percent, usual_matr_t *matrix)
{
	matrix->rows = matr_size;
	matrix->cols = matr_size;
	int non_zero_els = matr_size * matr_size / 100 * matr_percent;
	int *arr;
	int index;
	int *index_array;
	if (matr_percent == 100)
	{
		for (int i = 0; i < matr_size; i ++)
		{
			
			for (int j = 0; j < matr_size; j ++)
			{
				matrix->matrix[i][j] = rand()  % MAX_MULT_FIG + 1;
			}
		}
	}
	else
	{

		arr = calloc(matr_size * matr_size, sizeof(int));
		if (!arr)
		{
			printf("ERROR IN MEMORY\n");
			return 1;
		}
		index_array = malloc(sizeof(int) * (non_zero_els + 2));
		if (!index_array)
		{
			free(arr);
			printf("ERROR IN MEMORY\n");
			return 1;
		}
		index_array[0] = -1;
		for (int j = 0; j < non_zero_els; j ++)
		{
			index = (int)fabs(rand() % (matr_size * matr_size));
			while (1)
			{
				if (check_random(index_array, j + 1, index) == 0)
				{
					index_array[j + 1] = index;
					break;
				}
				index = (int)fabs(rand() % (matr_size * matr_size));
			}
			arr[index] = rand()  % MAX_MULT_FIG + 1;
		}
		for (int i = 0; i < matr_size; i ++)
		{
			
			for (int j = 0; j < matr_size; j ++)
			{
				matrix->matrix[i][j] = arr[j];
			}
		}
	}
	return 0;
}

