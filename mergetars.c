#include "mergetars.h"

//arrays//
char** TempDir;
FILES* files;

int main(int argc, char *argv[])
{
    //Initalisations and defintions for ease of reading//
    int TempDirNeeded;
    TempDirNeeded = argc-2;
    TempDir = malloc(TempDirNeeded*sizeof(*TempDir));
    printf("Directory Count: %i\n", TempDirNeeded);

    //FAILURE CONDITION//
    if(argc<3)
    {
        fprintf(stderr, "Mergetars expects 3 arguments, but recieved only %i\n", argc);
        exit(EXIT_FAILURE);
    }

    //TODO ADD FUNCTIONS//
    createdir(TempDirNeeded, TempDir);
    clean(TempDirNeeded, TempDir);    

    //debugging//
    for(int i=0; i<TempDirNeeded; i++)
    {
        printf("Dir %i: %s\n", i+1, TempDir[i]);
    }

    exit(EXIT_SUCCESS);
}
