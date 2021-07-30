#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"
#include "matr_io.h"
int input_vector(int *len_v, char filename[], int *non_zero_els)
{
	int check;
	int scanner;
	int flag_non_zero = 0;
	FILE *f;	
	printf("INPUT SIZE OF VECTOR:\n");
	check = scanf("%d", len_v);
	if (check != 1)
	{
		return 1;
	}
	if (*len_v <= 0)
	{
		return 1;
	}
	f = fopen(filename, "w");
	fprintf(f, "%d\n", *len_v);
	printf("INPUT VECTOR (%d elements):\n", *len_v);
	for (int i = 0; i < *len_v;  i++)
	{
		check = scanf("%d", &scanner);
		if (check != 1)
		{
			return 1;
		}
		fprintf(f, "%d ", scanner);
		if (scanner)
		{
			(*non_zero_els) ++;
		}
		fprintf(f, "\n");
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
		if (scanner != 0)
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
int generate_usual_vector(usual_matr_t *vector)
{
	int check;
	int scanner;
	int flag_non_zero = 0;
	FILE *f;
	int *col_ind = NULL;
	int *elems = NULL;
	printf("INPUT SIZE OF VECTOR:\n");
	vector->rows = 1;
	int non_zero_els;
	check = scanf("%d", &(vector->cols));
	if (check != 1)
	{
		return 1;
	}
	if (vector->cols <= 0 || MATRSIZE < vector->cols)
	{
		return 1;
	}
	printf("INPUT AMOUNT OF NON_ZERO ELEMENTS:\n");
	check = scanf("%d", &non_zero_els);
	if (check != 1)
	{
		return 1;
	}
	if (non_zero_els < 0)
	{
		printf("INCORRECT INPUT OF AMOUNT\n");
		return 1;
	}
	printf("format of input: index = j, elem = 1\n");
	printf("INPUT NON-ZERO ELEMENTS (%d elements):\n", non_zero_els);
	col_ind = malloc(sizeof(int) * non_zero_els);
	if (col_ind == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	elems = malloc(sizeof(int) * non_zero_els);
	if (elems == NULL)
	{
		free(col_ind);
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	for (int i = 0; i < non_zero_els;  i++)
	{
		check = scanf("%d", &(col_ind[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i == 0 && (col_ind[i] < 0 || col_ind[i] >= vector->cols))
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i != 0 && (col_ind[i] < 0 || col_ind[i] >= vector->cols || col_ind[i] <= col_ind[i - 1]))
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		check = scanf("%d", &(elems[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		if (elems[i] == 0)
		{
			printf("ERROR , ZERO ELEMENT INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		printf("\n");
		
	}
	int flag = 0;
	for (int i = 0; i < vector->cols; i ++)
	{
		flag = 0;
		for (int j = 0; j < non_zero_els; j ++)
		{
			if (i == col_ind[j])
			{
				flag = 1;
				vector->matrix[0][i] = elems[j];
				break;
			}
		}
		if (!flag)
		{
			vector->matrix[0][i] = 0;
		}
	}
	free(elems);
	free(col_ind);
	return 0;
}

int generate_vector(int *len_v, char filename[], int *non_zero_els)
{
	int check;
	int scanner;
	int flag_non_zero = 0;
	FILE *f;
	int *col_ind = NULL;
	int *elems = NULL;
	printf("INPUT SIZE OF VECTOR:\n");
	check = scanf("%d", len_v);
	if (check != 1)
	{
		return 1;
	}
	if (*len_v <= 0)
	{
		return 1;
	}
	printf("INPUT AMOUNT OF NON_ZERO ELEMENTS:\n");
	check = scanf("%d", non_zero_els);
	if (check != 1)
	{
		return 1;
	}
	if (*non_zero_els < 0 || *non_zero_els > *len_v)
	{
		printf("INCORRECT INPUT OF AMOUNT\n");
		return 1;
	}
	printf("format of input: index = j, elem = 1\n");
	printf("INPUT NON-ZERO ELEMENTS (%d elements):\n", *non_zero_els);
	col_ind = malloc(sizeof(int) * *non_zero_els);
	if (col_ind == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	elems = malloc(sizeof(int) * *non_zero_els);
	if (elems == NULL)
	{
		free(col_ind);
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	for (int i = 0; i < *non_zero_els;  i++)
	{
		check = scanf("%d", &(col_ind[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i == 0 && (col_ind[i] < 0 || col_ind[i] >= *len_v))
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i != 0 && (col_ind[i] < 0 || col_ind[i] >= *len_v || col_ind[i] <= col_ind[i - 1]))
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		check = scanf("%d", &(elems[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		if (elems[i] == 0)
		{
			printf("ERROR , ZERO ELEMENT INPUT\n");
			free(col_ind);
			free(elems);
			return 1;
		}
		printf("\n");
		
	}
	f = fopen(filename, "w");
	fprintf(f, "%d\n", *len_v);
	int flag = 0;
	for (int i = 0; i < *len_v; i ++)
	{
		flag = 0;
		for (int j = 0; j < *non_zero_els; j ++)
		{
			if (i == col_ind[j])
			{
				flag = 1;
				fprintf(f, "%d ", elems[j]);
				break;
			}
		}
		if (!flag)
		{
			fprintf(f, "0 ");
		}
	}
	free(elems);
	free(col_ind);
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
	printf("INPUT ROWS AND COLS OF MATRIX:\n");
	check = scanf("%d", rows);
	if (check != 1)
	{
		return 1;
	}
	check = scanf("%d", cols);
	if (check != 1)
	{
		return 1;
	}
	if (*rows <= 0 || *cols <= 0)
	{
		return 1;
	}
	f = fopen(filename, "w");
	fprintf(f, "%d\n", *rows);
	fprintf(f, "%d\n", *cols);
	printf("INPUT MATRIX %d x %d:\n", *rows, *cols);
	for (int i = 0; i < *rows;  i++)
	{
		flag_non_zero = 0;
		for (int j = 0; j < *cols; j ++)
		{
			check = scanf("%d", &scanner);
			if (check != 1)
			{
				return 1;
			}
			fprintf(f, "%d ", scanner);
			if (scanner)
			{
				(*non_zero_els) ++;
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
	return 0;
}
int generate_usual_matr(usual_matr_t *matrix)
{
	int check;
	int scanner;
	int a_ind = 0;
	int ia_ind = 0;
	int flag_non_zero = 0;
	int non_zero_els;
	int *elems;
	int *row_ind;
	int *col_ind;
	FILE *f;	
	printf("INPUT ROWS AND COLS OF MATRIX:\n");
	check = scanf("%d", &(matrix->rows));
	if (check != 1)
	{
		return 1;
	}
	check = scanf("%d", &(matrix->cols));
	if (check != 1)
	{
		return 1;
	}
	if (matrix->rows <= 0 || matrix->cols <= 0 || matrix->rows > MATRSIZE || matrix->cols > MATRSIZE)
	{
		return 1;
	}
	printf("INPUT AMOUNT OF NON-ZERO ELEMENTS:\n");
	check = scanf("%d", &non_zero_els);
	if (check != 1)
	{
		return 1;
	}
	if (non_zero_els <= 0 || non_zero_els > matrix->rows * matrix->cols)
	{
		printf("ERROR: INCORRECT INPUT\n");
		return 1;
	}
	elems = malloc(sizeof(int) * non_zero_els);
	if (elems == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	row_ind = malloc(sizeof(int) * non_zero_els);
	if (elems == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	col_ind = malloc(sizeof(int) * non_zero_els);
	if (elems == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	printf("format of matrix input: row = i, col = j, elem = 1\n");
	for (int i = 0; i < non_zero_els;  i++)
	{
		check = scanf("%d", &(row_ind[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT#0\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i == 0 && (row_ind[i] < 0 || row_ind[i] >= matrix->rows))
		{
			printf("ERROR IN INPUT#5\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i != 0 && (row_ind[i] < 0 || row_ind[i] >= matrix->rows || row_ind[i] < row_ind[i - 1]))
		{
			printf("ERROR IN INPUT#6, %d %d\n", row_ind[i], row_ind[i - 1]);
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		check = scanf("%d", &(col_ind[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT#1\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i == 0 && (col_ind[i] < 0 || col_ind[i] >= matrix->cols))
		{
			printf("ERROR IN INPUT#2\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i != 0 && (col_ind[i] < 0 || col_ind[i] >= matrix->cols || (col_ind[i] <= col_ind[i - 1] && row_ind[i] == row_ind[i - 1])))
		{
			printf("ERROR IN INPUT#3\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		check = scanf("%d", &(elems[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT#11\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (elems[i] == 0)
		{
			printf("ERROR , ZERO ELEMENT INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		printf("\n");
		
	}
	int flag = 0;
	for (int i = 0; i < matrix->rows; i ++)
	{
		for(int j = 0; j < matrix->cols; j ++)
		{		
			flag = 0;
			for (int k = 0; k < non_zero_els; k ++)
			{
				if (i == row_ind[k] && j == col_ind[k])
				{
					flag = 1;
					matrix->matrix[i][j] = elems[k];
					break;
				}
			}
			if (!flag)
			{
				matrix->matrix[i][j] = 0;
			}
		}
	}
	free(elems);
	free(col_ind);
	free(row_ind);
	return 0;
}
int generate_matr(int *rows, int *cols, char filename[], int *non_zero_els)
{
	int check;
	int scanner;
	int a_ind = 0;
	int ia_ind = 0;
	int flag_non_zero = 0;
	int *elems;
	int *row_ind;
	int *col_ind;
	FILE *f;	
	printf("INPUT ROWS AND COLS OF MATRIX:\n");
	check = scanf("%d", rows);
	if (check != 1)
	{
		return 1;
	}
	check = scanf("%d", cols);
	if (check != 1)
	{
		return 1;
	}
	if (*rows <= 0 || *cols <= 0)
	{
		return 1;
	}
	printf("INPUT AMOUNT OF NON-ZERO ELEMENTS:\n");
	check = scanf("%d", non_zero_els);
	if (check != 1)
	{
		return 1;
	}
	if (*non_zero_els <= 0 || *non_zero_els > *rows * *cols)
	{
		printf("ERROR: INCORRECT INPUT\n");
		return 1;
	}
	f = fopen(filename, "w");
	fprintf(f, "%d\n", *rows);
	fprintf(f, "%d\n", *cols);
	elems = malloc(sizeof(int) * *non_zero_els);
	if (elems == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	row_ind = malloc(sizeof(int) * *non_zero_els);
	if (elems == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	col_ind = malloc(sizeof(int) * *non_zero_els);
	if (elems == NULL)
	{
		printf("ERROR IN MEMORY ALLOCATION\n");
		return 1;
	}
	printf("format of matrix input: row = i, col = j, elem = 1\n");
	for (int i = 0; i < *non_zero_els;  i++)
	{
		check = scanf("%d", &(row_ind[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i == 0 && (row_ind[i] < 0 || row_ind[i] >= *rows))
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i != 0 && (row_ind[i] < 0 || row_ind[i] >= *rows || row_ind[i] < row_ind[i - 1]))
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		check = scanf("%d", &(col_ind[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i == 0 && (col_ind[i] < 0 || col_ind[i] >= *cols))
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (i != 0 && (col_ind[i] < 0 || col_ind[i] >= *cols || (col_ind[i] <= col_ind[i - 1] && row_ind[i] == row_ind[i - 1])))
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		check = scanf("%d", &(elems[i]));
		if (check != 1)
		{
			printf("ERROR IN INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		if (elems[i] == 0)
		{
			printf("ERROR , ZERO ELEMENT INPUT\n");
			free(row_ind);
			free(col_ind);
			free(elems);
			return 1;
		}
		printf("\n");
		
	}
	int flag = 0;
	for (int i = 0; i < *rows; i ++)
	{
		for(int j = 0; j < *cols; j ++)
		{		
			flag = 0;
			for (int k = 0; k < *non_zero_els; k ++)
			{
				if (i == row_ind[k] && j == col_ind[k])
				{
					flag = 1;
					fprintf(f, "%d ", elems[k]);
					break;
				}
			}
			if (!flag)
			{
				fprintf(f, "0 ");
			}
		}
		fprintf(f, "\n");
	}
	free(elems);
	free(col_ind);
	free(row_ind);
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
	tmp_a = malloc(sizeof(int) * non_zero_els);
	if (tmp_a == NULL)
	{
		printf("ERROR IN MEMORY\n");
		return 1;
	}
	matrix->a = tmp_a;	
	tmp_ja = malloc(sizeof(int) * non_zero_els);
	if (!tmp_ja)
	{
		free(matrix->a);
		printf("ERROR IN MEMORY\n");
		return 1;
	}
	matrix->ja = tmp_ja;	
	tmp_ia = calloc(rows + 1, sizeof(int));
	if (!tmp_ia)
	{
		free(matrix->a);
		free(matrix->ja);
		printf("ERROR IN MEMORY\n");
		return 1;
	}
	matrix->ia = tmp_ia;
	f = fopen(filename, "r");
	//setbuf(f, NULL);
	check = fscanf(f, "%d", &rows);
	if (check != 1)
	{
		printf("1# ERROR IN SCAN\n");
		return 1;
	}
	
	check = fscanf(f, "%d", &cols);
	if (check != 1)
	{
		printf("2# ERROR IN SCAN\n");
		return 1;
	}
	if (rows <= 0 || cols <= 0)
	{
		printf("ERROR\n");
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
				printf("\n3# ERROR IN SCAN\n");
				return 1;
			}
			if (scanner != 0)
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
int input_usual_matr(usual_matr_t *matr_str)
{
	int check;
	int scanner;
	FILE *f;	
	printf("INPUT ROWS AND COLS OF MATRIX:\n");
	check = scanf("%d", &(matr_str->rows));
	if (check != 1)
	{
		return 1;
	}
	check = scanf("%d", &(matr_str->cols));
	if (check != 1)
	{
		return 1;
	}
	if (matr_str->rows <= 0 || matr_str->cols <= 0 || matr_str->rows > MATRSIZE || matr_str->cols > MATRSIZE)
	{
		printf("ERROR SIZE OF MATRIX IS BIGGER THAN %d\n", MATRSIZE);
		return 1;
	}
	printf("INPUT MATRIX %d x %d:\n", matr_str->rows, matr_str->cols);
	for (int i = 0; i < matr_str->rows;  i++)
	{
		for (int j = 0; j < matr_str->cols; j ++)
		{
			check = scanf("%d", &(matr_str->matrix[i][j]));
			if (check != 1)
			{
				return 1;
			}
		}
	}
	return 0;
}
int input_usual_vect(usual_matr_t *vect_str)
{
	int check;
	int scanner;
	FILE *f;	
	printf("INPUT LENGTH OF VECTOR:\n");
	check = scanf("%d", &(vect_str->cols));
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
			check = scanf("%d", &(vect_str->matrix[0][i]));
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

