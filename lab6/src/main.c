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
		return ERROR;
	}
	*arr = calloc(len, sizeof(char *));
	if (!*arr)
	{
		printf("Cant alloc memory\n");
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
			return ERROR;
		}
		strcpy((*(*arr + i)), str);
	}
	fclose(f);
	return OK;
}
void delete_in_file(char word[], char **file, int *len, int *if_c)
{
	int flag = 0;
	for (int i = 0; i < *len; i ++)
	{
		(*if_c)++;
		if (!strcmp(word, file[i]))
		{
			flag = 1;
			for (int j = i; j < *len - 1; j ++)
			{
				strcpy(file[j], file[j + 1]); 
			}
			free(file[*len - 1]);
			*len = *len - 1;
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

int main()
{
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
	int tab_len;
	hash_table_t *table = NULL;
	char filename[256] = "data.txt";
	char str_to_find[256];
	char c;
	int check;
	int coll_max;
	int flag_safe = 0;
	int flag_choice_1 = 0;
	int choice;
	while (1)
	{
		printf("1 - Fill structures by data from file\n");
		printf("2 - Print Binary tree\n");
		printf("3 - Print AVL tree\n");
		printf("4 - Print Hash table\n");
		printf("5 - Print file\n");
		printf("6 - Make delete\n");
		printf("0 - Exit\n");

		check = scanf("%d", &choice);
		if (check != 1)
		{
			printf("ERROR in choice input\n");
			destruct_tree(t_root);
			destruct_tree(balance_root);
			destruct_tab(table);
			free_file(file, file_len);
			return ERROR;
		}
		if (choice < 0 || choice > 6)
		{
			printf("ERROR in choice input\n");
			destruct_tree(t_root);
			destruct_tree(balance_root);
			destruct_tab(table);
			free_file(file, file_len);
			return ERROR;
		}
		if (flag_choice_1 == 1)
			printf("Structures already initialised\n");
		if (choice == 1 && flag_choice_1 != 1)
		{
			flag_choice_1 = 1;
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
			tab_len = 0;
			coll_max = 0;
			check = hash_t_input_data(&tab_len, &coll_max);
			if (check)
			{
				printf("ERROR WHILE BUILD HASH TABLE\n");
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				return ERROR;
			}			
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
			file_len = count_file_len(filename);
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
		}
		else if (choice == 2)
		{	
			printf("Binary search tree(usual):\n");
			print_tree(t_root, 0);
		}
		else if (choice == 3)
		{	
			printf("Binary search tree(balanced):\n");
			print_tree(balance_root, 0);
		}
		else if (choice == 4)
		{	
			printf("Hash Table:\n");
			print_table(table, coll_max);
		}
		else if (choice == 5)
		{	
			printf("File:\n");
			print_file(file, file_len);
		}
		else if (choice == 6)
		{	
			printf("Input string for delete:\n");
			scanf("%s", str_to_find);



			del_start_us = tick();
			int if_us = 0;
			delete_tree(&t_root, tree_search(t_root, str_to_find, &if_us), &if_us);	
			del_stop_us = tick();



			t_root = find_root(t_root);
			del_start_bal = tick();
			int if_bal = 0;
			rec_delete(&balance_root, balance_root, str_to_find, &if_bal);
			del_stop_bal = tick();
			balance_root = find_root(balance_root);



			int (*hash)( char *word, int length);
			int if_hash = 0;
			if (flag_safe)
				hash = &hash_safe;
			else
			{
				hash = &hash_usual;
			}
			del_start_hash = tick();
			delete_h(table, str_to_find, hash, &if_hash);
			del_stop_hash = tick();


			int if_file = 0;
			del_start_file = tick();
			delete_in_file(str_to_find, file, &file_len, &if_file);
			del_stop_file = tick();


			printf("time for usual tree = %ju, comprasions = %d\n", del_stop_us - del_start_us, if_us);
			printf("time for balanced tree = %ju, comprasions = %d\n", del_stop_bal - del_start_bal, if_bal);
			printf("time for hash tab = %ju, comprasions = %d\n", del_stop_hash - del_start_hash, if_hash);
			printf("time for file = %ju, comprasions = %d\n", del_stop_file - del_start_file, if_file);
		}
		else if (choice == 0)
		{
			destruct_tree(t_root);
			destruct_tree(balance_root);
			destruct_tab(table);
			free_file(file, file_len);
			break;
			return OK;
		}
		else
		{
			if (flag_choice_1 != 1)
			{
				printf("ERROR in choice input\n");
				destruct_tree(t_root);
				destruct_tree(balance_root);
				destruct_tab(table);
				free_file(file, file_len);
				break;
				return ERROR;
			}
		}
	}
	return OK;
}
