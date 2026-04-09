#include "stack.h"

stack **create_stack(char **name, FILE *filein)
{
    stack **head = malloc(3 * sizeof(stack*));
    if(head == NULL)
    {
        perror("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 3; i++)
    {
        head[i] = NULL;
    }

    char line[15] = "\0"; 
    int k = -1;

    //  Parcurgem fisierul
    while(fgets(line, sizeof(line), filein))
    {

        line[strcspn(line, "\n")] = '\0';

        //  Verificam daca este de o valoare numerica.
        if(line[0] >= '0' && line[0] <= '9')
        {
            stack *newNode = malloc(sizeof(stack));
            if(newNode == NULL)
            {
                perror("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            
            //  Transformam valoarea numerica in double din char
            char *endp;
            double val;
            val = strtod(line,&endp);

            newNode -> value = val;
                
            newNode -> next = head[k];
            head[k] = newNode;
        }
        //  Pastram numele orasului
        else
        {
            k++;
            strcpy(name[k], line);
        }
    }

    return head;
}

int arbitration(double number1, double number2, double number3, double *difference)
{
    if(number1 == number2)
        if(number1 != number3)
        {
            *difference = fabs (number1 - number3);
            return 3;
        }

    if(number1 == number3)
        if(number1 != number2)
        {
            *difference = fabs(number2 - number3);
            return 2;
        }

    if(number2 == number3)
        if(number1 != number2)
        {
            *difference = fabs(number1 - number2);
            return 1;
        }
    
    *difference=0.0;
    return 0;
}


void oportunities(char **name, stack **head,FILE *fileout)
{
    stack *head1=head[0],*head2=head[1],*head3=head[2];
    int i=1;
    while(head1 != NULL && head2 != NULL && head3 != NULL)
    {
        double difference;
        int position=arbitration(head1 -> value, head2 -> value, head3 -> value,&difference);

        if(position)
        {
            position--;
            fprintf(fileout, "ziua %d - %.2f - %s\n", i, difference, name[position]);
        }
        i++;

        head1 = head1 -> next;
        head2 = head2 -> next;
        head3 = head3 -> next;
    }
}

//  Functie pentru eliberarea memoriei a stivei
void free_memory_stack(stack *head)
{
    while(head != NULL)
    {
        stack *aux = head;
        head = head -> next;
        free(aux);
    }
}