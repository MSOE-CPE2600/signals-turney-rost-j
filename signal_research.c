#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    // kill example
    pid_t pid = 1234;  // Replace with target process ID
    kill(pid, SIGTERM);  // Send SIGTERM to process 1234
    // raise example
    printf("Sending myself SIGINT\n");
    raise(SIGINT);  // Sends SIGINT to the current process
    return 0;
}