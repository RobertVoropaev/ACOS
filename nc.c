#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX 1024

int check_to_exit(char *str){
    return str[0] == 'e' && str[1] == 'x' &&
           str[2] == 'i' && str[3] == 't';
}

int client_socket;
int listener;

void terminate(){
    
    shutdown(client_socket, 2);
    close(client_socket);
    close(listener);

	perror("SIGINT error");
    exit(3);
}

int main (int argc, char * argv[]) {
    signal(SIGINT, terminate);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0){
    	perror("Listener error");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int bind_res = bind(listener, (struct sockaddr *)&addr, sizeof(addr));
    if(bind_res < 0){
    	perror("Bing error");
        exit(2);
    }

    listen(listener, 1);

    char buffer[MAX];
    int recv_size;
    char *message;


    while(1) {
        client_socket = accept(listener, NULL, NULL);
        if (client_socket < 0) {
        	perror("Accept error");
            continue;
        }

        while (1) {
            recv_size = recv(client_socket, buffer, MAX, 0);
            if (recv_size <= 0) {
                shutdown(client_socket, 2);
                break;
            }

            message = (char *) malloc(recv_size + 1);
            strncpy(message, buffer, recv_size);
            printf("%s", message);

            if (check_to_exit(message)) {
                break;
            }
            free(message);
        }

        close(client_socket);
    }
    
    return 0;
}
