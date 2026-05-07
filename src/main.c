#include "list.h"
#include "numberfile.h"
#include "stack.h"
#include "tree.h"

int main(int argc,const char *argv[])
{

    // Deschiderea fisierelor
    if(argc < 3 || argv[1] == NULL || argv[2] == NULL)
    {
        return 0;
    }

    FILE *filein = fopen(argv[1],"r");
    FILE *fileout = fopen(argv[2],"w");

    // Extragerea numarului din fisier
    int numberfile = number_file(argv[1]);    

    // Verificam ce tip de fisier este
    if(numberfile <= 5)
    {
            int n;
            double rand_med;
            double vol;
            double sharpe;
            double rand_risk = 0.0;


            fscanf(filein, "%d", &n);
            TLinkedList *head = create_list(n, &rand_med, filein);
            vol = volatility(n, head, rand_med);
            sharpe = sharpe_ratio(rand_med, rand_risk, vol);

            //  Trunchiem fiecare valoare
            rand_med = (int)(rand_med * 1000);
            rand_med /= 1000;

            vol = (int)(vol * 1000);
            vol /= 1000;

            sharpe = (int)(sharpe * 1000);
            sharpe /= 1000;


            fprintf(fileout, "%.3f\n", rand_med);
            fprintf(fileout, "%.3f\n", vol);
            fprintf(fileout, "%.3f\n", sharpe);

            //  Eliberam memoria
            free_memory_list(head);
    }
    else
        if(numberfile <= 10)
        {
            char **name = malloc(3 * sizeof(char*));
            if(name == NULL)
            {
                perror("Memory allocation failed.");
                exit(EXIT_FAILURE);
            }

            for(int i = 0; i < 3; i++)
            {
                name[i] = malloc(15 * sizeof(char));

                if(name[i] == NULL)
                {
                    perror("Memory allocation failed.");
                    exit(EXIT_FAILURE);
                }
            }


            stack **head;

            head=create_stack(name, filein);

            oportunities(name, head, fileout);

            //  Eliberarea memoriei
            for(int i = 0; i < 3; i++)
            {
                free_memory_stack(head[i]);
                free(name[i]);
            }
            free(name);
            free(head);
        }
        else
            if(numberfile <= 15)
            {
                int n;
                char *names=malloc(100 * sizeof(char));

                if(names == NULL)
                {
                    perror("Memory allocation failed.");
                    exit(EXIT_FAILURE);
                }

                fgets(names, 100, filein);

                char **company;
                company = company_name(names, &n);

                tree *company_stock = read_data(filein, n);

                int x=0;
                for(int k = 0; k < 2; k++)
                {
                    for(int i = 0; i < n-1; i++)
                    {
                        for(int j = i+1; j < n; j++)
                        {
                            char *path1 = NULL,*path2 = NULL,*reversed = NULL;
                            path1 = malloc(50*sizeof(char));
                            path2 = malloc(50*sizeof(char));
                        
                            path1[0] = path2[0] = '\0';
                            tree_path(company_stock[i].price,path1,0);
                            tree_path(company_stock[j].price,path2,0);

                            reversed = malloc(strlen(path2)+1);
                            reversed_path(path2,reversed);
                            reversed[strlen(reversed)]='\0';

                            if(paths(path1,reversed))
                            {
                                if(k == 0)
                                    x++;
                                else
                                {
                                    fprintf(fileout,"%s-%s",company[i],company[j]);
                                    if(x>1)
                                    {
                                        char space='\n';
                                        fprintf(fileout,"%c",space);
                                    }
                                    x--;
                                }
                            }

                            free(path1);
                            free(path2);
                            free(reversed);
                        }
                    }
                }

                for(int i = 0; i < n; i++)
                {
                    free_bst(company_stock[i].price);
                    free(company[i]);
                }

                free(names);
                free(company);
                free(company_stock);
            }

    //  Inchidem fisierele
    fclose(filein);
    fclose(fileout);

    return 0;
}