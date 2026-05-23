#include "markov.h"

int value_node(double value, double dimension)
{
    return (int)(value/dimension);
}

int *read_task4(FILE *filein,int *observation, double *dimension, int *days, int *start, int *target)
{
    double temp;
    fscanf(filein, "%d", observation);
    fscanf(filein, "%lf", dimension);
    fscanf(filein, "%d", days);
    fscanf(filein, "%lf", &temp);
    *start = value_node(temp, *dimension);

    fscanf(filein, "%lf", &temp);
    *target = value_node(temp, *dimension);

    int *values = malloc(*observation * sizeof(int));
    if(values == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < *observation; i++)
    {
        fscanf(filein, "%lf", &temp);
        values[i] = value_node(temp, *dimension);
    }
    return values;
}

int number_nodes(const int *values, int observation, int *minimum)
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

graph *markov_graph(const int *values,int observation, int minimum, int ***markov, int **prob)
{

    int max = values[0];
    for(int i = 1; i < observation; i++)
        if(max < values[i])
            max = values[i];
    
    int nodes = max - minimum + 1;

    graph *markov_nodes = calloc(nodes, sizeof(graph));
    if(markov_nodes == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    *markov = malloc(nodes * sizeof(int*));
    if(*markov == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nodes; i++)
    {
        (*markov)[i] = malloc(nodes * sizeof(int));
        if((*markov)[i] == NULL)
        {
            perror("Memory allocation failed.");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < nodes; i++)
    {
        for(int j = 0; j < nodes; j++)
        {
            (*markov)[i][j] = 0;
        }
    }

    for(int i = 0; i < observation - 1; i++)
    {
        int curr = return_node(values[i], minimum);
        int next = return_node(values[i+1], minimum);

        (*markov)[curr][next]++;
    }

    *prob = malloc(nodes * sizeof(int));
    if(*prob == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nodes; i++)
    {
        int nr_muchii = 0;
        for(int j = 0; j < nodes; j++)
            nr_muchii += (*markov)[i][j];

        (*prob)[i] = nr_muchii;
    }

    return markov_nodes;
}

Queue *createQueue()
{
    Queue * q;
    q = malloc(sizeof(Queue));
    if (q == NULL) 
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    
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

graph next_day(graph muchie, graph next, int prob, int edge)
{
    int up = muchie.prec_up * edge;
    int down = muchie.prec_down * prob;
    return fractie(next,up,down);
}

void calculate_graph(graph *markov_graph, int **markov, int nodes, Queue *q, const int *prob)
{
    for(int i = 0; i < nodes; i++)
    {
        markov_graph[i].prec_down = markov_graph[i].curr_down;
        markov_graph[i].prec_up = markov_graph[i].curr_up;
        markov_graph[i].curr_up = 0;
        markov_graph[i].curr_down = 1;
    }

    while(q -> size > 0)
        deQueue(q);

    for(int i = 0; i < nodes; i++)
    {
        if(markov_graph[i].prec_up != 0)
            enQueue(q,i);
    }

    int iter = q -> size;

    for(int i = 0; i < iter; i++)
    {
        int curr = deQueue(q);
        graph current = markov_graph[curr];

        for(int j = 0; j < nodes; j++)
            if(markov[curr][j])
            {
                markov_graph[j] = next_day(current,markov_graph[j],prob[curr],markov[curr][j]);
            }
    }
}

void free_queue(Queue *q)
{
    while(q -> front != NULL)
    {
        Queue *aux = q;
        q -> front = q -> front -> next; 
        free(aux);
    }
    free(q);
}

