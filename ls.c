//Created by RobertVoropaev
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <memory.h>

#define MAX_SIZE 255

char* get_full_name(char* path, char* name){
    char* full_name = (char*) malloc(MAX_SIZE);
    if(full_name == NULL){
        fprintf(stderr, "Can not allocate memory\n");
        exit(1);
    }
    
    strcpy(full_name, path);
    strcat(full_name, "/");
    strcat(full_name, name);
    return full_name;
}

void print_dir(char* path){
    DIR *dir = opendir(path);
    if(dir == NULL){
        fprintf(stderr, "Can not open dir %s\n", path);
    } else {
        struct dirent *entry = readdir(dir);
        while(entry != NULL){
            if(entry->d_type == 4) {
                char* dir_name = (char*) malloc(MAX_SIZE);
                if(dir_name == NULL){
                    fprintf(stderr, "Can not allocate memory\n");
                    exit(1);
                }
                
                strcpy(dir_name, entry->d_name);
                if (strcmp(dir_name, ".") != 0 && strcmp(dir_name, "..") != 0) {
                    char *full_name = get_full_name(path, dir_name);
                    print_dir(full_name);
                    free(full_name);
                }
            } else {
                char* full_name = get_full_name(path, entry->d_name);
                printf("%s\n", full_name);
                free(full_name);
            }
            entry = readdir(dir);
        }
        
        free(entry);
        closedir(dir);
    }
}

int main (int argc, char * argv[]) {
    char* path = (char*) malloc(MAX_SIZE);
    if(path == NULL){
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }
    
    if (argc < 2) {
        strcpy(path, ".");
    } else {
        strcpy(path, argv[1]);
    }
    print_dir(path);
    free(path);
    return 0;
}
