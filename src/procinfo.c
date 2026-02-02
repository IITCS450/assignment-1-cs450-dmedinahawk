#include <common.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
static void usage(const char *a){fprintf(stderr,"Usage: %s <pid>\n",a); exit(1);}
static int isnum(const char*s){for(;*s;s++) if(!isdigit(*s)) return 0; return 1;}
int main(int c,char**v){
 if(c!=2||!isnum(v[1])) usage(v[0]);
 

//<pid>
char path[256];
snprintf(path, sizeof(path), "/proc/%s/stat", v[1]);

//open <pid>
FILE *f = fopen(path, "r");
if (!f) {
perror(path);
return 1;
}

//if successful, close and continue
fclose(f);
return 0;
}
