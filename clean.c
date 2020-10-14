#include "mergetars.h"

    /*Clean//
    Clean, when given an array of directories and the size of the array, will
    delete the directories and their contents.

    Uses program "rm" with flags "-r" and "-v". Process forks, child becomes
    rm and parent waits.

    Notes:
    - TempDirectories is an array of temporary directories
    - n is the size of the temporary directories array*/

void clean(int n, char** TempDirectories)
{
    int pid;

    //creates a process for every directory created//
    for(int i=0; i<n; i++)   
    {
        pid = fork();
        switch(pid)
        {
            case -1:
                fprintf(stderr, "clean: fork() failed\n");
                exit(EXIT_FAILURE);
                break;

            case 0:
                execl("/bin/rm", "rm","-r","-v", TempDirectories[i], NULL);       
                break;

            default:
            {
                int child;
                int status;

                child = wait(&status);
                printf("Process %i terminated with status %i\n", 
                        child, WEXITSTATUS(status));
                break;
            }
        }
    }
}
