#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    double value;
    struct node *next;
}stack;

stack **create_stack(int *day,char **name,FILE *filein);
void free_memory_stack(stack *head);
void list_stack(stack *head);