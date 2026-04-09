#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node
{
    double value;
    struct node *next;
}stack;

stack **create_stack(char **name, FILE *filein);
int arbitration(double number1, double number2, double number3, double *difference);
void oportunities(char **name, stack **head, FILE *fileout);
void free_memory_stack(stack *head);