
//welcome to the main headerfile

//include these bad boys in our files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <dirent.h>
#include <sys/param.h>
//add any #define//


//add function declartions//
extern void createdir(int, char**);
extern void clean(int, char**);
extern void extract(char* TempDirectories,char** argv, int numbOfTars);

//add any global variables//

typedef struct{
	char *name;
	char *path;
	int modTime;
	int size;
	bool isLastTarArg;
} FILES;

