//Created by RobertVoropaev
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

int main (int argc, char * argv[]) {
    int total_line = 0, total_word = 0, total_char = 0;
    if(argc > 1){
        for(int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "Can not open file %s\n", argv[i]);
            } else {
                int count_line = 0, count_word = 0, count_char = 0;

                char *buffer = (char *) malloc(MAX_SIZE);
                if(buffer == NULL){
                    fprintf(stderr, "Can not allocate memory");
                    exit(1);
                }

                int is_first_space = 0;
                while (fgets(buffer, MAX_SIZE, file) != NULL) {
                    count_line++;
                    for (int i = 0; i < strlen(buffer); i++) {
                        count_char++;
                        char ch = buffer[i];
                        if (isspace(ch)) {
                            if (is_first_space == 0) {
                                count_word++;
                                is_first_space = 1;
                            }
                        } else {
                            is_first_space = 0;
                        }
                    }
                    if (is_first_space == 0) {
                        count_word++;
                    }
                }

                printf("%d %d %d %s\n", count_line, count_word, count_char, argv[i]);

                if(argc > 2){
                    total_line += count_line, total_word += count_word, total_char = count_char;
                }

                free(buffer);
            }
            fclose(file);
        }
    } else {
        FILE *file = stdin;
        int count_line = 0, count_word = 0, count_char = 0;

        char *buffer = (char *) malloc(MAX_SIZE);
        if(buffer == NULL){
            fprintf(stderr, "Can not allocate memory");
            exit(1);
        }

        int is_first_space = 0;
        while (fgets(buffer, MAX_SIZE, file) != NULL) {
            count_line++;
            for (int i = 0; i < strlen(buffer); i++) {
                count_char++;
                char ch = buffer[i];
                if (isspace(ch)) {
                    if (is_first_space == 0) {
                        count_word++;
                        is_first_space = 1;
                    }
                } else {
                    is_first_space = 0;
                }
            }
            if (is_first_space == 0) {
                count_word++;
            }

            printf("%d %d %d\n", count_line, count_word, count_char);
        }
        free(buffer);
    }
    
    if(argc > 2) {
        printf("%d %d %d total\n", total_line, total_word, total_char);
    }
    return 0;
}
