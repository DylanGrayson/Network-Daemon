#include "daemon.h"

void daemon_init(void) {
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
		// printf("process_id of child process %d \n", process_id);
  //       printf("Killing Parent Process!\n");
		// return success in exit status
		//exit(0);
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
<<<<<<< HEAD
    
=======
	// Open a log file in write mode.
	//fp = fopen ("Log.txt", "w+");
	while (1){
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		syslog(LOG_NOTICE, "Matt Daemon, reporting for duty");
		//fprintf(fp, "Logging info...\n");
		//fflush(fp);
		// Implement and call some function that does core work for this daemon.
	}
>>>>>>> 0abb00f89e908e81a32b98ead9feab63c5e25304
	//closelog();
}
