#include "mergetars.h"

//creates a tar file containing the best duplicates//
void createTar(char* TempDir, char* OutputDestination)
{
    int pid;
    pid = fork();

    switch(pid)
    {
        case -1:
            fprintf(stderr, "failed to fork!\n");
            exit(EXIT_FAILURE);
            break;

        case 0:
            printf("OutputDest: %s\n", OutputDestination);
            printf("TempDir: %s\n", TempDir);
            execl("/bin/tar", "tar", "cvpf", OutputDestination,"-C" , TempDir,".", NULL);
            break;

        default:
        {
            int child;
            int status;
            child = wait(&status);

                printf("Process %i terminated with status %i\n", 
                            child,WEXITSTATUS(status));
        }
    }
}

