#include "mergetars.h"

//arrays//
char** TempDir;
FILES *files;
int *OutputIndex;
int size;

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
    extract(TempDirNeeded, TempDir, argv);
    store(TempDirNeeded, &size, TempDir, &files);
    int SizeO = FindBestDup(&size,files, &OutputIndex);
    clean(TempDirNeeded, TempDir);
    
    //debugging//
    files = &files[0];

    for(int i=0; i<size; i++)
    {
        printf("\n\tALL FILES\n");
        printf("%i: %s\nPath %s\nSubPath %s\nModTime %i\n", i+1, files[i].name,
                        files[i].path, files[i].subPath,files[i].modTime);
        printf("Size %i\nArg %i\n", files[i].size, files[i].Arg);
    }

    for(int i=0; i<SizeO; i++)
    {
        printf("\n\tFinal Output\n");
        int Index = OutputIndex[i];
        printf("name %s \n", files[Index].name);
        printf("path %s \n", files[Index].path);
        printf("size %i \n", files[Index].size);
        printf("Mod Time %i \n", files[Index].modTime);
        printf("Arg %i \n", files[Index].Arg);
        printf("Index %i \n", OutputIndex[i]);
    }

    exit(EXIT_SUCCESS);
}
