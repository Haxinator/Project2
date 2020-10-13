#include "mergetars.h"

//decompresses and empties contents of tar files into the temporary directories//
char extractPath[MAXPATHLEN];

void extract(char *TempDirectories, char *argv[], int argc)
{
    int pid;
    for(int i=0;i<argc-2;i++)
    {
        strcpy(extractPath,TempDirectories); // wasn't sure whether to use this or strncpy, 
        pid=fork();
        switch(pid)
        {
            case -1:
                fprintf(stderr,"extract: fork() failed in extracting tar and im straight up not having a good time\n");
                exit(EXIT_FAILURE);
            case 0:
                execl("/bin/tar","-xvf",argv[i+1],"--directory", tempDirectories[i]); // having trouble getting this to work will revisit this after a nap. it shouldn't be too hard
            default:
                {
                    int child;
                    int status;
                    
                    child=wait(&status);
                    break;
                }
        
        }
    
    }
}



