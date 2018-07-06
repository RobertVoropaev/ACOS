//Created by RobertVoropaev
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int main (int argc, char * argv[]) {
    if(argc > 1) {
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "Cannot open file %s\n", argv[i]);
            } else {
                char *buffer = (char *) malloc(MAX_SIZE);
                if(buffer == NULL){
                    fprintf(stderr, "Can not allocate memory");
                    exit(1);
                }
                
                int count_line = 0;
                while (fgets(buffer, MAX_SIZE, file) != NULL) {
                    count_line++;
                }
                fclose(file);

                file = fopen(argv[i], "r");
                if (file == NULL) {
                    fprintf(stderr, "Can not open file %s\n", argv[i]);
                } else {
                    if (argc > 2) {
                        printf("%s\n", argv[i]);
                    }
                    int start = count_line - 10;
                    if (start < 0) {
                        start = 0;
                    }
                    for (int i = 0; i < start; i++) {
                        fgets(buffer, MAX_SIZE, file);
                    }
                    for (int i = start; i < count_line; i++) {
                        fgets(buffer, MAX_SIZE, file);
                        printf("%s", buffer);
                    }
                    printf("\n");
                }
                
                free(buffer);
                fclose(file);
            }
        }
    } else {
        FILE *file = stdin;

        char *buffer = (char *) malloc(MAX_SIZE);
        if(buffer == NULL){
            fprintf(stderr, "Can not allocate memory");
            exit(1);
        }

        while(fgets(buffer, MAX_SIZE, file) != NULL){
            printf("%s\n", buffer);
        }

        free(buffer);
        fclose(file);
    }
    return 0;
}
