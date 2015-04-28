/* 
This submission is for the following people:
    Conner Swann
    Dylan Grayson
    Brandon Paree
*/


#include "daemon.h"

#define PORT 23001
#define BANK_SIZE 1000

typedef struct answer {
	int in;
	int out;
} Answer;

typedef struct data_param {
	int connection;
	int len;
	pthread_mutex_t * mutex;
	struct answer * master_list;
} DataParam;


int threeAHelper(int num, DataParam * data);
int threeAplusOne(int num, int count, DataParam * data);
void sig_handler(int signo);
void connection_handler(void * data);

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
    //build our data parameter struct to be the master
    DataParam data;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    data.mutex = &mutex;
    Answer * answer_bank = malloc(sizeof(Answer) * BANK_SIZE);
    data.master_list = answer_bank;
    data.len = 0;
    while (1){
		struct sockaddr_in client_address;
		sin_size = sizeof(client_address);
        // wait for connections
		connected = accept(client_socket, (struct sockaddr *)&client_address, &sin_size);
		if (connected < 0) 
          perror("ERROR on accept");
		data.connection = connected;
        syslog(LOG_NOTICE, "Matt Daemon: Forking a thread for the new connection");
        //pass each thread the address of data
        rc = pthread_create(&threads[threadct++], &attr, (void *)connection_handler, (void *)&data);
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
void connection_handler(void * data){
    char buffer[256];
    int n;
	DataParam * dp;
	dp = (DataParam*)data;
    int con = (*dp).connection;
    syslog(LOG_NOTICE, "Entered new connection_handler thread.");
    while(1) {
        //syslog(LOG_NOTICE, "Zeroing Buffer.");
        bzero(buffer, 256);
        syslog(LOG_NOTICE, "Reading From Socket. %d", con);
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
			//get three a plus 1 answer and put it in debuf
			sprintf(debuf, "%d", threeAHelper(num, dp));
		}
		n = write(con, debuf, 18);
    }
    close(con);
    pthread_exit(NULL);
}

int threeAHelper(int num, DataParam* data) {
	//run algorithm and get answer in ans
	int ans = threeAplusOne(num, 0, data);
	int i;
	//initialize mutex
	pthread_mutex_t * mutex = (*data).mutex;
	//see if answer already exists in the answer bank
	for (i = 0; i < (*data).len; i++){
		pthread_mutex_lock(mutex);
		if ((*((*data).master_list + i)).in == num){
			pthread_mutex_unlock(mutex);
			return ans;
		}
		pthread_mutex_unlock(mutex);
	}
	//otherwise add it
	pthread_mutex_lock(mutex);
	(*((*data).master_list + i)).in = num;
	(*((*data).master_list + i)).out = ans;
	(*data).len += 1;
	pthread_mutex_unlock(mutex);
	return ans;
}

int threeAplusOne(int num, int count, DataParam* data) {
	if (num == 1) {
		//base case
		return count;
	}
	//check if current num is in answer bank
	int i;
	pthread_mutex_t * mutex = (*data).mutex;
	for (i = 0; i < (*data).len; i++){
		pthread_mutex_lock(mutex);
		if ((*((*data).master_list + i)).in == num){
			//if so: use that answer + count
			int ans = (*((*data).master_list + i)).out;
			syslog(LOG_NOTICE, "Fetched the answer %d for %d", ans, num);
			pthread_mutex_unlock(mutex);
			return ans + count;
		}
		pthread_mutex_unlock(mutex);
	}
	if (num % 2 == 0) {
		return threeAplusOne(num / 2, count + 1, data);
	}
	else {
		return threeAplusOne((3 * num) + 1, count + 1, data);
	}
}

// signal handler
void sig_handler(int signo){
    // if the signal matches, kill
    if (signo == SIGUSR1)
        daemon_exit();
}
