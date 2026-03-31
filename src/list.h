#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Node
{
    double value;
    double rand;
    struct Node *next;
}TLinkedList;

TLinkedList *create_list(int n,double *rand_med,FILE *filein);
double volatility(int n,TLinkedList *head,double rand_med);
double sharpe_ratio(double rand_med,double rand_risk,double vol);
void free_mem(TLinkedList *head);
