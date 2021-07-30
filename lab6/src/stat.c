#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../inc/tree_funcs.h"
#include "../inc/hash_funcs.h"
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
void free_file(char **arr, int len)
{
	for (int i = 0; i < len; i ++)
	{
		free(arr[i]);
	}
	free(arr);
}
int count_file_len(char filename[])
{
	int len = 0;
	char str[256];
	FILE *f = fopen(filename, "r");
	if (!f)
	{	
		printf("ERROR in open file\n");
		return len;
	}
	while (fscanf(f, "%s", str) != EOF)
	{
		len ++;
	}
	fclose(f);
	return len;
}
int fill_arr(char ***arr, int len, char filename[])
{
	char str[256];
	FILE *f = fopen(filename, "r");
	if (!f)
	{
		printf("ERROR in open file\n");
		fclose(f);
		return ERROR;
	}
	*arr = calloc(len, sizeof(char *));
	if (!*arr)
	{
		printf("Cant alloc memory\n");
		fclose(f);
		return ERROR;
	}
	for (int i = 0; i < len; i ++)
	{
		fscanf(f, "%s", str);
		*(*arr + i) = malloc(sizeof(char) * 256);
		if (!(*(*arr + i)))
		{
			free_file(*arr, len);
			printf("Cant alloc memory\n");
			fclose(f);
			return ERROR;
		}
		memmove((*(*arr + i)), str, strlen(str) + 1);
	}
	fclose(f);
	return OK;
}
void delete_in_file(char word[], char **file, int len, int *if_c)
{
	int flag = 0;
	for (int i = 0; i < len; i ++)
	{
		(*if_c)++;
		if (!strcmp(word, file[i]))
		{
			flag = 1;
			for (int j = i; j < len - 1; j ++)
			{
				memmove((file[j]), (file[j + 1]), strlen((file[j + 1])) + 1); 
			}
			free((file[len - 1]));
			len = len - 1;
			break;
		}
	}
	if (!flag)
	{
		printf("Cannot find string in file\n");
	}
}
int print_file(char **arr, int len)
{
	for (int i = 0; i < len; i ++)
		printf("%s\n", arr[i]);
}
size_t hash_size(hash_table_t *table)
{
	size_t size = 0;
	hash_node_t *tmp;
	for (int i = 0; i < table->len; i ++)
	{
		tmp = table->elems[i];
		if (tmp)
		{
			while(tmp)
			{
				size =  size + (sizeof(hash_node_t) - 256 + strlen(tmp->string));
				tmp = tmp->next;
			}
		}
		else
		{
			size += (sizeof(hash_node_t)- 256);
		}
	}
	return size;
}
int main()
{
	int if_bin = 0;
	int if_bal = 0;
	int if_hash = 0;
	int if_file = 0;
	char **data = NULL;

	uint64_t bin_time = 0;
	uint64_t bal_time = 0;
	uint64_t hash_time = 0;
	uint64_t file_time = 0;

	uint64_t del_start_us;
	uint64_t del_stop_us;
	uint64_t del_start_bal;
	uint64_t del_stop_bal;
	uint64_t del_start_hash;
	uint64_t del_stop_hash;
	uint64_t del_start_file;
	uint64_t del_stop_file;

	tree_t *t_root = NULL;
	tree_t *balance_root = NULL;
	tree_t *node_to_find = NULL;
	char **file = NULL;
	int file_len = 0;
	hash_table_t *table = NULL;
	char filename[256] = "big_data.txt";
	char str_to_find[256];
	char c;
	size_t h_size = 0;
	int check;
	int coll_max;
	int tab_len;
	int flag_safe = 0;
	int flag_choice_1 = 0;
	int choice;
	file_len = count_file_len(filename);
	if (!file_len)
	{
		destruct_tree(t_root);
		destruct_tree(balance_root);
		destruct_tab(table);
		free_file(file, file_len);
		return ERROR;
	}
	check = fill_arr(&data, file_len, filename);
	if (check == ERROR)
	{
		destruct_tree(t_root);
		destruct_tree(balance_root);
		destruct_tab(table);
		free_file(file, file_len);
		return ERROR;
	}
	printf("filelen = %d\n", file_len);
	for (int i = 0; i < file_len; i ++)
	{
			//setbuf(stdout, NULL);
			printf("%d.\n", i);
			strcpy(str_to_find, data[i]);
			check = build_tree(&t_root, filename);
			if (check)
			{
				printf("ERROR WHILE BUILD TREE\n");
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				return ERROR;
			}
			check = build_balanced_tree(&balance_root, filename);
			if (check)
			{
				printf("ERROR WHILE BUILD TREE\n");
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				return ERROR;
			}
			flag_safe = 0;
			tab_len = 300;
			coll_max = 3;			
			check = hash_t_input(&table, filename, &flag_safe, tab_len, coll_max);
			if (check)
			{
				printf("ERROR WHILE BUILD HASH TABLE\n");
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				return ERROR;
			}
			//file_len = count_file_len(filename);
			if (!filename)
			{
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				return ERROR;
			}
			check = fill_arr(&file, file_len, filename);
			if (check == ERROR)
			{
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				return ERROR;
			}
			del_start_us = tick();
			delete_tree(&t_root, tree_search(t_root, str_to_find, &if_bin), &if_bin);	
			del_stop_us = tick();


			t_root = find_root(t_root);
			del_start_bal = tick();
			rec_delete(&balance_root, balance_root, str_to_find, &if_bal);
			del_stop_bal = tick();
			balance_root = find_root(balance_root);



			int (*hash)( char *word, int length);
			if (flag_safe)
				hash = &hash_safe;
			else
			{
				hash = &hash_usual;
			}
			del_start_hash = tick();
			if (delete_h(table, str_to_find, hash, &if_hash))
				printf("Error in delete\n");
			del_stop_hash = tick();



			del_start_file = tick();
			delete_in_file(str_to_find, file, file_len, &if_file);
			del_stop_file = tick();

			bin_time += (del_stop_us - del_start_us);
			bal_time += (del_stop_bal - del_start_bal);
			hash_time += (del_stop_hash - del_start_hash);
			file_time += (del_stop_file - del_start_file);
			if (i == file_len - 1)
			{
				printf("Table size = %ld\n", hash_size(table));
			}

			destruct_tree(t_root);

			destruct_tree(balance_root);

			destruct_tab(table);

			free_file(file, file_len - 1);
			t_root = NULL;
			balance_root = NULL;
			table = NULL;
			file = NULL;
	}
	printf("SREDNEE for bin : %ju\n", bin_time / file_len);
	printf("SREDNEE for bal : %ju\n", bal_time / file_len);
	printf("SREDNEE for hash : %ju\n", hash_time / file_len);
	printf("SREDNEE for file : %ju\n", file_time / file_len);
	

	
	printf("IFS for bin : %lf\n", (double)if_bin / file_len);
	printf("IFS for bal : %lf\n", (double)if_bal / file_len);
	printf("IFS for hash : %lf\n", (double)if_hash / file_len);
	printf("IFS for file : %lf\n", (double)if_file / file_len);
		
}
