#define ERROR 1
#define OK 0
typedef struct
{
	int ind;
	double time;
} elem_t;

typedef struct
{
	int tail;
	int head;
	int size;
	int len;
	elem_t *arr;
} q_arr_t;


typedef struct node
{
	elem_t node_el;
	struct node *next;	

} q_node_t;


typedef struct
{
	q_node_t *head, *tail;
	int size, len;

} q_list_t;

typedef struct
{
	size_t *arr;
	int ind;
	int len;
}free_sp;
int create_fmem_arr(free_sp **fmem, int len);
void destroy_fmem_arr(free_sp **fmem);
int create_qarr(q_arr_t **queue, int leng);
int is_full_qarr(q_arr_t *queue);
int is_empty_qarr(q_arr_t *queue);
int add_qarr(q_arr_t *queue, elem_t el);
int rm_qarr(q_arr_t *queue);
int create_qlist(q_list_t **queue, int leng);
int is_full_qlist(q_list_t *queue);
int is_empty_qlist(q_list_t *queue);
int add_qlist(q_list_t *queue, elem_t el, free_sp *fmem, int *flag);
int rm_qlist(q_list_t *queue, free_sp *fmem);
void destroy_qarr(q_arr_t **queue);
void destroy_qlist(q_list_t **queue, free_sp *fmem);
double get_time(double llim, double rlim);
int array_process(double l_in_time, double r_in_time, double l_out_time, double r_out_time, q_arr_t *queue, int cycles);
int list_process(double l_in_time, double r_in_time, double l_out_time, double r_out_time, q_list_t *queue, int cycles, free_sp *fmem);
