#define ALLOC_ERROR 2
#define PUSH_ERROR 3
#define RESTRUCT_ERROR 5
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/structs.h"
int find_prost_fig(int current)
{
	int pr_fig = current;
	int dels = 0;
	pr_fig += 1;
	while(1)
	{
		dels = 0;
		for (int i = 1; i <= (pr_fig / 2 + 1); i ++)
		{
			if (((pr_fig % i) == 0) && pr_fig != i)
			{
				dels ++;
			}
		}
		if (dels == 1)
		{
			return pr_fig;
		}
		pr_fig ++;
	}
}
void destruct_tab(hash_table_t *table)
{
	hash_node_t *tmp;
	if (table)
	{
		for (int i = 0; i < table->len; i ++)
		{
			while(table->elems[i])
			{
				tmp = table->elems[i]->next;
				free(table->elems[i]);
				table->elems[i] = tmp;
			}	
		}
		free(table->elems);
		table->elems = NULL;
		free(table);
		table = NULL;
	}
}
int hash_safe(char *word, int n)
{
	unsigned long hash = 5381;
	int c;
	while(c = *word++)
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash % n;
}
int hash_usual(char *word, int n)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i ++)
    {
        sum += word[i];
    }
    return sum % n;
}
hash_node_t *create_h_node(char word[])
{
	hash_node_t *tmp = malloc(sizeof(hash_node_t));
	if (!tmp)
	{
		printf("Cannot allocate memory\n");
	}
	tmp->next = NULL;
	memmove(tmp->string, word, strlen(word) + 1);
	return tmp;
}
int push_h(hash_table_t *table, char *word, int coll_max, int (*hash)( char *word, int length))
{
	int index;
	hash_node_t *node;
	if (table == NULL)
	{
		printf("Table is empy\n");
		return ERROR;
	}
	index = hash(word, table->len);
	node = table->elems[index];
	hash_node_t *inserted = create_h_node(word);
	if (inserted == NULL)
	{
		return ALLOC_ERROR;
	}
	if (!node)
	{
		table->elems[index] = inserted;
		return OK;
	}
	if (strcmp(node->string, inserted->string) == 0)
	{
		printf("Same string\n");
		return OK;
	}
	for (int i = 0; i < coll_max; i ++)
	{
		if (node->next == NULL)
		{
			node->next = inserted;
			return OK;
		}
		if (strcmp(node->string, inserted->string) == 0)
		{
			printf("Same string\n");
			return OK;
		}
		node = node->next;
	}
	return PUSH_ERROR;
}
int create_hash_table( hash_table_t **table, int len)
{
	*table = malloc(sizeof(hash_table_t));
	if (*table == NULL)
	{
		printf("Cannot allocate memory\n");
		return ERROR;
	}
	(*table)->elems = calloc(len, sizeof(hash_node_t));
	if ((*table)->elems == NULL)
	{
		printf("Cannot allocate memory\n");
		return ERROR;
	}
	(*table)->len = len;
	return OK;
}
int restruct_tab(hash_table_t **table, int new_len, int (*hash)( char *word, int length), int coll_max)
{
	hash_table_t *table_tmp;
	if (create_hash_table(&table_tmp, new_len) == ERROR)
	{
		return ALLOC_ERROR;
	}
	hash_node_t *tmp;
	for (int i = 0; i < (*table)->len; i ++)
	{
		tmp = (*table)->elems[i];
		while(tmp)
		{
			if (push_h(table_tmp, tmp->string, coll_max, hash))
			{
				destruct_tab(table_tmp);
				return RESTRUCT_ERROR;
			}
			tmp = tmp->next;	
		}
	}
	destruct_tab(*table);
	*table = table_tmp;
	return OK;
}
int delete_h(hash_table_t *table, char word[], int (*hash)( char *word, int length), int *if_c)
{
	int index;
	if (table == NULL)
	{
		return ERROR;
	}
	index = hash(word, table->len);
	hash_node_t *tmp = table->elems[index];
	if (!tmp)
	{
		printf("cannot find node\n");
		return ERROR;
	}
	(*if_c)++;
	if (strcmp(tmp->string, word) == 0)
	{
		tmp = table->elems[index]->next;
		free(table->elems[index]);
		table->elems[index] = tmp;
		return OK;
	}
	hash_node_t *tmp_copy = NULL;
	while (tmp->next)
	{
		(*if_c)++;
		if (strcmp(tmp->next->string, word) == 0)
		{
			tmp_copy = tmp->next;
			tmp->next = tmp_copy->next;
			free(tmp_copy);
			tmp_copy = NULL;
			return OK;
			
		}
		tmp = tmp->next;
	}
	return ERROR;
}
int search_h(hash_table_t *table, char word[], int (*hash)( char *word, int length))
{
	int index = hash(word, table->len);	
	hash_node_t *tmp = table->elems[index];
	while(tmp)
	{
		if (strcmp(tmp->string, word) == 0)
		{
			return OK;
		}
		tmp = tmp->next;
	}		
	return ERROR;
}
int hash_t_input_data(int *tab_len, int *coll_max)
{
//int tab_len;
	printf("Input table size:\n");
	if (scanf("%d", tab_len) != 1)
	{
		printf("Incorrect input of the size\n");
		return ERROR;
	}
	if (*tab_len < 1)
	{
		printf("Incorrect input of the size\n");
		return ERROR;
	}
	printf("Input collision amount:\n");
	if (scanf("%d", coll_max) != 1)
	{
		printf("Incorrect input of collision amount\n");
		return ERROR;
	}
	if (*coll_max < 0)
	{
		printf("Incorrect input of collision amount\n");
		return ERROR;
	}
	return OK;
}
int hash_t_input(hash_table_t **table, char filename[], int *flag_safe, int tab_len, int coll_max)
{
	/*int tab_len;
	printf("Input table size:\n");
	if (scanf("%d", &tab_len) != 1)
	{
		printf("Incorrect input of the size\n");
		return ERROR;
	}
	if (tab_len < 1)
	{
		printf("Incorrect input of the size\n");
		return ERROR;
	}
	printf("Input collision amount:\n");
	if (scanf("%d", coll_max) != 1)
	{
		printf("Incorrect input of collision amount\n");
		return ERROR;
	}
	if (*coll_max < 0)
	{
		printf("Incorrect input of collision amount\n");
		return ERROR;
	}*/
	if (create_hash_table(table, tab_len))
	{
		return ERROR;
	}
	char str[256];
	FILE *f = fopen(filename, "r");
	if(!f)
	{
		printf("cannot open file\n");
		return ERROR;
	}
	int new_len = tab_len;
	int (*hash)( char *word, int length);
	hash = &hash_usual;
	int check;
	int check2;
	while(fscanf(f, "%s", str) != -1)
	{ 
		check2 = push_h(*table, str, coll_max, hash);
		if (check2 == ALLOC_ERROR)
		{
			return ALLOC_ERROR;
		}
		while (check2 == PUSH_ERROR)
		{
			hash = &hash_safe;
			*flag_safe = 1;
			if (new_len > 1000000)
			{
				printf("Too much collisions, cant build the table\n");
				return ERROR;
			}
			new_len = find_prost_fig(new_len);
			check = restruct_tab(table, new_len, hash, coll_max);
			if (check == ALLOC_ERROR)
				return ALLOC_ERROR;
			while(check)
			{
				new_len = find_prost_fig(new_len);
				check = restruct_tab(table, new_len, hash, coll_max);
				if (check == ALLOC_ERROR)
				{	
					return ALLOC_ERROR;
				}
			}
			check2 = push_h(*table, str, coll_max, hash);
			if (check2 == ALLOC_ERROR)
			{
				return ALLOC_ERROR;
			}
		}
	}
	fclose(f);
	return OK;
}
void print_table(hash_table_t *table, int coll_max)
{
	int c = ' ';
	int c2 = '-';
	int count = 0;
	hash_node_t *tmp;
	printf("|------|---------------|\n");
	printf("|   №  |    WORDS      |\n");
	printf("|------|---------------|\n");
	for (int i = 0; i < table->len; i ++)
	{
		printf("|%6d|", i);
		tmp = table->elems[i];
		if (!tmp)
		{
			for (int i = 0; i < coll_max + 1; i ++)
			{
				printf("%15c|", c);
			}
			printf("\n");
		}
		else
		{

			count = 0;
			while (tmp)
			{
				printf("%15s|", tmp->string);
				tmp = tmp->next;
				count ++;
			}
			for (int i = 0; i < coll_max + 1 - count; i ++)
			{
				printf("%15c|", c);
			}
			printf("\n");
		}
	}
	printf("\n");
}

