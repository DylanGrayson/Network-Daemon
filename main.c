/* 
This submission is for the following people:
    Conner Swann
    Dylan Grayson
    Brandon Paree
*/


#include "daemon.h"

#define SERVER_ADDR 0
#define PORT 23001

void sig_handler(int signo);
void connection_handler(int * connection);

int main(int argc, char* argv[]) {
    // init daemon
    daemon_init();

	struct sockaddr_in client_address, server_address;
	int client_socket, connected, n, rc;
	socklen_t sin_size;
	
	bzero(&server_address, sizeof(server_address));
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);

    /* Thread Stuff */
    //create, initialize, and set the thread attribute
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_t threads[100];


    syslog(LOG_NOTICE, "Matt Daemon: Okay, setting myself up.");
	if(bind(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
		perror("error connecting\n");
		exit(EXIT_FAILURE);
	}
	
	listen(client_socket, 5);

    // loop forever
    int threadct = 0;
    while (1){
		sin_size = sizeof(client_address);
        // wait for connections
		connected = accept(client_socket, (struct sockaddr *)&client_address, &sin_size);
		if (connected < 0) 
          perror("ERROR on accept");

        syslog(LOG_NOTICE, "Matt Daemon: Forking a thread for the new connection");
        rc = pthread_create(&threads[threadct++], &attr, (void *)connection_handler, (int *)&connected);
        if(rc){
            syslog(LOG_NOTICE, "ERROR; return code from pthread_create() is %d\n", rc);
        }
		
        if (signal(SIGUSR1, sig_handler) == SIG_ERR)
            syslog(LOG_NOTICE, "\ncan't catch SIGUSR1\n");
    }
    close(client_socket);
    return EXIT_SUCCESS;
}

// connection handler
void connection_handler(int * connection){
    char buffer[256];
    int n;
    syslog(LOG_NOTICE, "Entered new connection_handler thread.");
    while(1) {
        //syslog(LOG_NOTICE, "Zeroing Buffer.");
        //bzero(buffer, 256);
        syslog(LOG_NOTICE, "Reading from socket.");
        n = read(*connection, buffer, 255);

        if (n < 0)
            perror("ERROR reading from socket");
        if(buffer[0] == 'q') {
            syslog(LOG_NOTICE, "Recieved 'q' from client, killing thread");
            break;
        }

        n = write(*connection, buffer, 18);
    }
    close(*connection);
}

// signal handler
void sig_handler(int signo){
    // if the signal matches, kill
    if (signo == SIGUSR1)
        daemon_exit();
}
