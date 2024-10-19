#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p[2];
    pipe(p);

    int buf = 1;
    if (fork()) {
        write(p[1], &buf, sizeof(int));
        wait(0);

	    int tmp;
        read(p[0], &tmp, sizeof(int));
        printf("%d: received pong\n", getpid());

    } else {
        int tmp;
        read(p[0], &tmp, sizeof(int));
        printf("%d: received ping\n", getpid());

        write(p[1], &tmp, sizeof(int));
    }
    close(p[0]);
    close(p[1]); 
    exit(0);
}