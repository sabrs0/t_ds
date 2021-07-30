#define OK 0
#define ERROR 1
#define MAX_STACK_SIZE 1024
typedef struct node
{
    char bracket;
    struct node *next;
	int ind;
}Stack_list;
typedef struct array
{
	size_t arr[MAX_STACK_SIZE];
	int ind;
}free_sp;
void print_list(Stack_list **head, free_sp *arr);
void delete_stack(Stack_list **head, free_sp *arr);
int push(Stack_list **head, char bracket, free_sp *arr);
char get_top(Stack_list **head);
int delete_top(Stack_list **head, free_sp *arr);
int process_list(Stack_list **head, char string[], free_sp *arr);
int create_free_sp_arr(free_sp **array);
void print_free_sp(free_sp *arr);
