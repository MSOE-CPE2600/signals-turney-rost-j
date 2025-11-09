/**
 * @file        : recv_signal.c
 * @brief       : Registers a SIGUSR1 handler using sigaction; prints sival_int payload.
 *
 * Details      :
 * - Uses SA_SIGINFO to access the siginfo_t struct (si_value.sival_int).
 * - Waits indefinitely for SIGUSR1.
 * - Prints the integer value sent via sigqueue() by the sender.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra recv_signal.c -o recv_signal
 * Usage        : ./recv_signal
 *
 * Algorithm
 *  - Configure struct sigaction with SA_SIGINFO.
 *  - Register handler for SIGUSR1.
 *  - Pause forever, printing sival_int when received.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

/* Handler for SIGUSR1 using siginfo_t */
void handle_sigusr1(int signum, siginfo_t *info, void *context)
{
    (void)signum;
    (void)context;
    printf("Received SIGUSR1 with value: %d\n", info->si_value.sival_int);
}

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_sigaction = handle_sigusr1;
    sa.sa_flags = SA_SIGINFO; /* Required for accessing si_value */

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Receiver process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    /* Wait indefinitely for incoming signals */
    while (1)
    {
        pause();
    }

    return 0;
}
