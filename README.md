## Project Description
A command line utility for CITS2002 that merges the contents of two or more tar files into a single tar file, if two tar files contain the same file, it uses the most recent file. 
Two Files are considered the same if they have the same relative (relative to the tar file) pathname.

For determining which file is most recent the following rules are used:
- The file with the most recent modification time is considered the most recent version.
- If two files have the same modification time, then the larger file is considered most recent.
- Otherwise the last file mentioned on the command line is selected.

## How to Use 
Invoke the program using the command line, with the pathnames of the tars you want to merge as arguments. The final argument is the pathname of output tar file.


```> ./mergetars input_tarfile1 [input_tarfile2 ...] output_tarfile```
