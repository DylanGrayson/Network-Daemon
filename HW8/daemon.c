/* 
This submission is for the following people:
    Conner Swann
    Dylan Grayson
    Brandon Paree
*/

#include "daemon.h"

extern void daemon_init(void) {
	//FILE *fp= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;

	
	// Create child process
	process_id = fork();
	// Indication of fork() failure
	if (process_id < 0){
		printf("fork failed!\n");
		// Return failure in exit status
		exit(1);
	}
	// PARENT PROCESS. Need to kill it.
	if (process_id > 0){
		printf("process_id of child process %d \n", process_id);

	}
	//unmask the file mode
	umask(0);
	//set new session
	sid = setsid();
	if(sid < 0) {
		// Return failure
		exit(1);
	}
	// Change the current working directory to root.
	chdir("/");
	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

extern void daemon_exit(void) {
    // report one last message to the console
    syslog(LOG_NOTICE, "Daemon: Matt Daemon is taking control of this mission.");
    syslog(LOG_NOTICE, "Matthew McConaughey: Oh my god, he opened the airlock...");
    // then die 
    exit(0);
}
