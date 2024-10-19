#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int p[]) __attribute__((noreturn));

void sieve(int p[]) {
    close(p[1]);
    
    int prime;
    if (!read(p[0], &prime, sizeof(prime))) {
        close(p[0]);
        exit(0);
    }

    printf("prime %d\n", prime);

    int rp[2];
    pipe(rp);

    if (!fork()) {
        int num;

        while (read(p[0], &num, sizeof(num)) != 0) {
            if (num % prime != 0) {
                write(rp[1], &num, sizeof(num));
            }
        }
    } else {
        close(p[0]);
        sieve(rp);
    }

    exit(0);
}

int main() {
    int p[2];
    pipe(p);

    int N = 280;
    if (!fork()) {
        for (int i = 2; i <= N; i++) {
            write(p[1], &i, sizeof(i));
        }
        close(p[1]);
        exit(0);
    } else {
        sieve(p);
    }
    exit(0);
}
