#include "list.h"
#include "numberfile.h"

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


            fscanf(filein,"%d",&n);
            TLinkedList *head = create_list(n,&rand_med,filein);
            vol = volatility(n,head,rand_med);
            sharpe = sharpe_ratio(rand_med,rand_risk,vol);

            //  Trunchiem fiecare valoare
            rand_med = (int)(rand_med*1000);
            rand_med /= 1000;

            vol = (int)(vol*1000);
            vol /= 1000;

            sharpe = (int)(sharpe*1000);
            sharpe /= 1000;


            fprintf(fileout,"%.3f\n",rand_med);
            fprintf(fileout,"%.3f\n",vol);
            fprintf(fileout,"%.3f\n",sharpe);

            //  Eliberam memoria
            free_mem(head);
    }

    //  Inchidem fisierele
    fclose(filein);
    fclose(fileout);

    return 0;
}