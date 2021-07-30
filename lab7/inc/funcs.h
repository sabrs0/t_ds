#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct
{
	int size;
	int **matr;	
}sm_matr_t;
/*typedef struct node
{
	int city;
	int power;
	struct  node *next;
}sm_node_t;
typedef struct
{
	int size;
	sm_node_t **arr;
}sm_list_t;*/
//void push(sm_node_t **head, int data);
/*sm_node_t *create_node(int data);
sm_node_t *add_end(sm_node_t *head, sm_node_t *tmp);
void pop_back(sm_node_t **head);
int get_back(sm_node_t *head);
int find_prev(sm_node_t *head);
void print_list(sm_node_t *head);
void push_back(sm_node_t **head, int data);
void dfs(sm_matr_t *matrix, int index, int *visit, int a_city, int b_city, sm_node_t **head, int *flag_b, int *prev);*/
int input_data(char filename[], sm_matr_t **matrix/*, sm_list_t **list*/);
void output_matr(const sm_matr_t *matrix);
//void output_list(sm_list_t *list);
void graph_viz(sm_matr_t *matrix);
int input_a_b_cities(int *a, int *b);
//int route_exists(sm_matr_t *matrix, int a_city, int b_city/*, sm_node_t **route*/);
//int count_edge_connection(sm_matr_t *matrix/*, sm_list_t *list*/, int *e_c, int a_city, int b_city/*, sm_list_t **routes*/);
void dfs_classic(sm_matr_t *matrix, int index, int *visit);
int route_exists_classic(sm_matr_t *matrix, int a_city, int b_city);
int matr_copy(const sm_matr_t *m1, sm_matr_t **m2);
void destroy_matr(sm_matr_t **matrix);
void perebor(const sm_matr_t *matrix/*, sm_list_t *routes*/, int **bridges, int a_city, int b_city);
void final_graph_viz(sm_matr_t *matrix, int **bridges, int e_c);
int big_perebor(const sm_matr_t *matrix/*, sm_list_t *routes*/, int **bridges, int a_city, int b_city);
