#include "mergetars.h"

//removes temporary directories using "rm -r -v" which removes the directory
//and its contents, and prints what its deleting to the terminal//

//fork needs to be used in order to call execl, as the process that calls
//execl is converted to the process specified in the first argument provided//

void clean(int n, char** TempDirectories)
{
    int pid;

    //creates a process for every directory created//
    //child will turn into "rm" and parent will wait for child//
    for(int i=0; i<n; i++)   
    {
        pid = fork();
        switch(pid)
        {
            //fork failed//
            case -1:
            fprintf(stderr, "clean: fork() failed\n");
            exit(EXIT_FAILURE);
            break;

            //if your child do this//        
            case 0:
            execl("/bin/rm", "/bin/rm","-r","-v", TempDirectories[i], NULL);       
            break;

            //if your parent do that//
            default:
            //makes the print outputs more readable//
            sleep(1);      
            break;
        }
    }

}
