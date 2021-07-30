#define OK 0
#define ERROR 1
typedef struct node
{
	char string[256];
	struct node *left;
	struct node *right;
	struct node *prnt;
	int height;
} tree_t;
typedef struct hash_node
{
	char string[256];
	struct hash_node *next;
} hash_node_t;
typedef struct hash_table
{
	hash_node_t **elems;
	int len;
} hash_table_t;
