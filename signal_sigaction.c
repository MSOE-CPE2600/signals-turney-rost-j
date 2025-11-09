/**
 * @file        : signal_sigaction.c
 * @brief       : Installs a SIGUSR1 handler using sigaction and prints sender's PID.
 *
 * Details      :
 * - Uses SA_SIGINFO to access extended info (siginfo_t).
 * - Prints the sender PID when SIGUSR1 is received.
 * - Waits indefinitely for incoming signals.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra signal_sigaction.c -o signal_sigaction
 * Usage        : ./signal_sigaction
 *
 * Algorithm
 *  - Configure struct sigaction with SA_SIGINFO.
 *  - Register handler for SIGUSR1.
 *  - Pause forever printing sender PID upon receipt.
 *
 * To send SIGUSR1 to this process from another terminal:
 *      kill -USR1 <pid>
 */

/* This makes <signal.h> reveal extra types and functions
   other than the original C standard. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

/* Correct signature for SA_SIGINFO handler */
void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    (void)signum;
    (void)context; /* suppress unused variable warning */
    printf("Received SIGUSR1 from process with PID: %d\n", info->si_pid);
}

int main(void) {
    struct sigaction sa;

    /* Zero out the sigaction struct */
    memset(&sa, 0, sizeof(sa));

    /* Assign the handler function */
    sa.sa_sigaction = handle_sigusr1;

    /* Tell sigaction to use sa_sigaction instead of sa_handler */
    sa.sa_flags = SA_SIGINFO;

    /* Register the handler for SIGUSR1 */
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    /* Display the process ID so you can send the signal */
    printf("Process running with PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    /* Wait forever for signals */
    while (1) {
        pause(); /* Suspend until signal arrives */
    }

    return 0;
}
