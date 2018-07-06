#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <sys/wait.h>

#define MAX_SIZE 100

int main(int argc, char *argv[]){
    char *arg = (char*) malloc(MAX_SIZE);
    if(arg == NULL){
        fprintf(stderr, "Can not allocate memory");
        exit(1);
    }
    arg[0] = '\0';
    
    for(int i = 1; i < argc; i++){
        int fd[2];
        pipe(fd);
        
        int result = fork();
        if(result == 0){
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            if(strcmp(arg, "") == 0){
                execlp(argv[i], "", (char *) NULL);
            } else {
                execlp(argv[i], "", arg, (char *) NULL);
            }
        } else if (result > 0){
            int status;
            wait(&status);
            
            read(fd[0], arg, MAX_SIZE);
            if(arg[strlen(arg) - 1] == '\n'){
                arg[strlen(arg) - 1] = '\0';
            }
            
            close(fd[1]);
            close(fd[0]);
        }
    }
    printf("%s\n", arg);
    return 0;
}
