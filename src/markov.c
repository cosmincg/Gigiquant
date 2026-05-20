#include "markov.h"

int value_node(double value, double dimension)
{
    return (int)(value/dimension);
}

void read_task4(FILE *filein,int *observation, double *dimension, int *days, int *start, int *target, int **values)
{
    double temp;
    fscanf(filein, "%d", observation);
    fscanf(filein, "%lf", dimension);
    fscanf(filein, "%d", days);
    fscanf(filein, "%lf", &temp);
    *start = value_node(temp, *dimension);

    fscanf(filein, "%lf", &temp);
    *target = value_node(temp, *dimension);

    *values = malloc(*observation * sizeof(int));
    
    for(int i = 0; i < *observation; i++)
    {
        fscanf(filein, "%lf", &temp);
        (*values)[i] = value_node(temp, *dimension);
    }
}

int number_nodes(int *values, int observation, int *minimum)
{
    int max = values[0];
    int min = values[0];

    for(int i = 1; i < observation; i++)
    {
        if(max < values[i])
            max = values[i];
        
        if(min > values[i])
            min = values[i];
    }

    *minimum = min;
    return max - min + 1;
}

int return_node(int value, int minimum)
{
    return value-minimum;
}

graph *markov_graph(int *values,int observation, int minimum, int **markov)
{

    int min;
    int nodes = number_nodes(values,observation,&min);
    graph *markov_nodes = malloc(nodes * sizeof(graph));

    for(int i = 0; i < nodes; i++)
    {
        for(int j = 0; j < nodes; j++)
        {
            markov[i][j] = 0;
        }
    }

    for(int i = 0; i < observation - 1; i++)
    {
        int curr = return_node(values[i], minimum);
        int next = return_node(values[i+1], minimum);

        markov[curr][next] = 1;
    }

    for(int i = 0; i < nodes; i++)
    {
        int nr_muchii = 0;
        for(int j = 0; j < nodes; j++)
            if(markov[i][j])
                nr_muchii++;

        markov_nodes[i].curr_down = nr_muchii;
        markov_nodes[i].curr_up = 1;
        markov_nodes[i].prec_down = 0;
        markov_nodes[i].prec_up = 0;
    }

    return markov_nodes;
}

Queue *createQueue()
{
    Queue * q;
    q = malloc(sizeof(Queue));
    if (q == NULL) 
        return NULL ;
    
    q -> size = 0;
    q -> front = q -> rear = NULL ;

    return q ;
}

void enQueue(Queue *q, int val)
{
    calls *node = malloc(sizeof(calls));
    node -> value = val;
    node ->next = NULL;

    if(q -> rear == NULL) 
        q -> rear = node;
    else
    {
        q -> rear -> next = node;
        q -> rear = node;
    }

    if(q -> front == NULL)
        q -> front = q -> rear;
    q -> size ++;
}

int deQueue(Queue *q)
{
    calls *aux;
    int val;

    if(q -> front == NULL)
        return -1;

    aux = q -> front;
    val = aux -> value;

    q -> front = q -> front -> next;

    if(q -> front == NULL)
        q -> rear = NULL;
    
    free(aux);
    q -> size --;

    return val;
}

int cmmdc(int a, int b)
{
    while(b)
    {
        int aux = b;
        b = a % aux;
        a = aux;
    }

    return a;
}

graph fractie(graph next, int up, int down)
{
    int rez_up = next.curr_up * down + up * next.curr_down;
    int rez_down = next.curr_down * down;

    int cmm = cmmdc(rez_up,rez_down);
    next.curr_up = rez_up / cmm;
    next.curr_down = rez_down / cmm;

    return next;
}

graph next_day(graph muchie, graph next)
{
    int up = muchie.prec_up;
    int down = muchie.prec_down * muchie.curr_down;
    
    return fractie(next,up,down);
}

void calculate_graph(graph *markov_graph, int **markov, int nodes, Queue *q)
{
    for(int i = 0; i < nodes; i++)
    {
        markov_graph[i].prec_down = markov_graph[i].curr_down;
        markov_graph[i].prec_up = markov_graph[i].curr_up;
        markov_graph[i].curr_up = 0;
        markov_graph[i].curr_down = 1;
    }

    int iter = q -> size;
    for(int i = 0; i < iter; i++)
    {
        int curr = deQueue(q);
        for(int j = 0; j < nodes; j++)
            if(markov[curr][j])
            {
                enQueue(q,j);
                markov_graph[j] = next_day(markov_graph[curr],markov_graph[j]);
            }
    }
}


