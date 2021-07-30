#define OK 0
#define ERROR 1
#define MAX_STACK_SIZE 1024
typedef struct
{
    char array[MAX_STACK_SIZE];
	int len;
}Stack_arr;
void print_arr(Stack_arr *head);
int push_arr(Stack_arr *head, char bracket);
char get_top_arr(Stack_arr *head);
int delete_top_arr(Stack_arr *head);
int process_arr(Stack_arr *head, char string[]);
int delete_arr_st(Stack_arr *head);
