#include <stdio.h>
#include "../inc/funcs.h"
#include <stdlib.h>
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
}
int main()
{
    int choice = -1;
    int str_choice = -1;
    int check;
	int cycles;
	uint64_t start, stop;
	q_list_t *q_list = NULL;
	int q_arr_size, q_list_size;
	double l_in_time, r_in_time, l_out_time, r_out_time;
	q_arr_t *q_arr = NULL;
	free_sp *fmem = NULL;
	printf("Programm executes a model of service automat with queue.\n");
    while (1)
    {
        printf("Choose structure:\n");
        printf("1 - Array\n");
        printf("2 - List\n");
		printf("0 - Exit\n");
        check = scanf("%d", &str_choice);
        if (check != 1)
        {
			printf("Error in input of choice\n");
            return ERROR;
        }
        if (str_choice != 1 && str_choice != 2 && str_choice != 0)
        {
				printf("Error in choice value\n");
                return ERROR;
        }
        if (str_choice == 1)
        {
            printf("Choose action:\n");
            printf("1 - Input data and show statistics\n");
            printf("2 - Show operation's process statistics\n");
			printf("0 - Exit\n");
            check = scanf("%d", &choice);
            if (check != 1)
            {
				printf("Error in input of choice\n");
                return ERROR;
            }
            if (choice != 1 && choice != 2 && choice != 0)
            {
				printf("Error in choice value\n");
                return ERROR;
            }
            if (choice == 1)
            {
				if (q_arr)
				{
					destroy_fmem_arr(&fmem);
					destroy_qarr(&q_arr);
					destroy_qlist(&q_list, fmem);
					printf("Error. Queue of this type already exists. Exit\n");
					return ERROR;
				}
				printf("Input amount of elements in queue:\n");
				check = scanf("%d", &q_arr_size);
				if (check != 1)
				{
					printf("Error in input of queue size\n");
					return 1;
				}
				if (q_arr_size < 0 || q_arr_size > 10000)
				{
					printf("Error in input of queue size\n");
					return ERROR;
				}
				check = create_qarr(&q_arr, q_arr_size);
				if (check == ERROR)
				{
					printf("Error in creation of queue as array\n");
					return ERROR;
				}
				/*l_in_time = 0.0;
				r_in_time = 6.0;
				l_out_time = 0.0;
				r_out_time = 1.0;
				cycles = 5;*/
				printf("Input limits of queue insertion time(2 numbers from 0 to 99999):\n");
				check = scanf("%lf", &l_in_time);
				if (check != 1)
				{
					printf("Error in input of first limit number\n");
					return ERROR;
				}
				check = scanf("%lf", &r_in_time);
				if (check != 1)
				{
					printf("Error in input of second limit number\n");
					return ERROR;
				}
				if (r_in_time <= l_in_time)
				{
					printf("Error: left limit should be less than right limit\n");
					return ERROR;
				}
				if (r_in_time < 0 || l_in_time < 0 || r_in_time > 99999 || l_in_time > 99999)
				{
					printf("Error in limit value\n");
					return ERROR;
				}



				printf("Input limits of Service Automatic time(2 numbers from 0 to 99999):\n");
				check = scanf("%lf", &l_out_time);
				if (check != 1)
				{
					printf("Error in input of first limit number\n");
					return ERROR;
				}
				check = scanf("%lf", &r_out_time);
				if (check != 1)
				{
					printf("Error in input of second limit number\n");
					return ERROR;
				}
				if (r_out_time < l_out_time)
				{
					printf("Error: left limit should be less than right limit\n");
					return ERROR;
				}
				if (r_out_time < 0 || l_out_time < 0 || r_out_time > 99999 || l_out_time > 99999)
				{
					printf("Error in limit value\n");
					return ERROR;
				}
				printf("Input cycles amount:\n");
				check = scanf("%d", &cycles);
				if (check != 1)
				{
					printf("Error in input of second limit number\n");
					return ERROR;
				}
				if (cycles < 0 || cycles > 99999)
				{
					printf("Error in cycles value\n");
					return ERROR;
				}
				start = tick();
				array_process(l_in_time, r_in_time, l_out_time, r_out_time, q_arr, cycles);
				stop = tick();
				printf("\n\n Time for this modeling = %ju\n", stop - start);
				
            }
            else if (choice == 2)
            {
         		q_arr_t *queue = NULL;
				elem_t elem;
				check  = create_qarr(&queue, 1000);
				if (check == ERROR)
				{
					printf("Error in creation of queue as array\n");
					return ERROR;
				}
				start =  tick();
				for (int i = 0; i < 1000; i ++)
				{
					elem.ind = i;
					elem.time = 0;
					add_qarr(queue, elem);
				}
				stop = tick();
				printf("Time for add element in array queue = %ju\n", (stop - start) / 1000);

				start =  tick();
				for (int i = 0; i < 1000; i ++)
				{
					rm_qarr(queue);
				}
				stop = tick();
				printf("Time for delete element in array queue = %ju\n", (stop - start) / 1000);
            }
        }
        else if (str_choice == 2)
        {
            printf("Choose action:\n");
            printf("1 - Input data and show statistics\n");
            printf("2 - Show operation's process statistics\n");
			printf("0 - Exit\n");
            check = scanf("%d", &choice);
            if (check != 1)
            {
				printf("Error in input of choice\n");
                return ERROR;
            }
            if (choice != 1 && choice != 2)
            {
				printf("Error in value of choice\n");
                return ERROR;
            }
            if (choice == 1)
            {
				if (q_list)
				{
					destroy_qarr(&q_arr);
					destroy_qlist(&q_list, fmem);
					destroy_fmem_arr(&fmem);
					printf("queue already exists. Exit");
					return ERROR;
				}
				printf("Input queue size:\n");
				check = scanf("%d", &q_list_size);
				if (check != 1)
				{
					printf("Error in input of queue size\n");
					return 1;
				}
				if (q_list_size < 0 || q_list_size > 10000)
				{
					printf("Incorrect value of queue size\n");
					return ERROR;
				}
				check = create_qlist(&q_list, q_list_size);
				if (check == ERROR)
				{
					printf("Error in creation of queue as list\n");
					return ERROR;
				}
				check = create_fmem_arr(&fmem, q_list_size);
				/*l_in_time = 0.0;
				r_in_time = 6.0;
				l_out_time = 0.0;
				r_out_time = 1.0;
				cycles = 5;*/
				printf("Input limits of queue insertion time(2 numbers from 0 to 99999):\n");
				check = scanf("%lf", &l_in_time);
				if (check != 1)
				{
					printf("Error in input of first limit number\n");
					return ERROR;
				}
				check = scanf("%lf", &r_in_time);
				if (check != 1)
				{
					printf("Error in input of second limit number\n");
					return ERROR;
				}
				if (r_in_time <= l_in_time)
				{
					printf("Error: left limit should be less than right limit\n");
					return ERROR;
				}
				if (r_in_time < 0 || l_in_time < 0 || r_in_time > 99999 || l_in_time > 99999)
				{
					printf("Error in limit value\n");
					return ERROR;
				}



				printf("Input limits of Service Automatic time(2 numbers from 0 to 99999):\n");
				check = scanf("%lf", &l_out_time);
				if (check != 1)
				{
					printf("Error in input of first limit number\n");
					return ERROR;
				}
				check = scanf("%lf", &r_out_time);
				if (check != 1)
				{
					printf("Error in input of second limit number\n");
					return ERROR;
				}
				if (r_out_time <= l_out_time)
				{
					printf("Error: left limit should be less than right limit\n");
					return ERROR;
				}
				if (r_out_time < 0 || l_out_time < 0 || r_out_time > 99999 || l_out_time > 99999)
				{
					printf("Error in limit value\n");
					return ERROR;
				}
				printf("Input cycles amount:\n");
				check = scanf("%d", &cycles);
				if (check != 1)
				{
					printf("Error in input of second limit number\n");
					return ERROR;
				}
				if (cycles < 0 || cycles > 99999)
				{
					printf("Error in cycles value\n");
					return ERROR;
				}

				start = tick();
				list_process(l_in_time, r_in_time, l_out_time, r_out_time, q_list, cycles, fmem);
				stop = tick();
				printf("\n\n Time for this modeling = %ju\n", stop - start);
            }
            else if (choice == 2)
            {
         		q_list_t *queue = NULL;
				free_sp *fmem_test = NULL;
				elem_t elem;
				check  = create_qlist(&queue, 1000);
				if (check == ERROR)
				{
					printf("Error in creation of queue as list\n");
					return ERROR;
				}
				check  = create_fmem_arr(&fmem_test, 1000);
				if (check == ERROR)
				{
					printf("Error in creation of memory array\n");
					return ERROR;
				}
				int flag;
				start =  tick();
				for (int i = 0; i < 1000; i ++)
				{
					elem.ind = i;
					elem.time = 0;
					add_qlist(queue, elem, fmem_test, &flag);
				}
				stop = tick();
				printf("Time for add element in array queue = %ju\n", (stop - start) / 1000);

				start =  tick();
				for (int i = 0; i < 1000; i ++)
				{
					rm_qlist(queue, fmem_test);
				}
				stop = tick();
				printf("Time for delete element in array queue = %ju\n", (stop - start) / 1000);
				destroy_fmem_arr(&fmem_test);
            }

        }
		else
		{
			break;
		}
    }
	destroy_fmem_arr(&fmem);
	destroy_qarr(&q_arr);
	destroy_qlist(&q_list, fmem);
	return OK;
}
