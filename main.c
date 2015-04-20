#include "daemon.h"

#define SERVER_ADDR 0
#define PORT 23001

void sig_handler(int signo);

int main(int argc, char* argv[]) {
    // init daemon
    daemon_init();

	struct sockaddr_in client_address, server_address;
	int client_socket, connected, n;
	socklen_t sin_size;
	char buffer[256];
	
	bzero(&server_address, sizeof(server_address));
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);

	if(bind(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
		perror("error connecting\n");
		exit(EXIT_FAILURE);
	}
	
	listen(client_socket, 5);

    // loop forever
    while (1){
		
		sin_size = sizeof(client_address);
		connected = accept(client_socket, (struct sockaddr *)&client_address, &sin_size);
		if (connected < 0) 
          perror("ERROR on accept");

		bzero(buffer, 256);
		n = read(connected, buffer, 255);
		if (n < 0)
			perror("ERROR reading from socket");
		if(buffer[0] == 'q') {
			break;
		}
		n = write(connected, buffer, 18);
		
        if (signal(SIGUSR1, sig_handler) == SIG_ERR)
            printf("\ncan't catch SIGUSR1\n");
    }
     close(connected);
     close(client_socket);
    return EXIT_SUCCESS;
}

// signal handler
void sig_handler(int signo){
    // if the signal matches, kill
    if (signo == SIGUSR1)
        daemon_exit();
}
