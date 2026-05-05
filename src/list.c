#include "list.h"

//  Functie pentru crearea listei inlantuite
TLinkedList *create_list(int n,double *rand_med,FILE *filein)
{
    if( filein == NULL )
        return NULL;
    
    TLinkedList *head = NULL;
    TLinkedList *iter = NULL;
    *rand_med = 0.0;

    for(int i = 0; i < n; i++)
    {
        TLinkedList *newNode = malloc (sizeof(TLinkedList));
        if(newNode == NULL)
        {
            perror("Memory allocation failed.");
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
            //  Folosim formula pentru randamentul a fiecarui nod incepand cu al doilea
            newNode->rand = (newNode->value-iter->value) / iter->value;

            //  Adaugam randamentul pentru a calcula randamentul mediu  
            (*rand_med) += newNode->rand;
    
            iter->next = newNode;
            iter = newNode;
        }
    }

    //  Impartim la n-1 deoarece am calculat n-1 randamente
    *rand_med /= n-1;
    return head;
}

//  Functie pentru calcularea volatilitatii
double volatility(int n,TLinkedList *head,double rand_med)
{
    //  Nu luam in considerare primul element deoarece nu are randament
    head = head->next;
    double vol = 0.0;

    while(head != NULL)
    {
        //  Adunam fiecare randament la patrat
        vol += (head->rand-rand_med)*(head->rand-rand_med);
        head = head->next;
    }
    
    //  Returnam radical din media obtinuta
    return sqrt(vol / (n-1));
}

//  Functie pentru a calcula Sharpe Ratio
double sharpe_ratio(double rand_med,double rand_risk,double vol)
{
    return (rand_med-rand_risk)/vol;
}

// Functie pentru a elibera memoria
void free_memory_list(TLinkedList *head)
{
    while(head != NULL)
    {
        TLinkedList *aux = head;
        head = head->next;
        free(aux);
    }
}   