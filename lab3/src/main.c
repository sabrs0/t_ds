#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"
#include "matr_io.h"
#include "matr_gener.h"
#include "multiply.h"
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

	int check, choice, input_choice, size_choice, percent_choice, matr_size, matr_percent, vect_size, vect_percent;	

	char filename[256] = "in_matr.txt";
	char filename2[256] = "in_vector.txt";
	while (1)
	{

		printf("1 - multiply sparse vector on sparse matrix\n");
		printf("2 - multiply usual vector on usual matrix\n");
		printf("0 - EXIT\n");
		check = scanf("%d", &choice);
		if (check != 1)
		{
			printf("ERROR WHILE INPUT CHOICE\n");
			return 1;
		}
		if (choice == 1)
		{
			printf("CHOOSE FORMAT OF INPUT:\n");
			printf("1 - COORDINATE INPUT\n");
			printf("2 - USUAL INPUT\n");
			printf("3 - GENERATE MATRIX\n");
			check = scanf("%d", &input_choice);
			if (check != 1)
			{
				printf("ERROR: INCORRECT INPUT OF CHOICE\n");
				return 1;
			}
			if (input_choice == 1)
			{
				check = generate_vector(&len_v, filename2, &non_zero_els3);
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


				check = generate_matr(&rows, &cols, filename, &non_zero_els);
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
			}
			else if (input_choice == 2)
			{
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
			}
			else if (input_choice == 3)
			{
				printf("\tCHOOSE SIZE OF VECTOR:\n");
				printf("\t\t1 - 50\n");
				printf("\t\t2 - 100\n");	
				printf("\t\t3 - 500\n");
				check = scanf("%d", &size_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (size_choice < 1 || size_choice > 3)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (size_choice == 1)
				{
					vect_size = 50;
				}
				else if (size_choice == 2)
				{
					vect_size = 100;
				}
				else if (size_choice == 3)
				{
					vect_size = 500;
				}
				printf("\tCHOOSE PERCENTAGE OF VECTOR:\n");
				printf("\t\t1 - 5 %%\n");
				printf("\t\t2 - 10 %%\n");	
				printf("\t\t3 - 20 %%\n");
				printf("\t\t4 - 30 %%\n");
				printf("\t\t5 - 50 %%\n");
				printf("\t\t6 - 60 %%\n");
				printf("\t\t7 - 80 %%\n");
				printf("\t\t8 - 100 %%\n");
				check = scanf("%d", &percent_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (percent_choice < 1 || percent_choice > 8)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (percent_choice == 1)
				{
					vect_percent = 5;
				}
				else if (percent_choice == 2)
				{
					vect_percent = 10;
				}
				else if (percent_choice == 3)
				{
					vect_percent = 20;
				}
				else if (percent_choice == 4)
				{
					vect_percent = 30;
				}
				
				else if (percent_choice == 5)
				{
					vect_percent = 50;
				}
				
				else if (percent_choice == 6)
				{
					vect_percent = 60;
				}
				
				else if (percent_choice == 7)
				{
					vect_percent = 80;
				}
				
				else if (percent_choice == 8)
				{
					vect_percent = 100;
				}
				check = input_gener_vect(vect_size, vect_percent, filename2, &non_zero_els3, &len_v);
				if (check != 0)				
				{
					printf("ERROR\n");
					return 1;
				}
				check = init_vector(len_v, &vector, filename2, non_zero_els3);
				if (check != 0)				
				{
					printf("ERROR\n");
					return 1;
				}
				print_razr_vect(vector);



				printf("\tCHOOSE SIZE OF MATRIX:\n");
				printf("\t\t1 - 50X50\n");
				printf("\t\t2 - 100X100\n");	
				printf("\t\t3 - 500X500\n");
				check = scanf("%d", &size_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (size_choice < 1 || size_choice > 3)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (size_choice == 1)
				{
					matr_size = 50;
				}
				else if (size_choice == 2)
				{
					matr_size = 100;
				}
				else if (size_choice == 3)
				{
					matr_size = 500;
				}
				printf("\tCHOOSE PERCENTAGE OF MATRIX:\n");
				printf("\t\t1 - 5 %%\n");
				printf("\t\t2 - 10 %%\n");	
				printf("\t\t3 - 20 %%\n");
				printf("\t\t4 - 30 %%\n");
				printf("\t\t5 - 50 %%\n");
				printf("\t\t6 - 60 %%\n");
				printf("\t\t7 - 80 %%\n");
				printf("\t\t8 - 100 %%\n");
				check = scanf("%d", &percent_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (percent_choice < 1 || percent_choice > 8)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 8)\n");
					return 1;
				}
				if (percent_choice == 1)
				{
					matr_percent = 5;
				}
				else if (percent_choice == 2)
				{
					matr_percent = 10;
				}
				else if (percent_choice == 3)
				{
					matr_percent = 20;
				}
				else if (percent_choice == 4)
				{
					matr_percent = 30;
				}
				
				else if (percent_choice == 5)
				{
					matr_percent = 50;
				}
				
				else if (percent_choice == 6)
				{
					matr_percent = 60;
				}
				
				else if (percent_choice == 7)
				{
					matr_percent = 80;
				}
				
				else if (percent_choice == 8)
				{
					matr_percent = 100;
				}
				check = input_gener_matr(matr_size, matr_percent, filename, &non_zero_els, &rows, &cols);
				if (check != 0)				
				{
					printf("ERROR\n");
					return 1;
				}
				check = init_matr(rows, cols, &matrix, filename, non_zero_els);
				if (check != 0)
				{
					printf("ERROR IN INITIALIZE SPARSE MATRIX\n");
					return 1;
				}
						
			}

			else
			{
				printf("INCORRECT INPUT OF CHOICE");
				return 1;
			}
			print_razr_matr(matrix);
			start = clock();
			check = mult_razr(vector, matrix, &vector_res, len_v, rows);
			if (check)
			{
				printf("ERROR IN SPARSE MULTIPLICATION\n");
				return 1;
			}
			stop = clock();
			res_time = (double)(stop - start)/ CLOCKS_PER_SEC;
			printf("RESULT(SPARSE):\n");
			print_razr_vect(vector_res);
			printf("TIME FOR THIS OPERATION: %lf (s)\n",  res_time);
		}
		else if (choice == 2)
		{
			printf("CHOOSE FORMAT OF INPUT:\n");
			printf("\t1 - COORDINATE INPUT\n");
			printf("\t2 - USUAL INPUT\n");
			printf("\t3 - GENERATE MATRIX\n");
			check = scanf("%d", &input_choice);
			if (check != 1)
			{
				printf("ERROR: INCORRECT INPUT OF CHOICE\n");
				return 1;
			}
			if (input_choice == 1)
			{
				check = generate_usual_vector(&vector1);;
				if (check)
				{
					printf("ERROR IN INPUT USUAL VECTOR\n");
					return 1;
				}
				print_usual_matr(vector1);


				check = generate_usual_matr(&matrix1);
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
				printf("TIME FOR USUAL OPERATION: %lf (s)\n",  res_time);				
			}
			else if (input_choice == 2)
			{
				check = input_usual_vect(&vector1);;
				if (check)
				{
					printf("ERROR IN INPUT USUAL VECTOR\n");
					return 1;
				}
				print_usual_matr(vector1);


				check = input_usual_matr(&matrix1);
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
				printf("TIME FOR USUAL OPERATION: %lf (s)\n",  res_time);
			}
			else if (input_choice == 3)
			{
				printf("\tCHOOSE SIZE OF VECTOR:\n");
				printf("\t\t1 - 50\n");
				printf("\t\t2 - 100\n");	
				printf("\t\t3 - 500\n");
				check = scanf("%d", &size_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (size_choice < 1 || size_choice > 3)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (size_choice == 1)
				{
					vect_size = 50;
				}
				else if (size_choice == 2)
				{
					vect_size = 100;
				}
				else if (size_choice == 3)
				{
					vect_size = 500;
				}
				printf("\tCHOOSE PERCENTAGE OF VECTOR:\n");
				printf("\t\t1 - 5 %%\n");
				printf("\t\t2 - 10 %%\n");	
				printf("\t\t3 - 20 %%\n");
				printf("\t\t4 - 30 %%\n");
				printf("\t\t5 - 50 %%\n");
				printf("\t\t6 - 60 %%\n");
				printf("\t\t7 - 80 %%\n");
				printf("\t\t8 - 100 %%\n");
				check = scanf("%d", &percent_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (percent_choice < 1 || percent_choice > 8)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (percent_choice == 1)
				{
					vect_percent = 5;
				}
				else if (percent_choice == 2)
				{
					vect_percent = 10;
				}
				else if (percent_choice == 3)
				{
					vect_percent = 20;
				}
				else if (percent_choice == 4)
				{
					vect_percent = 30;
				}
				
				else if (percent_choice == 5)
				{
					vect_percent = 50;
				}
				
				else if (percent_choice == 6)
				{
					vect_percent = 60;
				}
				
				else if (percent_choice == 7)
				{
					vect_percent = 80;
				}
				
				else if (percent_choice == 8)
				{
					vect_percent = 100;
				}
				check = input_gener_usual_vect(vect_size, vect_percent, &vector1);
				if (check != 0)				
				{
					printf("ERROR\n");
					return 1;
				}
				print_usual_matr(vector1);



				printf("\tCHOOSE SIZE OF MATRIX:\n");
				printf("\t\t1 - 50X50\n");
				printf("\t\t2 - 100X100\n");	
				printf("\t\t3 - 500X500\n");
				check = scanf("%d", &size_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (size_choice < 1 || size_choice > 3)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (size_choice == 1)
				{
					matr_size = 50;
				}
				else if (size_choice == 2)
				{
					matr_size = 100;
				}
				else if (size_choice == 3)
				{
					matr_size = 500;
				}
				printf("\tCHOOSE PERCENTAGE OF MATRIX:\n");
				printf("\t\t1 - 5 %%\n");
				printf("\t\t2 - 10 %%\n");	
				printf("\t\t3 - 20 %%\n");
				printf("\t\t4 - 30 %%\n");
				printf("\t\t5 - 50 %%\n");
				printf("\t\t6 - 60 %%\n");
				printf("\t\t7 - 80 %%\n");
				printf("\t\t8 - 100 %%\n");
				check = scanf("%d", &percent_choice);
				if (check != 1)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
					return 1;
				}
				if (percent_choice < 1 || percent_choice > 8)
				{
					printf("ERROR : INCORRECT INPUT OF CHOICE(1 - 3)\n");
					return 1;
				}
				if (percent_choice == 1)
				{
					matr_percent = 5;
				}
				else if (percent_choice == 2)
				{
					matr_percent = 10;
				}
				else if (percent_choice == 3)
				{
					matr_percent = 20;
				}
				else if (percent_choice == 4)
				{
					matr_percent = 30;
				}
				
				else if (percent_choice == 5)
				{
					matr_percent = 50;
				}
				
				else if (percent_choice == 6)
				{
					matr_percent = 60;
				}
				
				else if (percent_choice == 7)
				{
					matr_percent = 80;
				}
				
				else if (percent_choice == 8)
				{
					matr_percent = 100;
				}
				check = input_gener_usual_matrix(matr_size, matr_percent, &matrix1);
				if (check != 0)				
				{
					printf("ERROR: INCORRECT INPUT OF CHOICE\n");
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
				printf("TIME FOR USUAL OPERATION: %lf (s)\n",  res_time);							
			}
			else
			{
				printf("ERROR: INCORRECT CHOICE INPUT\n");
			}
		}
		else if (choice == 0)
		{
			printf("EXIT\n");
			return 0;
		}
        else
        {
            printf("ERROR IN INPUT CHOICE\n");
            return 1;
        }
	}
	return 0;
}
