#include "list.h"

TLinkedList *create_list(int n,double *rand_med,FILE *filein)
{
    if( filein == NULL )
        return NULL;
    
    TLinkedList *head = NULL;
    TLinkedList *iter = NULL;
    *rand_med = 0.0;

    for(int i=0;i<n;i++)
    {
        TLinkedList *newNode = malloc (sizeof(TLinkedList));
        if(newNode == NULL)
        {
            perror("Memory allocation fault.");
            exit(EXIT_FAILURE);
        }

        fscanf(filein,"%lf",&newNode->value);
        newNode->next = NULL;

        if ( head == NULL )
        {
            newNode->rand = 0;
            head = newNode;
            iter = newNode;
        }
        else
        {

            newNode->rand = (newNode->value-iter->value) / iter->value;
            (*rand_med) += newNode->rand;

            iter->next = newNode;
            iter = newNode;
        }
    }

    *rand_med /= n-1;
    return head;
}

double volatility(int n,TLinkedList *head,double rand_med)
{
    head=head->next;
    double vol=0.0;

    while(head!=NULL)
    {
        vol += (head->rand-rand_med)*(head->rand-rand_med);
        head=head->next;
    }
    
    return sqrt(vol/(n-1));
}

double sharpe_ratio(double rand_med,double rand_risk,double vol)
{
    return (rand_med-rand_risk)/vol;
}

void free_mem(TLinkedList *head)
{
    while(head!=NULL)
    {
        TLinkedList *aux=head;
        head=head->next;
        free(aux);
    }
}