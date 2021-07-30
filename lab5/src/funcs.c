#include <stdio.h>
#include "../inc/funcs.h"
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <math.h>
int create_fmem_arr(free_sp **fmem, int len)
{
	*fmem = malloc(sizeof(free_sp));
	if (!*fmem)
	{
		printf("Error in alloc fmem\n");
		return ERROR;
	}
	(*fmem)->arr = malloc(sizeof(size_t) * len);
	if (!(*fmem)->arr)
	{
		free(*fmem);
		*fmem = NULL;
		printf("Error in alloc fmem array\n");
		return ERROR;
	}
	(*fmem)->len = len;
	(*fmem)->ind = 0;
}
void destroy_fmem_arr(free_sp **fmem)
{
	if (fmem && *fmem)
	{
		if 	((*fmem)->arr)
		{
			free((*fmem)->arr);
			(*fmem)->arr = NULL;
		}
		free(*fmem);
		*fmem = NULL;
	}
}
int create_qarr(q_arr_t **queue, int leng)
{
	*queue = malloc(sizeof(q_arr_t));
	if(!*queue)
	{
		printf("Error in alloc queue array\n");
		return ERROR;
	}
	if (leng == 0)
	{
		printf("ERROR: trying to create empty queue\n");
		return ERROR;
	}
	(*queue)->arr = malloc(sizeof(elem_t) * leng);
	if (!(*queue)->arr)
	{
		free(*queue);
		*queue = NULL;
		printf("Error in alloc queue array\n");
		return ERROR;
	}
	(*queue)->len = leng;
	(*queue)->head = 0;
	(*queue)->tail = leng - 1;
	(*queue)->size = 0;
	return OK;
}
int is_full_qarr(q_arr_t *queue)
{
	return queue->size == queue->len;
}
int is_empty_qarr(q_arr_t *queue)
{
	return queue->size == 0;
}
int add_qarr(q_arr_t *queue, elem_t el)
{
	if (is_full_qarr(queue))
	{
		//printf("queue is full\n");
		return ERROR;
	}
	queue->tail = (queue->tail + 1) % queue->len;
	queue->arr[queue->tail] = el;
	queue->size ++;
	return OK;
}
int rm_qarr(q_arr_t *queue)
{
	if (is_empty_qarr(queue))
	{
		printf("queue is empty\n");
		return ERROR;
	}
	queue->head = (queue->head + 1) % queue->len;
	queue->size --;
	return OK;
}



int create_qlist(q_list_t **queue, int leng)
{
	*queue = malloc(sizeof(q_list_t));
	if(!*queue)
	{
		printf("Error in alloc queue list\n");
		return ERROR;
	}
	(*queue)->head = NULL;
	(*queue)->tail = NULL;
	(*queue)->len = leng;
	(*queue)->size = 0;
	
}
int is_full_qlist(q_list_t *queue)
{
	return queue->size == queue->len;
}
int is_empty_qlist(q_list_t *queue)
{
	return queue->tail == NULL;
}
int add_qlist(q_list_t *queue, elem_t el, free_sp *fmem, int *flag)
{
	*flag = 0;
	if (is_full_qlist(queue))
	{
		return ERROR;
	}
	q_node_t *tmp = malloc(sizeof(q_node_t));
	if (!tmp)
	{
		printf("Error in alloc queue node for list\n");
		return ERROR;
	}
	tmp->node_el.time = el.time;
	tmp->node_el.ind = el.ind;
	tmp->next = NULL;
	if (queue->tail == NULL)
	{
		queue->head = tmp;
		queue->tail = tmp;
		queue->size ++;
	}
	else
	{
		queue->tail->next = tmp;
		queue->tail = tmp;
		queue->size ++;
	}
	for (int i = 0; i < fmem->ind; i ++)
	{
		if (fmem->arr[i] == (size_t)tmp)
		{
			for (int j = i; j < fmem->ind - 1; j ++)
			{
				fmem->arr[j] = fmem->arr[j + 1];
			}
			fmem->ind --;
			*flag = 1;
			break;
		}
	}
	return OK;
}
int rm_qlist(q_list_t *queue, free_sp *fmem)
{
	if (is_empty_qlist(queue) || !queue->head)
	{
		printf("queue is empty\n");
		return ERROR;
	}
	q_node_t *tmp = queue->head;
	if (queue->head == queue->tail)
	{
		queue->head = NULL;
		queue->tail = NULL;
	}
	else
	{
		queue->head = queue->head->next;
	}
	queue->size --;
	fmem->arr[fmem->ind] = (size_t)tmp;
	fmem->ind ++;
	free(tmp);
	return OK;
}
void destroy_qarr(q_arr_t **queue)
{
	if (*queue)
	{
		free((*queue)->arr);
		(*queue)->arr = NULL;
	}
	free((*queue));
	(*queue) = NULL;
}
void destroy_qlist(q_list_t **queue, free_sp *fmem)
{
	if (queue && *queue)
	{
		while(!is_empty_qlist(*queue))
		{
			rm_qlist(*queue, fmem);
		}
		free(*queue);
		*queue = NULL;
	}
}
double get_time(double llim, double rlim)
{
	//srand(time(NULL));
	double rnd = (double) rand() / RAND_MAX;
	//printf("%lf\n", (rlim - llim) * rnd + llim);
	return (rlim - llim) * rnd + llim;
}
int array_process(double l_in_time, double r_in_time, double l_out_time, double r_out_time, q_arr_t *queue, int cycles)
{
	srand(time(NULL));
	int in_amount = 0;
	int out_amount = 0;
	int failed_amount = 0;
	double hold_time = 0.0; // время простоя аппарата
	double serv_time = 0.0; // время обслуживания 

	double time_in = get_time(l_in_time, r_in_time);
	double time_oa = -1; // время оа
	int check;
	elem_t z_fast;
	elem_t z_usual;
	int total_size = 0;
	int calls = 0;
	double avg_time = 0.0;
	while (out_amount != 1000)
	{
		if (time_oa < 0 || time_in < time_oa)
		{
			if (time_oa < 0)
				hold_time += time_in;
			serv_time += time_in;

			time_oa -= time_in;

			time_in =  get_time(l_in_time, r_in_time);

			z_fast.time = get_time(l_out_time, r_out_time);
			z_fast.ind = 0;

			check = add_qarr(queue, z_fast);	
			if (check == ERROR)
			{
				//printf("Queue is full\n");
				failed_amount ++;
			}
			else
				in_amount ++;

			if (time_oa < 0 && queue->size)
			{
				z_usual = queue->arr[queue->head];
				rm_qarr(queue);
				time_oa = z_usual.time;
			}
		}
		else
		{
			calls ++;
			time_in -= time_oa;
			serv_time += time_oa;
			
			z_usual.ind ++;
			time_oa = 0;
			if (z_usual.ind < cycles)
			{
				z_usual.time = get_time(l_out_time, r_out_time);
				check = add_qarr(queue, z_usual);
				if (check == ERROR)
				{
					printf("Queue is full\n");
					failed_amount ++;
				}
			}
			else
			{
				out_amount++;
				total_size += queue->size;
				if (out_amount % 100 == 0)
				{
					printf("Out tasks amount == %d\n", out_amount);
					printf("Queue size == %d\n", queue->size);
					printf("Average queue size %d\n", total_size / out_amount);	
				}	
			}
			if (is_empty_qarr(queue))
			{
				time_oa = -1;
				
			}
			else
			{
				z_usual = queue->arr[queue->head];
				time_oa = z_usual.time;
				rm_qarr(queue);
				
			}
	
			
		}
		
	}
	double theor_time;
	if (((l_in_time + r_in_time) / 2 * 1000) > ((l_out_time + r_out_time)/ 2 * 1000 * cycles))
	{
		theor_time = (l_in_time + r_in_time) / 2 * 1000;
	}
	else
	{
		theor_time = calls * (r_out_time + l_out_time)/ 2;
	}
	double diff_prcnt = fabs(theor_time - serv_time) / theor_time * 100;
	printf("\n\n\nModeling overall time = %lf, expected time = %lf, difference = %lf %%\n", serv_time, theor_time, diff_prcnt);
	printf("Income tasks = %d\n", in_amount);
	printf("Outcome tasks = %d\n", out_amount);
	printf("automatic calls = %d\n", calls);
	//printf("Service automat time: theoretic = %lf and practic = %lf\n", (l_out_time + r_out_time)/ 2 * 1000 * cycles, calls * (l_out_time + r_out_time)/ 2);
	printf("Hold time = %lf\n", hold_time);
	printf("Failed not used tasks = %d\n", failed_amount);
	return OK;
}

int list_process(double l_in_time, double r_in_time, double l_out_time, double r_out_time, q_list_t *queue, int cycles, free_sp *fmem)
{
	srand(time(NULL));
	int in_amount = 0;
	int out_amount = 0;
	int failed_amount = 0;
	double hold_time = 0.0; // время простоя аппарата
	double serv_time = 0.0; // время обслуживания 

	double time_in = get_time(l_in_time, r_in_time);
	double time_oa = -1; // время оа
	int check;
	elem_t z_fast;
	elem_t z_usual;
	int total_size = 0;
	int calls = 0;
	double avg_time = 0.0;
	int flag;
	int new_mem = 0, used_mem = 0;
	while (out_amount != 1000)
	{
		if (time_oa < 0 || time_in < time_oa)
		{
			if (time_oa < 0)
				hold_time += time_in;
			serv_time += time_in;

			z_fast.time = get_time(l_out_time, r_out_time);
			z_fast.ind = 0;
			check = add_qlist(queue, z_fast, fmem, &flag);	
			if (check == ERROR)
			{
				//printf("Queue is full\n");
				failed_amount ++;
			}
			else
			{
				if (flag)
				{
					used_mem ++;
				}
				else
				{
					new_mem ++;
				}
			}
			in_amount ++;
			time_oa -= time_in;

			time_in =  get_time(l_in_time, r_in_time);

			if (time_oa < 0 && queue->size)
			{
				
				z_usual = queue->head->node_el;
				rm_qlist(queue, fmem);
				time_oa = z_usual.time;
			}
		}
		else
		{
			calls ++;
			time_in -= time_oa;
			serv_time += time_oa;
			
			z_usual.ind ++;
			time_oa = 0;
			if (z_usual.ind < cycles)
			{
				z_usual.time = get_time(l_out_time, r_out_time);
				check = add_qlist(queue, z_usual, fmem, &flag);
				if (check == ERROR)
				{
					//printf("Queue is full\n");
					failed_amount ++;
				}
				else
				{
					if (flag)
					{
						used_mem ++;
					}
					else
					{
						new_mem ++;
					}
				}
			}
			else
			{
				out_amount++;
				total_size += queue->size;
				if (out_amount % 100 == 0)
				{
					printf("Out tasks amount == %d\n", out_amount);
					printf("Queue size == %d\n", queue->size);
					printf("Average queue size %d\n", total_size / out_amount);	
				}	
			}
			if (is_empty_qlist(queue))
			{
				time_oa = -1;
				
			}
			else
			{
				z_usual = queue->head->node_el;
				time_oa = z_usual.time;
				rm_qlist(queue, fmem);
				
			}
	
			
		}
		
	}
	double theor_time;
	if (((l_in_time + r_in_time) / 2 * 1000) > ((l_out_time + r_out_time)/ 2 * 1000 * cycles))
	{
		theor_time = (l_in_time + r_in_time) / 2 * 1000;
	}
	else
	{
		theor_time = calls * (r_out_time + l_out_time)/ 2;
	}
	double diff_prcnt = fabs(theor_time - serv_time) / theor_time * 100;
	printf("\n\n\nModeling overall time = %lf, expected time = %lf, difference = %lf %%\n", serv_time, theor_time, diff_prcnt);
	printf("Income tasks = %d\n", in_amount);
	printf("Outcome tasks = %d\n", out_amount);
	printf("automatic calls = %d\n", calls);
	//printf("Service automat time: theoretic = %lf and practic = %lf\n", (l_out_time + r_out_time)/ 2 * 1000 * cycles, calls * (l_out_time + r_out_time)/ 2);
	printf("Hold time = %lf\n", hold_time);
	printf("Failed not used tasks = %d\n", failed_amount);
	printf("Reused memory amount = %d\n", used_mem);
	printf("New memory amount = %d\n", new_mem);
	return OK;	
}


