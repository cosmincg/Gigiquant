#include "numberfile.h"

//  Functie pentru a returna numarul fisierului
int number_file(const char *argv)
{
    int nr=0;
    for(int i = 0; argv[i] != '\0'; i++)
        if(isdigit(argv[i]))
            nr = nr*10+(argv[i]-'0'); 
            
    return nr;
}