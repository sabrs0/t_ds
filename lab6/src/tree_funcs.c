#include "../inc/structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void infix_print_tree(tree_t *tr_node)
{
    tree_t *tmp = tr_node;
    if (tmp != NULL)
    {
        infix_print_tree(tmp->left);
        printf("%s - %p, parent - %p(%s)\n", tmp->string, tmp, tmp->prnt, (tmp->prnt)->string);
        infix_print_tree(tmp->right);
    }
}
tree_t *create_t_node(char word[])
{
	tree_t *tmp = malloc(sizeof(tree_t));
	if (tmp)
	{
		tmp->right = NULL;
		tmp->left = NULL;
		strcpy(tmp->string, word);
	}
	return tmp;
}
void destruct_tree(tree_t *root)
{
    if (root != NULL)
    {
        destruct_tree(root->left);
        destruct_tree(root->right);
		free(root);
		root = NULL;
    }
	
}
int tree_insert(tree_t **root, tree_t *node)
{
	tree_t *tmp = *root;
	tree_t *prnt = NULL;
	while (tmp)
	{
		prnt = tmp;
		if (strcmp(node->string, tmp->string) < 0)
		{
			tmp = tmp->left;
		}
		else
		{
			tmp = tmp->right;
		}
	}
	node->prnt = prnt;
	if (!prnt)
	{
		*root = node;
		return OK;
	}
	if (strcmp(node->string, prnt->string) < 0)
	{
		prnt->left = node;
	}
	else if (strcmp(node->string, prnt->string) > 0)
	{
		prnt->right = node;
	}
	else
		printf("Same string\n");
	return OK;
}
int build_tree(tree_t **root, char filename[])
{
	char word[256];
	char c;
	tree_t *node;
	FILE *f = fopen(filename, "r");
	if (!f)
	{
		printf("Cannot open file\n");
		return ERROR;
	}
	while(fscanf(f, "%s", word) != EOF)
	{
		fflush(stdin);
		node = create_t_node(word);
		if (tree_insert(root, node))
		{
			printf("Cannot insert element in the tree\n");
			return 1;
		}
	}
	fclose(f);
	return OK;
}
void print_tree(tree_t *root, int space)
{
	int spacing = 5;
    if (root == NULL)
    {
        return;
    }
    space += spacing;
    print_tree(root->right, space);
    printf("\n");
    for (int i = spacing; i < space; i++)
    {
        printf(" ");
    }
    printf("%s\n", root->string);

    print_tree(root->left, space);
}
tree_t *leftest_in_right(tree_t *root)
{
	if (root->right)
	{
		root = root->right;
		while (root->left)
		{
			root = root->left;
		}
	}
	return root;
}
tree_t *delete_tree(tree_t **root, tree_t *deleted, int *if_c)
{
	(*if_c)++;
	if (deleted == NULL)
	{
		return NULL;
	}	
	tree_t *y;
	tree_t *x;
	(*if_c)++;
	if (deleted->left == NULL || deleted->right == NULL)
	{
		y = deleted;	
	}
	else
	{
		y = leftest_in_right(deleted);
	}
	(*if_c)++;
	if (y->left)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	(*if_c)++;
	if (x)
	{
		x->prnt = y->prnt;
	}
	if (!y->prnt)
	{
		(*if_c)++;
		*root = x;
	}
	else if (y == (y->prnt)->left)	
	{
		(*if_c)++;
		(y->prnt)->left = x;
	}
	else
	{
		(*if_c)++;
		(y->prnt)->right = x;
	}
	(*if_c)++;
	if (y != deleted)
	{
		strcpy(deleted->string, y->string);
	}
	return y;
}
int height(tree_t *node)
{
	if (node)
	{
		
		if (!node->right && !node->left)
		{
			return 0;
		}
		else return node->height;
	}
	else
		return 0;
	
}
int b_factor(tree_t *node)
{
	return height(node->right) - height(node->left);
}
void fixheight(tree_t *node)
{	
	int hr, hl;
	hr = height(node->right);
	hl = height(node->left);
	node->height = (hl<hr?hr:hl) + 1;
}
tree_t *rotate_right(tree_t *node)
{
	tree_t *tmp = malloc(sizeof(tree_t));
	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	tmp->prnt = node->prnt;
	node->prnt = tmp;
	if(node->left)
		(node->left)->prnt = node;
	fixheight(node);
	fixheight(tmp);
	return tmp;
}
tree_t *rotate_left(tree_t *node)
{
	tree_t *tmp = malloc(sizeof(tree_t));
	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	tmp->prnt = node->prnt;
	node->prnt = tmp;
	if (node->right)
		(node->right)->prnt = node;
	fixheight(node);
	fixheight(tmp);
	return tmp;
}
tree_t *balance( tree_t *node)
{
	fixheight(node);
	if (b_factor(node) == 2)
	{
		if (b_factor(node->right) < 0)
			node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	if (b_factor(node) == -2)
	{
		if (b_factor(node->left) > 0)
		{
			node->left = rotate_left(node->left);
		}
		return rotate_right(node);
	}
	return node;
}
tree_t *balance_insert(tree_t *node, char word[], tree_t *prnt)
{
	if (node == NULL)
	{
		
		node = malloc(sizeof(tree_t));
		if (!node)
		{
			printf("Cannot allocate memory\n");
		}
		else
		{
			strcpy(node->string, word);
			node->left = NULL;
			node->right = NULL;
			node->prnt = prnt;
		}
	}
	else
	{
		prnt = node;
		if (strcmp(word, node->string) < 0)
		{
			tree_t *added;
			added = balance_insert(node->left, word, prnt);
			node->left = added;
			node = balance(node);
		}
		else if (strcmp(word, node->string) > 0)
		{
			tree_t *added;
			added = balance_insert(node->right, word, prnt);
			node->right = added;
			node = balance(node);
		}
		else
		{
			printf("Same string\n");
		}
	}
	return node;
}
tree_t *find_root(tree_t *node)
{
	if (node)
	{
		while(node->prnt)
		{
			node = node->prnt;
		}
	}
	return node;
}
int build_balanced_tree(tree_t **root, char filename[])
{
	char word[256];
	char c;
	tree_t *node = *root;
	tree_t *prnt = NULL;
	int x =0;
	FILE *f = fopen(filename, "r");
	if (!f)
	{
		printf("Cannot open file\n");
		return ERROR;
	}
	while(fscanf(f, "%s", word) != EOF)
	{
		fflush(stdin);
		node = balance_insert(*root, word, prnt);
		if (!node)
		{
			printf("Cannot insert element in the tree\n");
			return 1;
		}
		*root = find_root(node);
		prnt = (*root)->prnt;
	}
	fclose(f);
	return OK;
}
tree_t *rec_delete(tree_t **root, tree_t *node, char word[], int *if_c)
{
	if (node)
	{
		if (strcmp(word, node->string) == 0)
		{
			(*if_c)++;
			tree_t *deleted;
			tree_t *prnt = node;
			deleted = delete_tree(root, node, if_c);
			prnt = balance(prnt);
			return deleted;
		}
		else if (strcmp(word, node->string) < 0)
		{
			(*if_c)++;
			rec_delete(root, node->left, word, if_c);	
			node = balance(node);
		}
		else
		{
			rec_delete(root, node->right, word, if_c);
			node = balance(node);
		}
	}
	else
	{	
		printf("Nothing to delete\n");
	}
}
tree_t *tree_search(tree_t *root, char word[], int *if_c)
{
	while (root != NULL && strcmp(root->string, word))
	{
		(*if_c)++;
		if (strcmp(word, root->string) < 0)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
		
	}
	(*if_c)++;
	if (!root)
	{
		printf("Nothing to delete\n");
	}
	return root;
}
