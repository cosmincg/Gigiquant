#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    double value;
    double rand;
    struct Node *next;
}TLinkedList;

TLinkedList *create_list(int n,double *rand_med,FILE *filein);
void free_mem(TLinkedList *head);