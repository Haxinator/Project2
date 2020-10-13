//Needed for strdup//
#define _POSIX_C_SOURCE 200809L


#include "mergetars.h"

/*
When given a directory it reads its contents and the contents of its 
sub directories

Path is the directories we are reading e.g. /tmp/tepfile //

subpath are the paths INSIDE the tmp file e.g. /tmp/tempfile/file1, the sub
path is /file1
this is done to simplfiy the process of remembering the directory structure
of the file (no complex string deconstruction).

fpp is a pointer to an array of files structure//

Arg is which argument the tar file is found in (is this file found in the last input
 argument)//

size is a pointer to an int declared in mergetars.c, if contains the size of
the files array, this allows us to iterate through its contents conviently
and allow us to dynamicall allocate memory to the files array//
*/

void readDirectory(char *Path, char *SubPath, FILES **fpp, int Arg, int *size)
{
    //defintions//
    char NewPath[MAXPATHLEN];
    char NewSubPath[MAXPATHLEN];
    char FullPath[MAXPATHLEN];
    DIR *dirp;
    struct dirent *dp;
    
    dirp = opendir(Path);

    //directory doesn't exist//
    if(dirp == NULL) {
        perror("readDirectory");
        exit(EXIT_FAILURE);
    }

    //read contents of directory while its not NULL//                                                     
    while((dp = readdir(dirp)) != NULL)
    {
        struct stat stat_buffer;  

        //don't read to . and .. at the begining of each directory//
        if(strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0)
        {
            //create file string//
            sprintf(FullPath, "%s/%s", Path, dp->d_name);

            //failed to read file//
            if(stat(FullPath, &stat_buffer) != 0)
            {
                perror("readDirectory");
            }


            //if its a directory create a subdirectory
            //and pass it back through this function//

            if(S_ISDIR(stat_buffer.st_mode))
            {
                //create new path to include subdirectory//
                strcpy(NewPath, Path);
                strcat(NewPath, "/");
                strcat(NewPath, dp->d_name);

                //remember the subdirectory structure//
                strcpy(NewSubPath, SubPath);
                strcat(NewSubPath, "/");
                strcat(NewSubPath, dp->d_name);

                //read contents of subdirectory//
                printf("Entering %s\n",NewPath);
                readDirectory(NewPath,NewSubPath, fpp, Arg, size);

            } else if(S_ISREG(stat_buffer.st_mode)){

                //every time you find a file increment the size of the files
                //array by 1//
//                printf("Old Size: %i\n", *size);
                *size +=1;
//                printf("New Size: %i\n", *size);

                //dynamically allocate +1 memory to the file array//
                *fpp = realloc(*fpp,(*size)*sizeof(**fpp));

                //ease of reading definitions//
                int Index = (*size)-1;
                FILES *Files = *fpp;

                //store file data//
                Files[Index].name=strdup(dp->d_name);                    
                Files[Index].path=strdup(Path);   
                Files[Index].subPath=strdup(SubPath);                 
                Files[Index].modTime = (int)stat_buffer.st_mtime;
                Files[Index].size = (int)stat_buffer.st_size;
                Files[Index].Arg = Arg;

                //debugging//
/*
                printf("Name: %s\n", Files[Index].name);
                printf("Path: %s\n", Files[Index].path);
                printf("SubPath: %s\n", Files[Index].subPath);
                printf("Mod Time: %i\n", Files[Index].modTime);
                printf("size: %i\n", Files[Index].size);
                printf("Arg: %i\n", Files[Index].Arg);
*/
            } else{
                //Error unknown file type, ignore it and//
                //continue loop anyway//
                printf("%s is unknown!\n", FullPath);
            }
            
        }
    }
    closedir(dirp);
}
//n is the number of directories

//size is a pointer to an int that holds the size of the files array

//Tempdirectoires is a pointer to an array of directories

//fp is a pointer to an array of files.


//loop goes through each element in tempdirectories and passes it to ReadDirectories//
//which reads the contents and subcontents of that directory//
void store(int n, int *size, char **TempDirectories, FILES **fp)
{
    //initalize value of size//
    *size = 0;

    //read each temporary directory//
    for(int i=0; i<n; i++)
    {
        printf("directory reading: %s\n", TempDirectories[i]);
        readDirectory(TempDirectories[i],"", fp, i+1, size);
    }

}

