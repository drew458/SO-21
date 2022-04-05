#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define abort(msg) do{printf(msg);exit(1);}while(0)

int main(int argc, char *argv[]){
    char salt[] = "$1$Ynt5vLPQ";
    char target[] = "$1$Ynt5vLPQ$FqmNnL5O9C59equlR12F11";

    char *password, *line=NULL;
    FILE *fp;
    size_t len=0;
    ssize_t read;
    int finish=0, i=0;
    
    fp = fopen(argv[1], "r");
    if (fp == NULL) abort("Input open error\n");

    while ((read = getline(&line, &len, fp)) != -1){
        password = crypt(line, salt);
        while (target[i]!='\0' && password[i]!='\0'){
            if(target[i]==password[i]){
                i++;
            }
            else{
                finish=1;
                break;
            }
        }
        if (finish==0) printf(ANSI_COLOR_GREEN "FOUND!" ANSI_COLOR_RESET "\nKey inserted: %s\nTarget: %s\nOutput: %s\n", line, target, password);
        else printf(ANSI_COLOR_RED "\nNot found\n" ANSI_COLOR_RESET "Key inserted: %sTarget: %s\nOutput: %s\n", line, target, password);
    }
    
    fclose(fp);
    if(line) free(line);

    return 0;
}