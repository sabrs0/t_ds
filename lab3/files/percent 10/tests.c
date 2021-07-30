#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MATRSIZE 500
typedef struct
{
	int *a;
	int len_a;

	int *ja;
	int len_ja;

	int *ia;
	int len_ia;
}matr_t;
typedef struct
{
	int matrix[MATRSIZE][MATRSIZE];
	int rows;
	int cols;
}usual_matr_t;
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
int mult_razr(matr_t vector, matr_t matrix, matr_t *res, int len_v, int rows, FILE *f)
{
	if (rows != len_v)
	{
		printf("ERROR in mult\n");
		return 1;
	}
	double res_time;
	int index = -1;
	int res_el = 0;
	int res_ind = 0;
	clock_t start, stop;
	int len_res = find_max(matrix.ja, matrix.len_ja) + 1;
	res->a = malloc(sizeof(int) * len_res);
	res->ja = malloc(sizeof(int) * len_res);
	int i1, i2, counter;
	start = clock();
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
			if (i1 != - 1 && matrix.ja[i1] <= i)
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
	stop = clock();
	res_time = (double)(stop - start)/ CLOCKS_PER_SEC;
	fprintf(f, "\tTIME FOR SPARSE OPERATION: %lf (s)\n",  res_time);
	res->len_a = res_ind;
	res->len_ja = res_ind;
	return 0;
}
int input_vector(int *len_v, char filename[], int *non_zero_els)
{
	int check;
	int scanner;
	int flag_non_zero = 0;
	FILE *f;
	f = fopen(filename, "r");
	printf("INPUT SIZE OF VECTOR:\n");
	check = fscanf(f, "%d", len_v);
	if (check != 1)
	{
		return 1;
	}
	if (*len_v <= 0)
	{
		return 1;
	}
	printf("INPUT VECTOR (%d elements):\n", *len_v);
	for (int i = 0; i < *len_v;  i++)
	{
		check = fscanf(f, "%d", &scanner);
		if (check != 1)
		{
			return 1;
		}
		if (scanner)
		{
			(*non_zero_els) ++;
		}
	}
	fclose(f);
	return 0;

}
int init_vector(int len_v, matr_t *vector, char filename[], int non_zero_els)
{
	printf("NON ZERO ELS = %d\n", non_zero_els);
	
	int check;
	int scanner;
	int a_ind = 0;
	int flag_non_zero = 0;
	FILE *f;
	vector->a = malloc(sizeof(int) * non_zero_els);
	if (!(vector->a))
	{
		free(vector->a);
		return 1;
	}
	vector->ja = malloc(sizeof(int) * non_zero_els);
	if (!(vector->ja))
	{
		free(vector->a);
		free(vector->ja);
		return 1;
	}	
	f = fopen(filename, "r");
	check = fscanf(f, "%d", &len_v);
	if (check != 1)
	{
		return 1;
	}
	for (int i = 0; i < len_v;  i ++)
	{
		check = fscanf(f, "%d", &scanner);
		if (check != 1)
		{
			return 1;
		}
		if (scanner)
		{
			vector->a[a_ind] = scanner;
			vector->ja[a_ind] = i;
			a_ind ++;
		}
	}
	vector->len_a = a_ind;
	vector->len_ja = a_ind;

	fclose(f);
	return 0;	
}
int input_matr(int *rows, int *cols, char filename[], int *non_zero_els)
{
	int check;
	int scanner;
	int a_ind = 0;
	int ia_ind = 0;
	int flag_non_zero = 0;
	FILE *f;
	f = fopen(filename, "r");	
	printf("INPUT ROWS AND COLS OF MATRIX:\n");
	check = fscanf(f, "%d", rows);
	if (check != 1)
	{
		return 1;
	}
	check = fscanf(f, "%d", cols);
	if (check != 1)
	{
		return 1;
	}
	if (*rows <= 0 || *cols <= 0)
	{
		return 1;
	}
	printf("INPUT MATRIX %d x %d:\n", *rows, *cols);
	for (int i = 0; i < *rows;  i++)
	{
		flag_non_zero = 0;
		for (int j = 0; j < *cols; j ++)
		{
			check = fscanf(f, "%d", &scanner);
			if (check != 1)
			{
				return 1;
			}
			if (scanner)
			{
				(*non_zero_els) ++;
			}
		}
	}
	fclose(f);
	return 0;
}
//ВАЖНО!!!! IA содержит ИНДЕКСЫ JA, а не его значения!!!!!!!
int init_matr(int rows, int cols, matr_t *matrix, char filename[], int non_zero_els)
{
	printf("NON ZERO ELS = %d\n", non_zero_els);
	int *tmp_a, *tmp_ja, *tmp_ia;
	int check;
	int scanner;
	int a_ind = 0;
	int ia_ind = 0;
	int flag_non_zero = 0;
	FILE *f;
	printf("CHECK@\n");
	tmp_a = malloc(sizeof(int) * non_zero_els);
	printf("CHECK2\n");
	if (tmp_a == NULL)
	{
		return 1;
	}
	matrix->a = tmp_a;	
	tmp_ja = malloc(sizeof(int) * non_zero_els);
	if (!tmp_ja)
	{
		free(matrix->a);
		return 1;
	}
	matrix->ja = tmp_ja;	
	tmp_ia = calloc(rows + 1, sizeof(int));
	if (!tmp_ia)
	{
		free(matrix->a);
		free(matrix->ja);
		return 1;
	}
	matrix->ia = tmp_ia;
	f = fopen(filename, "r");
	check = fscanf(f, "%d", &rows);
	if (check != 1)
	{
		return 1;
	}
	check = fscanf(f, "%d", &cols);
	if (check != 1)
	{
		return 1;
	}
	if (rows <= 0 || cols <= 0)
	{
		return 1;
	}
	for (int i = 0; i < rows;  i++)
	{
		flag_non_zero = 0;
		for (int j = 0; j < cols; j ++)
		{
			check = fscanf(f, "%d", &scanner);
			if (check != 1)
			{
				return 1;
			}
			if (scanner)
			{
				matrix->a[a_ind] = scanner;
				matrix->ja[a_ind] = j;
				a_ind ++;
				if (flag_non_zero == 0)
				{
					flag_non_zero = 1;
					matrix->ia[ia_ind] = a_ind - 1;
					ia_ind ++;
				}
			}
		}
		if (!flag_non_zero)
		{
			matrix->ia[ia_ind] =  -1;
			ia_ind ++;
		}
	}
	matrix->ia[ia_ind] = a_ind;
	ia_ind ++;
	
	matrix->len_a = a_ind;
	matrix->len_ja = a_ind;
	matrix->len_ia = ia_ind;

	fclose(f);

	return 0;	
}
void print_razr_matr(matr_t matrix)
{
	if (!matrix.len_a)
	{
		printf("MATRIX IS NULL\n");
	}
	else
	{
		printf("A[%d]:\n", matrix.len_a);
		for (int i = 0; i < matrix.len_a; i ++)
		{
			printf("%d ", matrix.a[i]);
		}
		printf("\n\n");
		printf("JA[%d]:\n", matrix.len_ja);
		for (int i = 0; i < matrix.len_ja; i ++)
		{
			printf("%d ", matrix.ja[i]);
		}
		printf("\n\n");
		printf("IA[%d]:\n", matrix.len_ia);
		for (int i = 0; i < matrix.len_ia; i ++)
		{
			printf("%d ", matrix.ia[i]);
		}
		printf("\n\n");
	}
}
void print_razr_vect(matr_t matrix)
{
	if (!matrix.len_a)
	{
		printf("MATRIX IS NULL\n");
	}
	else
	{

		printf("A[%d]:\n", matrix.len_a);
		for (int i = 0; i < matrix.len_a; i ++)
		{
			printf("%d ", matrix.a[i]);
		}
		printf("\n\n");
		printf("JA[%d]:\n", matrix.len_ja);
		for (int i = 0; i < matrix.len_ja; i ++)
		{
			printf("%d ", matrix.ja[i]);
		}
		printf("\n\n");
	}
}
int input_usual_matr(usual_matr_t *matr_str, char filename[])
{
	int check;
	int scanner;
	FILE *f;
	f = fopen(filename, "r");	
	printf("INPUT ROWS AND COLS OF MATRIX:\n");
	check = fscanf(f, "%d", &(matr_str->rows));
	if (check != 1)
	{
		return 1;
	}
	check = fscanf(f, "%d", &(matr_str->cols));
	if (check != 1)
	{
		return 1;
	}
	if (matr_str->rows <= 0 || matr_str->cols <= 0)
	{
		return 1;
	}
	printf("INPUT MATRIX %d x %d:\n", matr_str->rows, matr_str->cols);
	for (int i = 0; i < matr_str->rows;  i++)
	{
		for (int j = 0; j < matr_str->cols; j ++)
		{
			check = fscanf(f, "%d", &(matr_str->matrix[i][j]));
			if (check != 1)
			{
				return 1;
			}
		}
	}
	fclose(f);
	return 0;
}
int input_usual_vect(usual_matr_t *vect_str, char filename[])
{
	int check;
	int scanner;
	FILE *f;
	f = fopen(filename, "r");	
	printf("INPUT LENGTH OF VECTOR:\n");
	check = fscanf(f, "%d", &(vect_str->cols));
	if (check != 1)
	{
		return 1;
	}
	if (vect_str->cols <= 0)
	{
		return 1;
	}
	printf("INPUT VECTOR (%d elements):\n", vect_str->cols);
	for (int i = 0; i < vect_str->cols;  i++)
	{
			check = fscanf(f, "%d", &(vect_str->matrix[0][i]));
			if (check != 1)
			{
				return 1;
			}
	}
	vect_str->rows = 1;
	return 0;
}
void print_usual_matr(usual_matr_t matr)
{
	if (matr.rows == 1)
	{
		printf("VECTOR (%d elements):\n", matr.cols);
		for (int i = 0; i < matr.cols; i ++)
		{
			printf("%d ", matr.matrix[0][i]);
		}
		printf("\n");
	}
	else
	{
		printf("MATRIX %d X %d:\n", matr.rows, matr.cols);
		for (int i = 0; i < matr.rows; i ++)
		{
			for (int j =0; j < matr.cols; j ++)
			{
				printf("%d ", matr.matrix[i][j]);
			}
			printf("\n");
		}
	}
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
int main()
{
	clock_t start, stop;
	double res_time;
	matr_t matrix;
	matr_t vector;
	matr_t vector_res;

	usual_matr_t matrix1;
	usual_matr_t vector1;
	usual_matr_t vector_res1;

	int rows, cols, non_zero_els = 0;

	int len_v, non_zero_els3 = 0;

	int check, choice;	
	int m[3] = {10, 100, 500};
	char filename[256] = "1.txt";
	char filename2[256] = "1v.txt";
	FILE *f;
	f = fopen("res.txt", "w");
	fprintf(f, "20 prcnt\n");
	for (int i = 0; i < 3; i ++)
	{
		fprintf(f, "%d X %d\n", m[i], m[i]);
			check = input_vector(&len_v, filename2, &non_zero_els3);
			if (check)
			{
				printf("ERROR IN INPUT SPARSE VECTOR\n");
				return 1;
			}
			check = init_vector(len_v, &vector, filename2, non_zero_els3);
			if (check)
			{
				printf("ERROR IN INITIALIZE SPARSE VECTOR\n");
				return 1;
			}
			print_razr_vect(vector);


			check = input_matr(&rows, &cols, filename, &non_zero_els);
			if (check)
			{
				printf("ERROR IN INPUT SPARSE MATRIX\n");
				return 1;
			}			
			check = init_matr(rows, cols, &matrix, filename, non_zero_els);
			
			if (check)
			{
				printf("ERROR IN INITIALIZE SPARSE MATRIX\n");
				return 1;
			}
			print_razr_matr(matrix);
			check = mult_razr(vector, matrix, &vector_res, len_v, rows, f);
			if (check)
			{
				printf("ERROR IN SPARSE MULTIPLICATION\n");
				return 1;
			}
			printf("RESULT(SPARSE):\n");
			print_razr_vect(vector_res);
			
			check = input_usual_vect(&vector1, filename2);
			if (check)
			{
				printf("ERROR IN INPUT USUAL VECTOR\n");
				return 1;
			}
			print_usual_matr(vector1);


			check = input_usual_matr(&matrix1, filename);
			if (check)
			{
				printf("ERROR IN INPUT USUAL MATRIX\n");
				return 1;
			}			
			print_usual_matr(matrix1);
			start = clock();
			check = mult_usual(vector1, matrix1, &vector_res1);
			if (check)
			{
				printf("ERROR IN usual MULTIPLICATION\n");
				return 1;
			}
			stop = clock();
			res_time = (double)(stop - start)/ CLOCKS_PER_SEC;
			printf("RESULT(USUAL):\n");
			print_usual_matr(vector_res1);
			fprintf(f, "\tTIME FOR USUAL OPERATION: %lf (s)\n",  res_time);
			filename[0] = filename[0] + 1;
			filename2[0] = filename2[0] + 1;
	}
}
