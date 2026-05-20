#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int curr_up;
    int curr_down;
    int prec_up;
    int prec_down;
}graph;

typedef struct calls
{
    int value;
    struct calls *next;
}calls;

typedef struct
{
    int size;
    calls *front,*rear;
}Queue;

int value_node(double value, double dimension);
int *read_task4(FILE *filein,int *observation, double *dimension, int *days, int *start, int *target);
int number_nodes(int *values, int observation, int *minimum);
int return_node(int value, int minimum);
graph *markov_graph(int *values,int observation, int minimum, int ***markov, int **prob);
Queue *createQueue();
void enQueue(Queue *q, int val);
int deQueue(Queue *q);
int cmmdc(int a, int b);
graph fractie(graph next, int up, int down);
graph next_day(graph muchie, graph next, int prob);
void calculate_graph(graph *markov_graph, int **markov, int nodes, Queue *q, int *prob);
void free_queue(Queue *q);