#include "tree.h"

char **company_name(char *names, int *n)
{
    *n = 0;
    char **company = NULL;

    char *copy = strdup(names);
    if (copy == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    char *name = strtok(copy, ", \n\r");
    
    while(name != NULL)
    {
        //  Incrementam numarul de companii
        *n += 1;
        
        //  Alocam memorie pentru indicele fiecarei companii
        company = realloc(company, (*n) * sizeof(char*));

        if(company == NULL)
        {
            perror("Memory allocation failed.");
            exit(EXIT_FAILURE);
        }

        //  Alocam memorie pentru fiecare nume
        company[(*n) - 1] = malloc(strlen(name)+1);

        if(company[(*n) - 1] == NULL)
        {
            perror("Memory allocation failed.");
            exit(EXIT_FAILURE);
        }

        //  Copiem numele
        strcpy(company[(*n) - 1], name);

        //  Mergem la urmatorul nume
        name = strtok(NULL, ", \n\r");
    }
    free(copy);

    return company;
}

root *insert_node(root *node, double val)
{
    if(node == NULL)
    {
        node = malloc(sizeof(root));
        
        node -> value = val;
        node -> left = node -> right = NULL;
        
        return node;
    }
    else
    {
        if(node -> value > val)
            node -> left = insert_node(node -> left, val);
        else
            node -> right = insert_node(node -> right, val);
    }

    return node;
}

tree *read_data(FILE *filein, int n)
{
    tree *company_stock = malloc(n * sizeof(tree));
    if(company_stock == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++)
        company_stock[i].price = NULL;

    char *read_price = malloc(100 * sizeof(char));
    if(read_price == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    while(fgets(read_price, 100, filein) != NULL)
    {
        int id = 0;
        char *endp;

        char *everyprice = strtok(read_price, ", \n\r");

        while(everyprice != NULL && id < n)
        {
            double val = strtod(everyprice, &endp);

            if (endp == everyprice)
            {
                perror("Invalid conversion double.");
                exit(EXIT_FAILURE);
            }
            company_stock[id].price = insert_node(company_stock[id].price, val);

            id++;
            everyprice = strtok(NULL,", \n\r");
        }
    }

    free(read_price);

    return company_stock;
}

void free_bst(root *node)
{
    if(node == NULL)
        return;
    
    free_bst(node -> left);
    free_bst(node -> right);

    free(node);
}