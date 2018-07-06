//Created by RobertVoropaev
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 100

char* sed(char* text, char* old_word, char* new_word){
    char *result = (char *) malloc(MAX_SIZE);
    if(result == NULL){
        fprintf(stderr, "Can not allocate memory\n");
        exit(1);
    }
    
    size_t current_n = 0;
    char *current_char = text;
    char *buffer = NULL;

    char *funstr = strstr(current_char, old_word);
    while (funstr != NULL) {
        current_n = funstr - current_char;

        buffer = (char *) malloc(current_n + 1);
        strncpy(buffer, current_char, current_n);
        strcat(result, buffer);
        strcat(result, new_word);

        current_char = funstr + strlen(old_word);
        funstr = strstr(current_char, old_word);

        free(buffer);
    }
    free(funstr);

    strcat(result, current_char);
    return result;
}

int main (int argc, char * argv[]) {
    char *old_word = argv[1];
    char *new_word = argv[2];
    if(argc > 3) {
        for (int i = 3; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "Cannot open file %s\n", argv[i]);
            } else {
                char *buffer = (char *) malloc(MAX_SIZE);
                char *text = (char *) malloc(MAX_SIZE);
                if(buffer == NULL || text == NULL){
                    fprintf(stderr, "Can not allocate memory\n");
                    exit(1);
                }
                
                while (fgets(buffer, MAX_SIZE, file) != NULL) {
                    strcat(text, buffer);
                }
                free(buffer);
                
                char *result = sed(text, old_word, new_word);
                printf("%s", result);
                
                close(file);
            }
        }
    } else {
        char *text = (char *) malloc(MAX_SIZE);
        fgets(text, MAX_SIZE, stdin);
        
        char *result = sed(text, old_word, new_word);
        printf("%s", result);
        
        free(text);
        free(result);
    }
    return 0;
}
