#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/funcs.h"
/*void push(sm_node_t **head, int data)
{
	if (head)
	{
		sm_node_t *tmp = malloc(sizeof(sm_node_t));
		tmp->city = data;
		tmp->next = *head;
		*head = tmp;
	}
}
sm_node_t *create_node(int data)
{
    sm_node_t *tmp;
    tmp = malloc(sizeof(sm_node_t));
    if (!tmp)
    {
        return NULL;
    }
    tmp->next = NULL;
    tmp->city = data;
    return tmp;
}
sm_node_t *add_end(sm_node_t *head, sm_node_t *tmp)
{
    sm_node_t *cur;
    if (!head)
        return tmp;
    cur = head;
    for (; cur->next; cur = cur->next);
    cur->next = tmp;
    return head;
}
void pop_back(sm_node_t **head)
{
	sm_node_t *copy = *head;
	sm_node_t *tmp;
	if (head &&*head)
	{
		while (*head)
		{
			tmp = (*head)->next;
			if (tmp)
			{
				if (!tmp->next)
				{
					free(tmp);
					(*head)->next = NULL;
					*head = copy;
					break;
				}
			}
			*head = (*head)->next;
		}
	}
}
int get_back(sm_node_t *head)
{
	if (head)
	{
		while(head->next)
		{
			head = head->next;
		}
		return head->city;
	}
	else
	{
		return -1;
	}
}
int find_prev(sm_node_t *head)
{
	if (head && head->next)
	{
		while (head->next->next)
		{
			head = head->next;
		}
		return head->city;
	}
	else
	{
		return -1;
	}
}
void print_list(sm_node_t *head)
{
	while(head)
	{
		printf("%d\n", head->city);
		head = head->next;
	}
}
void push_back(sm_node_t **head, int data)
{
	sm_node_t *tmp = *head;
	if (*head)
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = malloc (sizeof(sm_node_t));
		tmp->next->city = data;
		tmp->next->next = NULL;
	}
	else
	{
		*head = malloc (sizeof(sm_node_t));
		(*head)->city = data;
		(*head)->next = NULL;
	}
}
void dfs(sm_matr_t *matrix, int index, int *visit, int a_city, int b_city, sm_node_t **head, int *flag_b, int *prev)
{
	visit[index] = 1;
	if (!*flag_b)
	{
		for (int i = 0; i < matrix->size; i ++)
		{
				if (matrix->matr[index][i] && !visit[i])
				{
					push_back(head, i);
					if (i == b_city)
					{
						*flag_b = 1;
					}
					dfs(matrix, i, visit, a_city, b_city, head, flag_b, prev);
					if (!*flag_b)
					{
						pop_back(head);
					}
					else
					{

						break;
					}
					
				}
		}
	}
}*/
void dfs_classic(sm_matr_t *matrix, int index, int *visit)
{
	visit[index] = 1;
	for (int i = 0; i < matrix->size; i ++)
	{
		if (matrix->matr[index][i] && !visit[i])
		{
			dfs_classic(matrix, i, visit);
		}
	}
}
int route_exists_classic(sm_matr_t *matrix, int a_city, int b_city)
{
	int *visited = calloc(matrix->size, sizeof(int));
	if (visited == NULL)
	{
		printf("Error in alloc\n");
		return -1;
	}
	dfs_classic(matrix, a_city, visited);
	return visited[b_city];
}
int input_data(char filename[], sm_matr_t **matrix/*, sm_list_t **list*/)
{	
	FILE *f;
	f = fopen(filename, "r");
	if (!f)
	{
		printf("Cannot open file\n");
		return 1;
	}
	int check;	
	int V_size;
	check = fscanf(f, "%d", &V_size);
	if (check == -1)
	{
		printf("empty file\n");
		fclose(f);
		return 1;
	}
	*matrix = malloc(sizeof(sm_matr_t));
	if (!*matrix)
	{
		printf("ERROR in matrix alloc\n");
		fclose(f);
		return 1;
	}
	/**list = calloc(1, sizeof(sm_list_t));
	if (!*list)
	{
		printf("ERROR in list alloc\n");
		fclose(f);
		return 1;
	}*/
	(*matrix)->matr = malloc(sizeof(int *) * V_size);
	if (!(*matrix)->matr)
	{
		printf("ERROR in matrix->matr alloc\n");
		fclose(f);
		return 1;
	}
	//(*list)->arr = malloc(sizeof(sm_node_t) * V_size);
	for (int i = 0; i < V_size; i ++)
	{
		((*matrix)->matr[i]) = calloc(V_size, sizeof (int));
		if (!(*matrix)->matr[i])
		{
			printf("ERROR in matrix->matr + i alloc\n");
			fclose(f);
			return 1;
		}
	}
	int v_1, v_2;
	//char space, sl_n;
	while(1)
	{
		check = fscanf(f, "%d", &v_1);
		if (check == -1)
		{
			break;
			/*printf("incorrect file \n");
			fclose(f);
			return 1;*/
		}
		check = fscanf(f, "%d", &v_2);
		if (check == -1)
		{
			printf("incorrect file\n");
			fclose(f);
			return 1;
		}
		if (v_1 == v_2 || v_1 < 0 || v_2 < 0 || v_2 >= V_size || v_1 >= V_size)
		{
			printf("Error,incorrect value of node\n");
			fclose(f);
			return 1;
		}
		(*matrix)->matr[v_1][v_2] = 1;
		(*matrix)->matr[v_2][v_1] = 1;
	}
	/*for (int i = 0; i < V_size; i ++)
	{
		sm_node_t *tmp = create_node(i);
		(*list)->arr[i] = add_end((*list)->arr[i], tmp);
		
		for (int j = 0; j < V_size; j ++)
		{
			if (*(*((*matrix)->matr + i) + j))
			{
				sm_node_t *tmp = create_node(j);
				(*list)->arr[i] = add_end((*list)->arr[i], tmp);
			}
		}
	}*/
	(*matrix)->size = V_size;
	//(*list)->size = V_size;
	fclose(f);
	return 0;
}
void output_matr(const sm_matr_t *matrix)
{
	for (int i = 0; i < matrix->size; i ++)
	{
		for (int j = 0; j < matrix->size; j ++)
		{
			printf("%d ", matrix->matr[i][j]);
		}
		printf("\n");
	}
}
/*void output_list(sm_list_t *list)
{
	for (int i = 0; i < list->size; i ++)
	{
		sm_node_t *tmp = list->arr[i];
		while(tmp)
		{
			printf("%d-->", tmp->city);
			tmp = tmp->next;
		}
		printf("NULL\n");
	}
}*/
void graph_viz(sm_matr_t *matrix)
{
	for (int i = 0; i < matrix->size; i ++)
	{
		for (int j = 0; j < matrix->size; j ++)
		{
			if (matrix->matr[i][j])
				matrix->matr[j][i] = 0;
		}
	}
	FILE *f = fopen("graph.gv", "w");
	fprintf(f, "graph G{\n");
	for (int i = 0; i < matrix->size; i ++)
	{
		for (int j = 0; j < matrix->size; j ++)
		{
			if (matrix->matr[i][j])
			{
				 fprintf(f, "\t%d -- %d;\n", i, j);
			}
		}
	}
	fprintf(f, "}\n");
	fclose(f);
	system("dot -Tpng graph.gv -o graph.png");
	system("xdg-open graph.png");
}
int input_a_b_cities(int *a, int *b)
{
	int check;
	check = scanf("%d", a);
	if (check != 1)
	{
		printf("Incorrect input of city\n");
		return -1;
	}
	check = scanf("%d", b);
	if (check != 1)
	{
		printf("Incorrect input of city\n");
		return -1;
	}
	if (*a == *b || *a < 0 || *b < 0)
	{
		printf("Incorrect input of city\n");
		return -1;
	}
	return 0;
}
/*int route_exists(sm_matr_t *matrix, int a_city, int b_city, sm_node_t **route)
{
	int *visited = calloc(matrix->size, sizeof(int));
	if (visited == NULL)
	{
		printf("Error in alloc\n");
		return -1;
	}
	int prev = -1, flag_b = 0;
	push_back(route, a_city);
	dfs(matrix, a_city, visited, a_city, b_city, route, &flag_b, &prev);
	return visited[b_city];
}
int count_edge_connection(sm_matr_t *matrix, sm_list_t *list, int *e_c, int a_city, int b_city, sm_list_t **routes)
{
	sm_matr_t *matr_routes = NULL;
	matr_routes = malloc(sizeof(sm_matr_t));
	if (!matr_routes)
	{
		printf("Error in alloc\n");
		return 1;
	}
	matr_routes->matr = calloc(matrix->size, sizeof(int *));
	if (!matr_routes->matr)
	{
		printf("Error in alloc\n");
		return 1;
	}
	for (int i = 0; i < matrix->size; i ++)
	{
		matr_routes->matr[i] = calloc(matrix->size, sizeof(int));
		if (!matr_routes->matr[i])
		{
			printf("Error in alloc\n");
			return 1;
		}
	}
	matr_routes->size = matrix->size;
	for (int i = 0; i < matrix->size; i ++)
	{
		for (int j  = 0; j < matrix->size; j ++)
		{
			matr_routes->matr[i][j] = matrix->matr[i][j];
		}
	}


	*routes = malloc(sizeof(sm_list_t));
	(*routes)->arr = calloc(matrix->size, sizeof(sm_matr_t));
	sm_node_t *route = NULL;
	sm_node_t *next = NULL;
	while(route_exists(matr_routes, a_city, b_city, &((*routes)->arr[*e_c])))
	{
		sm_node_t *route_copy = (*routes)->arr[*e_c];
		while((*routes)->arr[*e_c]->next)
		{
			matr_routes->matr[(*routes)->arr[*e_c]->city][((*routes)->arr[*e_c]->next)->city] = 0;
			matr_routes->matr[((*routes)->arr[*e_c]->next)->city][(*routes)->arr[*e_c]->city] = 0;
			(*routes)->arr[*e_c] = (*routes)->arr[*e_c]->next;
		}

		(*routes)->arr[*e_c] = route_copy;
		printf("route[%d]:\n", *e_c);
		print_list((*routes)->arr[*e_c]);
		(*e_c) ++;
	}
	printf("\nmatr of routes\n");
	output_matr(matr_routes);
	//graph_viz(matr_routes);
	(*routes)->size = *e_c;
	return 0;
}*/
int matr_copy(const sm_matr_t *m1, sm_matr_t **m2)
{
	*m2 = malloc(sizeof(sm_matr_t));
	(*m2)->matr = calloc(m1->size, sizeof(int *));
	(*m2)->size = m1->size;
	if ((*m2)->matr == NULL)
	{
		printf("ERROR in alloc\n");
		return 1;
	}
	for (int i = 0; i < (*m2)->size; i ++)
	{
		(*m2)->matr[i] = calloc((*m2)->size, sizeof(int));	
		if ((*m2)->matr[i] == NULL)
		{
			printf("ERROR in alloc\n");
			return 1;
		}
	}
	for (int i = 0; i < (*m2)->size; i ++)
	{
		for (int j = 0; j < (*m2)->size; j ++)
		{
			(*m2)->matr[i][j] = m1->matr[i][j];
		}
	}
}
void destroy_matr(sm_matr_t **matrix)
{
	for (int i = 0; i < (*matrix)->size; i ++)
	{
		free((*matrix)->matr[i]);
	}
	free((*matrix)->matr);
	(*matrix)->size = 0;
	free((*matrix));
	(*matrix) = NULL;
}
/*void perebor(const sm_matr_t *matrix, sm_list_t *routes, int **bridges, int a_city, int b_city)
{
	int i_b = 0;
	sm_matr_t *matr_copied = NULL;
	if (routes->size == 1)
	{
		while (routes->arr[0]->next)
		{
			matr_copy(matrix, &matr_copied);
			matr_copied->matr[routes->arr[0]->city][routes->arr[0]->next->city] = 0;
			matr_copied->matr[routes->arr[0]->next->city][routes->arr[0]->city] = 0;
			if (!route_exists_classic(matr_copied, a_city, b_city))
			{
				bridges[i_b][0] = routes->arr[0]->city;
				bridges[i_b][1] = routes->arr[0]->next->city;
				i_b ++;
				break;
			}
			routes->arr[0] = routes->arr[0]->next;
			destroy_matr(&matr_copied);
		}
	}
	else if (routes->size == 2)
	{
		while (routes->arr[0]->next)
		{
			//printf("Income\n");
			sm_node_t *tmp;// = malloc(sizeof(sm_node_t));
			tmp = routes->arr[1];
			int flag = 0;
			while(tmp->next)
			{
				matr_copy(matrix, &matr_copied);
				matr_copied->matr[routes->arr[0]->city][routes->arr[0]->next->city] = 0;
				matr_copied->matr[routes->arr[0]->next->city][routes->arr[0]->city] = 0;
				matr_copied->matr[tmp->city][tmp->next->city] = 0;
				matr_copied->matr[tmp->next->city][tmp->city] = 0;
				if (!route_exists_classic(matr_copied, a_city, b_city))
				{
					bridges[i_b][0] = routes->arr[0]->city;
					bridges[i_b][1] = routes->arr[0]->next->city;
					i_b ++;
					bridges[i_b][0] = tmp->city;
					bridges[i_b][1] = tmp->next->city;
					i_b ++;
					flag = 1;
					break;
				}
				tmp = tmp->next;
				destroy_matr(&matr_copied);
			}
			if (flag)
				break;
		}		
	}
	else if (routes->size == 3)
	{
		printf("INCOME\n");
		int flag = 0, flag2 = 0;
		while (routes->arr[0]->next)
		{
			printf("INCOME1\n");
			sm_node_t *tmp ;//= malloc(sizeof(sm_node_t));
			tmp = routes->arr[1];
			while(tmp->next)
			{
				printf("INCOME2\n");
				sm_node_t *tmp2;// = malloc(sizeof(sm_node_t));
				tmp2 = routes->arr[2];
				while(tmp2->next)
				{
					printf("INCOME3\n");
					matr_copy(matrix, &matr_copied);
					matr_copied->matr[routes->arr[0]->city][routes->arr[0]->next->city] = 0;
					matr_copied->matr[routes->arr[0]->next->city][routes->arr[0]->city] = 0;
					matr_copied->matr[tmp->city][tmp->next->city] = 0;
					matr_copied->matr[tmp->next->city][tmp->city] = 0;
					matr_copied->matr[tmp2->city][tmp2->next->city] = 0;
					matr_copied->matr[tmp2->next->city][tmp2->city] = 0;
					if (!route_exists_classic(matr_copied, a_city, b_city))
					{
						output_matr(matrix);
						printf("\n");
						output_matr(matr_copied);

						printf("ribs1 = %d %d, i_b = %d\n", routes->arr[0]->city, routes->arr[0]->next->city, i_b);
						bridges[i_b][0] = routes->arr[0]->city;
						bridges[i_b][1] = routes->arr[0]->next->city;
						printf("ribs2 = %d %d i_b = %d\n", tmp->city, tmp->next->city, i_b);
						i_b ++;
						bridges[i_b][0] = tmp->city;
						bridges[i_b][1] = tmp->next->city;
						i_b ++;
						bridges[i_b][0] = tmp2->city;
						bridges[i_b][1] = tmp2->next->city;
						i_b ++;
						flag2 = 1;
						break;
					}
					tmp2 = tmp2->next;
					destroy_matr(&matr_copied);
				}
				if (flag2)
				{
					flag = 1;
					break;
				}
				tmp = tmp->next;
			}
			if (flag)
				break;
			routes->arr[0] = routes->arr[0]->next;
		}
	}
	else
	{
		printf("It is impossible, edge_connection > 3\n");
	}
	if (!i_b)
	{
		printf("It is impossible, edge_connection > 3\n");
	}
}*/
void final_graph_viz(sm_matr_t *matrix, int **bridges, int e_c)
{
	for (int i = 0; i < matrix->size; i ++)
	{
		for (int j = 0; j < matrix->size; j ++)
		{
			if (matrix->matr[i][j])
				matrix->matr[j][i] = 0;
		}
	}
	FILE *f = fopen("res.gv", "w");
	fprintf(f, "graph G{\n");
	int flag = 0;
	for (int i = 0; i < matrix->size; i ++)
	{
		for (int j = 0; j < matrix->size; j ++)
		{
			if (matrix->matr[i][j])
			{
				flag = 0;
				for (int k = 0; k < e_c; k ++)
				{
					if ((i == bridges[k][0] && j == bridges[k][1]) || (j == bridges[k][0] && i == bridges[k][1]))
					{	flag = 1;			 		
						fprintf(f, "\t%d -- %d[color=white];\n", i, j);
						//printf("%d %d\n", i, j);
						break;
					}
				}
				if (!flag)
				{
					fprintf(f, "\t%d -- %d;\n", i, j);
				}
				
			}
		}
	}
	fprintf(f, "}\n");
	fclose(f);
	system("dot -Tpng res.gv -o res.png");
	system("xdg-open res.png");
}
int find_connections(int **ind_i, int **ind_j, const sm_matr_t *matrix)
{
	sm_matr_t *c_matr;
	matr_copy(matrix, &c_matr);
	int eds = 0;
	for (int i = 0; i < c_matr->size; i ++)
	{
		for (int j = 0; j < c_matr->size; j ++)
		{
			if (c_matr->matr[i][j])
			{
				c_matr->matr[j][i] = 0;
				eds ++;
			}
		}
	}
	*ind_i = malloc(sizeof(int) * eds);
	*ind_j = malloc(sizeof(int) * eds);
	int i_i = 0;
	for (int i = 0; i < c_matr->size; i ++)
	{
		for (int j = 0; j < c_matr->size; j ++)
		{
			if (c_matr->matr[i][j])
			{
				(*ind_i)[i_i] = i;
				(*ind_j)[i_i] = j;
				i_i ++;
			}
		}
	}
	destroy_matr(&c_matr);
	return eds;
}
int big_perebor(const sm_matr_t *matrix/*, sm_list_t *routes*/, int **bridges, int a_city, int b_city)
{
	int *ind_i = NULL, *ind_j = NULL;
	sm_matr_t *c_matr = NULL;
	int ribs = find_connections(&ind_i, &ind_j, matrix);
	printf("ribs amount == %d\n", ribs);
	if (ribs < 3)
	{
		printf("There are less than 3 ribs in graph\n");
		return 0;
	}
	int flag = 0;
	for (int i = 0; i < ribs; i ++)
	{
		for (int j = 0; j < ribs; j ++)
		{
			for (int k = 0; k < ribs; k ++)
			{
				matr_copy(matrix, &c_matr);
				c_matr->matr[ind_i[i]][ind_j[i]] = 0;
				c_matr->matr[ind_j[i]][ind_i[i]] = 0;

				c_matr->matr[ind_i[j]][ind_j[j]] = 0;
				c_matr->matr[ind_j[j]][ind_i[j]] = 0;

				c_matr->matr[ind_i[k]][ind_j[k]] = 0;
				c_matr->matr[ind_j[k]][ind_i[k]] = 0;
				if (!route_exists_classic(c_matr, a_city, b_city))
				{
					bridges[0][0] = ind_i[i];
					bridges[0][1] = ind_j[i];
					bridges[1][0] = ind_i[j];
					bridges[1][1] = ind_j[j];
					bridges[2][0] = ind_i[k];
					bridges[2][1] = ind_j[k];
					flag =  1;
					destroy_matr(&c_matr);
					return flag;
				}
				destroy_matr(&c_matr);
			}
		}
	}
	return flag;	
}
