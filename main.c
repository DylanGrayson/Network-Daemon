#include "daemon.h"

int main(int argc, char* argv[]) {
    daemon_init();
    int sleeping =0;
    while (1){
        sleeping += 5;
        sleep(5);
        syslog(LOG_NOTICE, "Sleeping for %d", sleeping);
    }
    return EXIT_SUCCESS;
}
