#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <omp.h>

#include <syslog.h>
#include "lib/safe/util.h"
#include "lib/modbus/connection.h"

int THREAD_COUNT = 1024; // default thread num


int main(int argc, char *argv[]) {
    menu();
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <modbus-server-ip> [thread-number]\n\n", argv[0]);
        exit(1);
    }
    omp_set_dynamic(0);
    if (argv[2] != NULL)
        THREAD_COUNT = atoi(argv[2]);

    fprintf(stderr, "> start with %d thread\n", THREAD_COUNT);
    omp_set_num_threads(THREAD_COUNT);
    if (VERBOSE)
        syslog(LOG_DEBUG, "total thread -> %d ", omp_get_num_threads());

#pragma omp parallel
    { // start parallel tasks
        get_connection(argv[1]);
    } // end of parallel tasks


    return 0;
}
