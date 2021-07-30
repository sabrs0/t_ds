#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcs.h"
#include "funcs_list.h"
#include <stdint.h>
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
}int check_input(char *string, int *br_flag)
{
	char x;
	scanf("%c",&x); 
    for (int i = 0; ; i ++)
    {
		if (scanf("%c", &x) != 1)
		{	
			return ERROR;
		}
		string[i] = x;
		if (string[i] == '\n')
		{
			string[i] = '\0';
			break;
		}
        /*if (((string[i] < 'a') || (string[i] > 'z')) && ((string[i] < 'A') || (string[i] > 'Z')) && ((string[i] < '0') || (string[i] > '9'))\
         && (string[i] != '+') && (string[i] > '-') && (string[i] != '*') && (string[i] != '/')&&\
         (string[i] != '[') && (string[i] != '(') && (string[i] != '{') && (string[i] != ']') && (string[i] != ')') && (string[i] != '}'))
        {
            return ERROR;
        }
        if ((string[i] == '[') || (string[i] == '(') || (string[i] == '{') || (string[i] == ']') || (string[i] == ')') || (string[i] == '}'))
        {
            *br_flag = 1;
        }*/
    }
    /*if (strlen(string) == 0 || string[0] == '\0' && strlen(string)!= 0)
    {
		printf("/");
        return ERROR;
    }*/
    return OK;
}
int main()
{
    int br_flag = 0;
    char *string = malloc(sizeof(char) * MAX_STACK_SIZE);
	if (string == NULL)
	{
		return ERROR;
	}
	char stroka[MAX_STACK_SIZE + 1];
    size_t str_len = 0;
    Stack_list *head = NULL;
	Stack_arr head_arr;
	head_arr.len = 0;
	char elem;
    int choice;
	//clock_t start, stop;
	uint64_t start, stop;
	double res;
	free_sp *free_arr = NULL;
    while(1)
    {
		printf("Choose struct:\n");
		printf("1 - array\n");
		printf("2 - list\n");
		printf("3 - Exit\n");
        if (scanf("%d", &choice) != 1)
		{
			printf("ERROR IN CHOICE\n");
			return ERROR;
		}
		if (choice < 0 || choice > 3)
		{
			printf("ERROR INCORRECT CHOICE\n");
			return ERROR;
		}
		if (choice == 1)
		{
			while(1)
			{
				printf("1 - solve problem\n");
				printf("2 - add elements\n");
				printf("3 - delete element\n");
				printf("4 - show stack\n");
				printf("5 - delete stack\n");
				printf("0 - exit\n");
				if (scanf("%d", &choice) != 1)
				{
					printf("ERROR IN CHOICE\n");
					return ERROR;
				}
				if (choice < 0 || choice > 5)
				{
					printf("ERROR INCORRECT CHOICE\n");
					return ERROR;
				}
				if (choice == 1)
				{
					br_flag = 0;
					//head_arr.len = 0;
					if (check_input(string, &br_flag))
					{
						printf("ERROR in check string\n");
						return ERROR;
					}
					if (br_flag == 0)
					{
						printf("NO BRACKETS");
						return ERROR;
					}
					//start = clock();
					start = tick();
					process_arr(&head_arr, string);
					stop = tick();
					printf("time for array = %ju\n", stop - start);
					/*stop = clock();
					res = (double)(stop - start) / CLOCKS_PER_SEC;
					printf("time for array = %lf\n", res);*/
				}		
				if (choice == 2)
				{
					elem = ' ';
					int str_size = 0;
					scanf("%c", &elem);
					while (1)
					{
						if (str_size > MAX_STACK_SIZE)
						{
							printf("ERROR OVERFLOW\n");
							return ERROR;
						}
						scanf("%c", &elem);
						/*if (scanf("%c", &elem) != 1)
						{
							printf("Incorrect scanning\n");
							return ERROR;
						}*/
						if (elem == '\n')
						{
							break;
						}
						stroka[str_size] = elem;
						str_size ++;
					}
					start = tick();
					for (int i = 0; i < str_size; i ++)
					{
						if (stroka[i] == '(' || stroka[i] == ')' || stroka[i] == '[' || stroka[i] == ']' || stroka[i] == '{' || stroka[i] == '}')
						{
							if (push_arr(&head_arr, stroka[i]))
							{
								break;
							}
						}
					}
					stop = tick();
					printf("time for array = %ju\n", stop - start);
					/*stop = clock();
					res = (double)(stop - start) / CLOCKS_PER_SEC;*/
				}
				if (choice == 3)
				{
					start = tick();
					delete_top_arr(&head_arr);
					stop = tick();
					printf("time for array = %ju\n", stop - start);
				}
				if (choice == 4)
				{
					printf("Stack as array:\n");
					print_arr(&head_arr);
				}
				if (choice == 5)
				{
					start = tick();
					delete_arr_st(&head_arr);
					stop = tick();
					printf("time for array = %ju\n", stop - start);
				}
				if (choice == 0)
				{
					break;
				}

			}
		}
		else if (choice == 2)
		{
			while(1)
			{
				printf("1 - solve problem\n");
				printf("2 - add elements\n");
				printf("3 - delete element\n");
				printf("4 - show stack\n");
				printf("5 - show free space\n");
				printf("6 - delete stack\n");
				printf("0 - exit\n");
				if (scanf("%d", &choice) != 1)
				{
					printf("ERROR IN CHOICE\n");
					return ERROR;
				}
				if (choice < 0 || choice > 6)
				{
					printf("ERROR INCORRECT CHOICE\n");
					return ERROR;
				}
				if (choice == 1)
				{
					br_flag = 0;
					/*delete_stack(&head, free_arr);
					head = NULL;*/
					if (check_input(string, &br_flag))
					{
						printf("ERROR in check string\n");
						return ERROR;
					}
					if (!free_arr)
						create_free_sp_arr(&free_arr);
					start = tick();
					if (process_list(&head, string, free_arr))
						printf( "Incorrect brackets\n");
					stop = tick();
					printf("time for list = %ju\n", stop - start);
				}
				if (choice == 2)
				{
					elem = ' ';
					int str_size2 = 0;
					scanf("%c", &elem);
					while (1)
					{
						if (str_size2 >= MAX_STACK_SIZE)
						{
							printf("ERROR OVERFLOW\n");
							return ERROR;
						}
						if (scanf("%c", &elem) != 1)
						{
							printf("Incorrect scanning\n");
							return ERROR;
						}
						if (elem == '\n')
						{
							break;
						}
						stroka[str_size2] = elem;
						str_size2 ++;
					}
					if(!free_arr)
					{
						create_free_sp_arr(&free_arr);
						free_arr->ind = -1;
					}
					start = tick();
					for (int i = 0; i < str_size2; i ++)
					{
						if (stroka[i] == '(' || stroka[i] == ')' || stroka[i] == '[' || stroka[i] == ']' || stroka[i] == '{' || stroka[i] == '}')
						{						
							if (push(&head, stroka[i], free_arr))
							{
								break;
							}
						}
					}
					stop = tick();
					printf("time for list = %ju\n", stop - start);
				}
				if (choice == 3)
				{
					if(!free_arr)
					{
						create_free_sp_arr(&free_arr);
						free_arr->ind = -1;
					}
					start = tick();
					delete_top(&head, free_arr);
					stop = tick();
					printf("time for list = %ju\n", stop - start);
				}
				if (choice == 4)
				{
					printf("Stack as list:\n");
					print_list(&head, free_arr);
				}
				if (choice == 5)
				{
					print_free_sp(free_arr);
				}
				if (choice == 6)
				{
					start = tick();
					delete_stack(&head, free_arr);
					stop = tick();
					printf("time for list = %ju\n", stop - start);
				}
				if (choice == 0)
				{
					delete_stack(&head, free_arr);
					head = NULL;
					break;
				}
			}
		}
		else if (choice == 3)
		{
			break;
		}
	}
    return OK;
}
