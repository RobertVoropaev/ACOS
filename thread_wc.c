#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_SIZE 255

typedef struct {
    int count_line;
    int count_word;
    int count_char;
} counter;

int main (int argc, char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    int N = atoi(argv[2]);

    char **text = (char**) malloc(MAX_SIZE * sizeof(char*));
    if(text == NULL){
        perror("Allocate error");
        exit(1);
    }

    char *buffer = (char*) malloc(MAX_SIZE);
    if(buffer == NULL){
        perror("Allocate error");
        exit(2);
    }

    int count_line = 0;
    while (fgets(buffer, MAX_SIZE, file) != NULL) {
        text[count_line++] = buffer;
        buffer = (char*) malloc(MAX_SIZE);
    }
    int for_one_thread = count_line / N;

    counter final;
    final.count_line = final.count_word = final.count_char = 0;

    for(int i = 0; i < N; i++){
        int fd[2];
        pipe(fd);
        char *buffer;

        int res = fork();
        if(res == 0){
            counter local;
            local.count_line = local.count_word = local.count_char = 0;

            int is_first_space = 0;
            for(int j = i * for_one_thread; j <= for_one_thread *(i + 1) - 1; j++) {
                buffer = text[j];

                if(buffer != NULL) {
                    local.count_line++;
                    for (int k = 0; k < strlen(buffer); k++) {
                        char ch = buffer[k];

                        local.count_char++;
                        if (isspace(ch)) {
                            if (is_first_space == 0) {
                                local.count_word++;
                                is_first_space = 1;
                            }
                        } else {
                            is_first_space = 0;
                        }
                    }
                }
                if (is_first_space == 0) {
                    local.count_word++;
                }
            }

            write(fd[1], &local, sizeof(counter));

            return 0;
        } else if(res > 0){
            int status;
            wait(&status);

            counter local;
            read(fd[0], &local, sizeof(counter));

            final.count_line += local.count_line;
            final.count_char += local.count_char;
            final.count_word += local.count_word;

            close(fd[0]);
            close(fd[1]);
        }
    }

    printf("%d %d %d total\n", final.count_line, final.count_word, final.count_char);

    free(text);
    free(buffer);
    close(file);
    return 0;
}
