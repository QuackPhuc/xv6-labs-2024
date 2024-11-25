// user/sysinfotest.c
#include "user.h"
#include "sysinfo.h"
#include "fcntl.h"

int main(void) {
    struct sysinfo info;
    if (sysinfo(&info) < 0) {
        printf("sysinfotest: sysinfo failed\n");
        exit(0);
    }

    printf("Free memory: %d bytes\n", info.freemem);
    printf("Number of active processes: %d\n", info.nproc);
    printf("Load average: %d\n", info.loadavg);

    printf("sysinfotest: OK\n");
    exit(0);
}
