#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	int matrix[512][512];	
	int vector[512];
	int m[3] = {10, 100, 500};
	char file_name[20] = "";
	char file_name2[20] = "";
	int percent[7] = {5, 10, 20, 50, 60, 80, 100};
	int ind_i, ind_j, ind_vect;
	int f_n = 0;
	FILE *f;
	FILE *f2;
	for (int i = 0; i < 7; i ++)
	{
		for (int j = 0; j < 3; j ++)
		{
			
			file_name[0] =  (f_n + 65);
			file_name[1] = '.';
			file_name[2] = 't';
			file_name[3] = 'x';
			file_name[4] = 't';
			file_name[5] = '\0';

			file_name2[0] =  (f_n + 65);
			file_name2[1] = 'V';			
			file_name2[2] = '.';
			file_name2[3] = 't';
			file_name2[4] = 'x';
			file_name2[5] = 't';
			file_name2[6] = '\0';
			f_n ++;
			f = fopen(file_name, "w");
			f2 = fopen(file_name2, "w");
			fprintf(f,"PERCENTAGE = %d:\n", percent[i]);
			fprintf(f2,"PERCENTAGE = %d:\n", percent[i]);
			fprintf(f, "%d %d\n", m[j], m[j]);
			fprintf(f2, "%d\n", m[j]);
			for (int k = 0; k < m[j]; k ++)
			{
				vector[k] = 0;
				for (int q = 0; q < m[j]; q ++)
				{
					matrix[k][q] = 0;
				}
			}
			for (int x = 0; x < ((m[j] * m[j]) / 100 * percent[i]); x ++)
			{	
				while (1)
				{
					ind_i = rand() % m[j];
					ind_j = rand() % m[j];
					if (matrix[ind_i][ind_j] == 0)
					{
						matrix[ind_i][ind_j] = fabs(rand() % 100) + 1;
						break;
					}
				}
			}
			for (int x = 0; x < (m[j] / 100 * percent[i] + 1); x ++)
			{	if (percent[i] == 100)
				{
					vector[x] = fabs(rand() % 100) + 1;
				}
				else
				{
					
					while (1)
					{
						ind_vect = rand() % m[j];
						if (vector[ind_vect] == 0)
						{
							vector[ind_vect] = fabs(rand() % 100) + 1;	
							break;
						}
					}
				}
			}
			printf("PERCENTAGE = %d:\n", percent[i]);
			for (int k = 0; k < m[j]; k ++)
			{
				for (int q = 0; q < m[j]; q ++)
				{
					fprintf(f, "%d ", matrix[k][q]);
				}
				fprintf(f, "\n");
			}
			for (int q = 0; q < m[j]; q ++)
			{
				fprintf(f2, "%d ", vector[q]);
			}
			fprintf(f2, "\n");
			fclose(f);
			fclose(f2);
		}
		
	}	
}
