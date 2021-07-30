#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"
#include "multiply.h"
int find_max(int *arr, int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i ++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
int mult_razr(matr_t vector, matr_t matrix, matr_t *res, int len_v, int rows)
{
	if (rows != len_v)
	{
		printf("ERROR in mult\n");
		return 1;
	}
	int index = -1;
	int res_el = 0;
	int res_ind = 0;
	int len_res = find_max(matrix.ja, matrix.len_ja) + 1;
	res->a = malloc(sizeof(int) * len_res);
	res->ja = malloc(sizeof(int) * len_res);
	int i1, i2, counter;
	for (int i = 0; i < len_res; i ++)
	{
		res_el = 0;
		for (int j = 0; j < vector.len_a; j ++)
		{
			index = -1;
			i1 = matrix.ia[vector.ja[j]];
			i2 = matrix.ia[vector.ja[j] + 1];
			if (i2 == - 1)
			{	
				counter = 2;
				while (i2 == - 1)
				{
					i2 = matrix.ia[vector.ja[j] + counter];
					counter ++;
				}
			}
			if (i1 != - 1 && matrix.ja[i1] <= i)//if mistake, remove && i1 <= i
			{
				for (int k =i1; k < i2; k ++)
				{
					if (i == matrix.ja[k])
					{
						index = k;
						break;
					}
				}
				if (index != -1)
				{
					//printf("%d %d\n", vector.a[j], matrix.a[index]);				
					res_el += (vector.a[j] * matrix.a[index]);
				}
			}
		}		
		if (res_el)
		{
			res->a[res_ind] = res_el;	
			res->ja[res_ind] = i;
			res_ind ++;
		}
	}
	res->len_a = res_ind;
	res->len_ja = res_ind;
	return 0;
}
int mult_usual(usual_matr_t vector1, usual_matr_t matrix1, usual_matr_t *vector_res)
{
	int elem = 0;
	if (vector1.cols != matrix1.rows)
	{
		printf("ERROR: VECTOR COLUMNS != MATRIX ROWS\n");
		return 1;
	}	
	vector_res->rows = 1;
	vector_res->cols = matrix1.cols;
	for (int i = 0; i < matrix1.cols; i ++)
	{
		elem = 0;
		for (int j = 0; j < vector1.cols; j ++)
		{
			elem += (vector1.matrix[0][j] * matrix1.matrix[j][i]);
		}
		vector_res->matrix[0][i] = elem;
	}
	return 0;
}

