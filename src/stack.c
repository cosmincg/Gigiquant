#include "stack.h"

stack **create_stack(int *day,char **name,FILE *filein)
{
    stack **head=malloc(3*sizeof(stack*));
    if(head==NULL)
    {
        perror("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<3;i++)
    {
        head[i]=NULL;
        day[i]=0;
    }

    char line[15]="\0"; 
    int k=-1;
    int number_days=0;

    //  Parcurgem fisierul
    while(fgets(line, sizeof(line), filein))
    {

        line[strcspn(line, "\n")] = '\0';

        //  Verificam daca este de o valoare numerica.
        if(line[0]>='0'&&line[0]<='9')
        {
            stack *newNode=malloc(sizeof(stack));
            if(newNode==NULL)
            {
                perror("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            number_days++;
            //  Transformam valoarea numerica in double din char
            char *endp;
            double val;
            val=strtod(line,&endp);

            newNode->value=val;
                
            newNode->next=head[k];
            head[k]=newNode;
        }
        //  Pastram numele orasului
        else
        {
            k++;
            day[k]=number_days;
            strcpy(name[k],line);
            number_days=0;
        }
    }

    return head;
}

//  Functie pentru eliberarea memoriei a stivei
void free_memory_stack(stack *head)
{
    while(head!=NULL)
    {
        stack *aux=head;
        head=head->next;
        free(aux);
    }
}