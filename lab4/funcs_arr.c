#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"
void print_arr(Stack_arr *head)
{
	if (head->len == 0)
		printf("STACK IS EMPTY\n");
	while (head->len != 0)
	{
		printf("%p - %c\n", head->array + head->len - 1, head->array[ head->len - 1]);
		head->len -- ;
	}
}
int push_arr(Stack_arr *head, char bracket)
{
    if (head->len == MAX_STACK_SIZE)
    {
        printf("ERROR: STACK OVERFLOW\n");
        return ERROR;
    }
	head->array[head->len] = bracket;
	head->len ++;
    return OK;
}
char get_top_arr(Stack_arr *head)
{
	char tmp = head->array[head->len];
	head->len --;
    return tmp;
}
int delete_top_arr(Stack_arr *head)
{
    if (head->len == 0)
    {
        printf("ERROR: STACK IS EMPTY. NOTHING TO DELETE\n");
        return ERROR;
    }
    //printf("deleted: %p - %c\n", head->array + head->len - 1, head->array[ head->len - 1]);
	head->len --;
    return OK;
}
int delete_arr_st(Stack_arr *head)
{
    if (head->len == 0)
    {
        printf("ERROR: STACK IS EMPTY. NOTHING TO DELETE\n");
        return ERROR;
    }
	while (head->len)
	{
		//printf("deleted: %p - %c\n", head->array + head->len - 1, head->array[ head->len - 1]);
		head->len --;
	}
    return OK;	
}
int process_arr(Stack_arr *head, char string[])
{
    char bracket_tmp;
    /*for (int i = 0; i < strlen(string); i ++)
    {
        if ((string[i] == '(') || (string[i] == '[') || (string[i] == '{'))
        {
            if (push_arr(head, string[i]))
            {
                return ERROR;
            }
        }
        else if ((string[i] == ')') || (string[i] == ']') || (string[i] == '}'))
        {
            if (head->len == 0)
            {
                printf("ERROR: Incorrect brackets\n");
                return ERROR;
            }
            bracket_tmp = get_top_arr(head);
            if ((string[i] == ')') && (bracket_tmp == '('))
            {
                if (delete_top_arr(head))
                {
                    return ERROR;
                }
            }
            else if ((string[i] == ']') && (bracket_tmp == '['))
            {
                if (delete_top_arr(head))
                {
                    return ERROR;
                }

            }
            else if ((string[i] == '}') && (bracket_tmp == '{'))
            {
                if (delete_top_arr(head))
                {
                    return ERROR;
                }

            }
            else
            {
                printf("ERROR: Incorrect brackets\n");
                return ERROR;
            }
        }*/
	int fig_brl = 0;
	int fig_brr = 0;
	int sq_brl = 0;
	int sq_brr = 0;
	int us_brl = 0;
	int us_brr = 0;
	while (head->len)
	{
		bracket_tmp = get_top_arr(head);
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
    if (head->len != 0)
    {
        printf("ERROR: Incorrect brackets\n");
        return ERROR;
    }
    return OK;
}
