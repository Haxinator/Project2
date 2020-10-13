#include "mergetars.h"


//The indexes of two files are passed to isBestDup and the best dup is found//
//returns true if first file is best dup//
bool isBestDup(int i, int ii, FILES* Files)
{
    //variable defintions for file 1//
    char PathName1[MAXPATHLEN];
    sprintf(PathName1, "%s/%s", Files[i].subPath, Files[i].name);
    int Arg1 = Files[i].Arg;
    int mtime1 = Files[i].modTime;
    int size1 = Files[i].size;

    //variable definitions for file 2
    char PathName2[MAXPATHLEN];
    sprintf(PathName2, "%s/%s", Files[ii].subPath, Files[ii].name);
    int Arg2 = Files[ii].Arg;
    int mtime2 = Files[ii].modTime;
    int size2 = Files[ii].size;

    printf("File1: %s\n", PathName1);
    printf("File2: %s\n", PathName2);

    //compare names//
    if(strcmp(PathName1,PathName2))
    {
        //different files//
        //first file is unique//
        return true;

    }else if(!(mtime1==mtime2)){
        //compare time//
        if(mtime1>mtime2)
        {
            //file1 is more recent//
            return true;

        } else{
            //file2 is more recent//
            return false;
        }

    } else if(!(size1==size2)){
        //compare size//
        if(size1>size2)
        {
            //file 1 larger//
            return true;
        
        } else {
            //file 2 larger//
            return false;
        }
        return false;

    } else if(Arg1>Arg2){
        //compare Args//

        //file1 is last arg//
        return true;
    //else statment as there will never be a case where two files are the same
    //and if there is then it doesn't matter what file we copy//
    } else {
        //file2 is last arg//
        return false;
    }
}

//inOutput checks if PathName1 is already in the Output, if it is, it already
//has been compared//

//returns true if in output//
bool inOutput(int SizeO, char* PathName1, int *OutputIndex, FILES* Files)
{
    for(int i=0; i<SizeO; i++)
    {
        //definitons for ease of reading
        char PathName2[MAXPATHLEN];
        int O_Index = OutputIndex[i];
        sprintf(PathName2,"%s/%s", Files[O_Index].subPath, Files[O_Index].name);

        //are they the same?//
        if(!strcmp(PathName1, PathName2))
        {
            //If they are then PathName1 has already been compared//
            printf("They are the same %s %s\n", PathName1, PathName2);
            return true;
        }
            printf("They are NOT the same %s %s\n", PathName1, PathName2);
    }

    printf("%s has no match\n", PathName1);
    //if you get here it must be false//
    return false;
}

//compares all files and finds the best duplicate of file//
//The index of that file in our structure is stored in OutputIndex//
int FindBestDup(int *size, FILES *Files, int **OutputIndex)
{
    int SizeO = 0;
    int O_Index;

    for(int i=0; i<(*size); i++)
    {

        char PathName[MAXPATHLEN];
        //create awesome pathname to compare//
        sprintf(PathName, "%s/%s", Files[i].subPath, Files[i].name);
        printf("%i: Comparing %s\n", i, PathName);

        //if size is zero then there is nothing in output index/
        if(SizeO>-1 && inOutput(SizeO, PathName,*OutputIndex, Files))
        {
            //if its already in the Output skip comparion
            continue;
        }

        //if conditions fail, that means our file hasn't been compared//
        //add 1 to the total size of output//
        //put here//

        //the zeros are used to deallocate the pointer//
        SizeO++;
        *OutputIndex = realloc(*OutputIndex, SizeO*sizeof(**OutputIndex));
        OutputIndex[0][i]= i;
        int Index = SizeO-1;

        //check if unique file is last element, if so add to output//
        if(i == (*size)-1)
        {

            printf("Adding last unique file %i", i);            
            OutputIndex[0][Index] = i;

          //continue loop, which will end the loop//
            continue;
        }
        //default output is the first file//
        O_Index = i;

        //start loop after current element we're looking at//
        for(int ii = i+1; ii<(*size); ii++)
        {
            //if first file isn't the best dup//
            if(!isBestDup(O_Index, ii, Files))
            {
                //set output to second file//
                O_Index = ii;
            }
        }
        printf("added %i to the output\n", O_Index);
        OutputIndex[0][Index]=O_Index;
    
    }

    return SizeO;
}
