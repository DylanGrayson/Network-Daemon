#include "daemon.h"

void sig_handler(int signo);

int main(int argc, char* argv[]) {
    // init daemon
    daemon_init();

    // loop forever
    int sleeping =0;
    while (1){
        sleeping += 5;
        // sleep for a while 
        sleep(5);
        // log stuff to syslog
        syslog(LOG_NOTICE, "Sleeping for %d", sleeping);
        // try to catch a signal
        if (signal(SIGUSR1, sig_handler) == SIG_ERR)
            printf("\ncan't catch SIGUSR1\n");
    }
    return EXIT_SUCCESS;
}

// signal handler
void sig_handler(int signo){
    // if the signal matches, kill
    if (signo == SIGUSR1)
        daemon_exit();
}
