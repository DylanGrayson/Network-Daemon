/* 
This submission is for the following people:
    Conner Swann
    Dylan Grayson
    Brandon Paree
*/


#include "daemon.h"

#define PORT 23001

int threeAHelper(int num);
int threeAplusOne(int num, int count);

struct answer {
	int connection;
	int in;
	int out;
};
void sig_handler(int signo);
void connection_handler(int * connection);

int main(int argc, char* argv[]) {
    // init daemon
    daemon_init();

	struct sockaddr_in server_address;
	int client_socket, connected, rc;
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
    //int i;
    //for(i=0; i<69; i++){
    //    syslog(LOG_NOTICE, matt_text[i]);
    //}
	if(bind(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
		perror("error connecting\n");
		exit(EXIT_FAILURE);
	}
	
	listen(client_socket, 5);

    // loop forever
    int threadct = 0;
    
    //struct answer answer_bank[100];
    
    while (1){
		struct sockaddr_in client_address;
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
    int con = *connection;
    syslog(LOG_NOTICE, "Entered new connection_handler thread.");
    while(1) {
        //syslog(LOG_NOTICE, "Zeroing Buffer.");
        bzero(buffer, 256);
        syslog(LOG_NOTICE, "Reading from socket. %d", con);
        n = read(con, buffer, 255);
		int num = atoi(buffer);
        if (n < 0)
            perror("ERROR reading from socket");
        if(buffer[0] == 'q') {
            syslog(LOG_NOTICE, "Recieved 'q' from client, killing thread");
            break;
        }
        char * debuf = buffer;
        if(num <= 0){
			debuf = "Not a Number!";
		}else{
			sprintf(debuf, "%d", threeAHelper(num));
		}
		n = write(con, debuf, 18);
    }
    close(con);
    pthread_exit(NULL);
}

int threeAHelper(int num) {
	int s = threeAplusOne(num, 0);
	return s;
}

int threeAplusOne(int num, int count) {
	if (num == 1) {
		return count;
	}
	else if (num % 2 == 0) {
		return threeAplusOne(num / 2, count + 1);
	}
	else {
		return threeAplusOne((3 * num) + 1, count + 1);
	}
}

// signal handler
void sig_handler(int signo){
    // if the signal matches, kill
    if (signo == SIGUSR1)
        daemon_exit();
}
