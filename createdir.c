//Defintion needed for mkdtemp//
#define _POSIX_C_SOURCE 200809L

//header//
#include "mergetars.h"

/*Defintions
    -TEMPLATE is the name and path of temp file created
    -SIZE is the number of elements in the char array TEMPLATE
*/
#define TEMPLATE "/tmp/Merge-XXXXXX"
#define SIZE 20

/*createdir
    Creates temporary directories corresponding to the number of tar input
    arguments.
    Notes:
    - "TempDirectories" stores the paths of the directories created
    - "n" is the Number of directories created
*/

void createdir(int n, char** TempDirectories)
{
    //Create n Directories//
    for(int DirCount; DirCount<n; DirCount++)
    {
        char dirName[SIZE];
        
        *TempDirectories = malloc(SIZE*sizeof(char));

        strcpy(dirName, TEMPLATE);
        strcpy(*TempDirectories, mkdtemp(dirName));

        if(*TempDirectories == NULL)
        {
            fprintf(stderr, "Failed to create Temporary Directory\n");
            exit(EXIT_FAILURE);
        }

        //debugging//
        printf("%s\n", dirName);
        printf("Directories created: %i \n", DirCount+1);
  
        TempDirectories++;
    }
    //change address to first element in pointer//
        TempDirectories -= n;
}

