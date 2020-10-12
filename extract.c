#include "mergetars.h"

//decompresses and empties contents of tar files into the temporary directories//
char extractPath[MAXPATHLEN];

void extract(char *TempDirectories, char *argv[], int numbOfTars)
{
    int pid;
    for(int i=0;i<numbOfTars;i++)
    {
        strcpy(extractPath,TempDirectories); // wasn't sure whether to use this or strncpy, 
        pid=fork();
        switch(pid)
        {
            case -1:
                fprintf(stderr,"extract: fork() failed in extracting tar and im straight up not having a good time\n");
                exit(EXIT_FAILURE);
            case 0:
                execl("/bin/tar",........); // having trouble getting this to work will revisit this after a nap. it shouldn't be too hard
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



