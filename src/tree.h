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

char **company_name(const char *names, int *n);
root *allocate_node(root *node,double val);
root *insert_node(root *node, double val,double last_value);
tree *read_data(FILE *filein, int n);
void tree_path(root *price,char *path,int depth);
void reversed_path(const char *path, char *reversed);
int paths(const char *path1, const char *path2);
void free_bst(root *node);
