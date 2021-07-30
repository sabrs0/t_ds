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


