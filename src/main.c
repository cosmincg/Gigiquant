#include "list.h"

int main(int argc,const char *argv[])
{

    
    FILE *filein=fopen(argv[1],"r");
    FILE *fileout=fopen(argv[2],"w");
    double rand_med;
    int n;
    double vol;

    fscanf(filein,"%d",&n);
    TLinkedList *head=create_list(n,&rand_med,filein);
    vol=volatility(n,head,rand_med);

    
    rand_med = (int)(rand_med*1000);
    rand_med /= 1000;

    vol = (int)(vol*1000);
    vol /= 1000;

    fprintf(fileout,"%.3f\n",rand_med);
    fprintf(fileout,"%.3f\n",vol);
    free_mem(head);
    fclose(filein);
    fclose(fileout);
    return 0;
}