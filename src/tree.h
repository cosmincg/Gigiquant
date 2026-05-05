#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_tree
{
    double value;
    struct Node_tree *left,*right;
}root;

typedef struct tree
{
    root *price;
}tree;

char **company_name(char *names, int *n);
root *insert_node(root *price, double val);
tree *read_data(FILE *filein, int n);
void free_bst(root *node);