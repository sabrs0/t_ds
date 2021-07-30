#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs_list.h"
void print_list(Stack_list **head, free_sp *arr)
{
    Stack_list *deleted;
	if (!*head)
	{
		printf("STACK IS EMPY\n");
		return;
	}
	while (*head)
	{
		deleted = *head;
		*head = (*head)->next;
		if (arr->ind == -1)
		{
			arr->arr[0] = (size_t)deleted;
			arr->ind = 1;
		}
		else
		{
			arr->arr[arr->ind] = (size_t)deleted;
			arr->ind ++;
		}
		printf("%zx - %c\n", (size_t)deleted, deleted->bracket);
		free(deleted);
	}
}
int push(Stack_list **head, char bracket, free_sp *arr)
{
	int flag = 0;
    Stack_list *tmp = malloc (sizeof(Stack_list));
    if (tmp == NULL)
    {
        printf("ERROR: STACK OVERFLOW\n");
        return ERROR;
    }
	if (*head && (*head)->ind == MAX_STACK_SIZE - 1)
	{
        printf("ERROR: STACK OVERFLOW\n");
		free(tmp);
        return ERROR;
	}
	if (!*head)
	{
		tmp->ind = 0;
	}
	else
	{
		tmp->ind = (*head)->ind + 1;
	}
    tmp->next = *head;
    tmp->bracket = bracket;
    *head = tmp;
	for (int i = 0; i < (arr)->ind; i ++)
	{
		if ((arr)->arr[i] == (size_t) *head)
		{
			flag = 1;
			for (int j = i; j < (arr)->ind - 1; j ++)
			{
				size_t swapper = arr->arr[j];
				arr->arr[j] = arr->arr[j + 1];
				arr->arr[j + 1] = swapper;
			}
		}
	}
	if (flag)
		arr->ind --;
    return OK;
}
char get_top(Stack_list **head)
{
	char tmp = (*head)->bracket;
	*head = (*head)->next;
    return tmp;
}
int delete_top(Stack_list **head, free_sp *arr)
{
    Stack_list *deleted;
    if (*head == NULL)
    {
        printf("ERROR: STACK IS EMPTY. NOTHING TO DELETE\n");
        return ERROR;
    }
    deleted = *head;
    *head = (*head)->next;
	if (arr->ind == -1)
	{
		arr->arr[0] = (size_t)deleted;
		arr->ind = 1;
	}
	else
	{
		arr->arr[arr->ind] = (size_t)deleted;
		arr->ind ++;
	}
    free(deleted);
    return OK;
}
void delete_stack(Stack_list **head, free_sp *arr)
{
    Stack_list *deleted;
	while (*head)
	{
		deleted = *head;
		*head = (*head)->next;
		if (arr->ind == -1)
		{
			arr->arr[0] = (size_t)deleted;
			arr->ind = 1;
		}
		else
		{
			arr->arr[arr->ind] = (size_t)deleted;
			arr->ind ++;
		}
		free(deleted);
	}
}
int process_list(Stack_list **head, char string[], free_sp *arr)
{
    char bracket_tmp;
	int fig_brl = 0;
	int fig_brr = 0;
	int sq_brl = 0;
	int sq_brr = 0;
	int us_brl = 0;
	int us_brr = 0;
	while (*head)
	{
		bracket_tmp = get_top(head);
        if ((bracket_tmp == '('))
        {
        	if (!us_brr)
			{
				return ERROR;
			}
			us_brr --;
        }
		if (bracket_tmp == '[')
		{
        	if (!sq_brr)
			{
				return ERROR;
			}
			sq_brr --;
		}
		if (bracket_tmp == '{')
		{
        	if (!fig_brr)
			{
				return ERROR;
			}
			fig_brr --;
		}
        if ((bracket_tmp == ')'))
        {
			us_brr ++;
        }
		if (bracket_tmp == ']')
		{

			sq_brr ++;
		}
		if (bracket_tmp == '}')
		{
			fig_brr ++;
		}
	}
	if (fig_brr || us_brr || sq_brr)
	{
		printf("ERROR: Incorrect brackets\n");
		return ERROR;
	}
    if (*head != NULL)
    {
        printf("ERROR: Incorrect brackets\n");
        return ERROR;
    }
    return OK;
}
int create_free_sp_arr(free_sp **array)
{
	*array = (free_sp*)malloc(sizeof(free_sp));
	if (!*array)
	{
		printf("Error in memory allocation");
		return ERROR;	
	}
	(*array)->ind = -1;
	return OK;
}
void print_free_sp(free_sp *arr)
{
	if (arr == NULL)
	{
		printf("Free Space array is empty\n");
		return;
	}
	printf("amount of free_spaced elements = %d\n", arr->ind);
	if (arr->arr == NULL)
	{
		printf("Free Space array is empty\n");
		return;
	}
	else if (arr->ind < 1)
	{
		printf("Free Space array is empty\n");
		return;	
	}
	else
	{
		for (int i = 0; i < arr->ind; i ++)
		{
			printf("%zx\n", (size_t)arr->arr[i]);		
		}
	}
}
