#include "list.h"

int main(int argc,const char *argv[])
{

    
    FILE *filein=fopen(argv[1],"r");
    FILE *fileout=fopen(argv[2],"w");
    double rand_med;
    int n;
    double vol;
    double sharpe;
    double rand_risk=0.0;

    fscanf(filein,"%d",&n);
    TLinkedList *head=create_list(n,&rand_med,filein);
    vol=volatility(n,head,rand_med);
    sharpe=sharpe_ratio(rand_med,rand_risk,vol);

    rand_med = (int)(rand_med*1000);
    rand_med /= 1000;

    vol = (int)(vol*1000);
    vol /= 1000;

    sharpe = (int)(sharpe*1000);
    sharpe /= 1000;

    fprintf(fileout,"%.3f\n",rand_med);
    fprintf(fileout,"%.3f\n",vol);
    fprintf(fileout,"%.3f",sharpe);
    free_mem(head);
    fclose(filein);
    fclose(fileout);
    return 0;
}