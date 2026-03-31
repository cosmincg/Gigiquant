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
            iter->next = newNode;

            newNode->rand = (newNode->value-iter->value) / iter->value;
            (*rand_med) += newNode->rand;

            iter = newNode;
        }
    }

    *rand_med /= n;
    return head;
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