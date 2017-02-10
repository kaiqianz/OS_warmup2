#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctype.h> 
#include <dirent.h>
#include <errno.h> 
#include <sys/stat.h>
#include "cs402.h" 
#include "my402list.h" 
 

/* ----------------------- main() ----------------------- */

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc == 2 && strcmp("sort", argv[1]) == 0) {
        fp = stdin;
        parseData(fp);
    }
    else if (argc == 3 && strcmp("sort", argv[1]) == 0) {
        fp = fopen(argv[2], "r");
        if (isDirectory(argv[2])) {
            fprintf(stderr, "Error: Cannot open the derectory\n");
            exit(1);
        }
        if (fp == NULL) {
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            exit(1);
        }
        else {
//            fprintf(stdout, "result1: **********\n");
            parseData(fp);
        }
        fclose(fp);
    }
    else {
        fprintf(stderr, "Error: invalid command format\n");
        exit(1);
    }
    return(0);
}

static int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
