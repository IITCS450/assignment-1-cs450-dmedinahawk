#include "common.h"
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
static void usage(const char *a){fprintf(stderr,"Usage: %s <cmd> [args]\n",a); exit(1);}
static double d(struct timespec a, struct timespec b){
 return (b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;}
int main(int c,char**v){
if (c <2) {
    usage(v[0]);
    return 1;

}

struct timespec t0, t1;
if (clock_gettime(CLOCK_MONOTONIC, &t0) != 0) {
    perror("clock_gettime");
    return 1;
}

pid_t pid = fork();
if (pid < 0) {
    perror("fork");
    return 1;
}

if (pid == 0) {
    execvp(v[1], &v[1]);
    perror("execvp");
    exit(27);
}

int status = 0;
if (waitpid(pid, &status, 0) < 0) {
    perror("waitpid");
    return 1;
}
if (clock_gettime(CLOCK_MONOTONIC, &t1) != 0) {
    perror("clock_gettime");
    return 1;
}

double elapsed = d(t0, t1);

if (WIFEXITED(status)) {
    printf("pid=%d exit=%d time=%.6f\n", (int)pid, WEXITSTATUS(status), elapsed);
} else if (WIFSIGNALED(status)) {
    printf("pid=%d signal=%d time=%.6f\n", (int)pid, WTERMSIG(status), elapsed);
} else {
    printf("pid=%d unknown termination time=%.6f\n", (int)pid, status, elapsed);
}