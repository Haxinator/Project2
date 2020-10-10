#include "mergetars.h"

char** TempDir;

int main(int argc, char *argv[])
{
    //Initalisations and defintions for ease of reading//
    int TempDirNeeded;
    TempDirNeeded = argc-2;
    TempDir = malloc(TempDirNeeded*sizeof(*TempDir));

    for(int i; i<TempDirNeeded; i++)
    {
        *TempDir = malloc(20*sizeof(char));
        TempDir++;
    }
        TempDir-=TempDirNeeded;

    //FAILURE CONDITION//
    if(argc<3)
    {
        fprintf(stderr, "Mergetars expects 3 arguments, but recieved only %i\n", argc);
        exit(EXIT_FAILURE);
    }

    //TODO ADD FUNCTIONS//
    createdir(TempDirNeeded, TempDir);

    for(int i=0; i<TempDirNeeded; i++)
    {
        printf("%s\n", *TempDir);
        TempDir++;
    }

    exit(EXIT_SUCCESS);
}
