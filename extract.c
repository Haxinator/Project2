#include "mergetars.h"

void ExtractTo(char *TempDirectory, char *argv)
{
    int pid;

    pid = fork();

    switch(pid)
    {
        case -1:
            fprintf(stderr, "extract: Failed to fork()");
            exit(EXIT_FAILURE);
            break;

        case 0:
            
            printf("argv: %s\n TempDir %s\n",argv,TempDirectory);
            execl("/bin/tar","tar","-xvpf", argv, "-C", TempDirectory, NULL);
            break;

        default:
        {
            int child;
            int status;

            child = wait(&status);

            printf("Child %i Exited with status %i\n", child, WEXITSTATUS(status));
            break;
        }

    }

}

//decompresses and empties contents of tar files into the temporary directories//

void extract(int n,char **TempDirectories, char **argv)
{
    for(int i = 0; i<n; i++)
    {
        printf("Passing %s and %s\n", TempDirectories[i], argv[i+1]);
        ExtractTo(TempDirectories[i], argv[i+1]);

    }
}

