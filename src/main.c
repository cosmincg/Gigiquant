#include "list.h"

int main(int argc,const char *argv[])
{

    
    FILE *filein=fopen(argv[1],"r");
    FILE *fileout=fopen(argv[2],"w");
    double rand_med;
    int n;
    
    fscanf(filein,"%d",&n);
    TLinkedList *head=create_list(n,&rand_med,filein);

    fprintf(fileout,"%.3f",rand_med);

    free_mem(head);
    fclose(filein);
    fclose(fileout);
    return 0;
}