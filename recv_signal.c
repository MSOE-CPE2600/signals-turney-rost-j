/**
 * @file recv_signal.c
 * @brief Program that registers a SIGUSR1 handler using sigaction.
 *        The handler retrieves and prints the integer value sent via sigqueue().
 *
 * Modified by: Jesse Rost <rostj@msoe.edu>
 *
 * Brief summary of program:
 * - Registers a handler for SIGUSR1 using sigaction.
 * - Uses SA_SIGINFO to access the siginfo_t struct and retrieve sival_int.
 * - Waits indefinitely for incoming signals.
 * - When a signal is received, prints the integer value that was sent.
 *
 * Compile with:
 *     gcc -Wall -Wextra recv_signal.c -o recv_signal
 *
 * Run this program first, note the PID, then run send_signal with that PID:
 *     ./recv_signal
 *     ./send_signal <pid>
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// Handler for SIGUSR1 using siginfo_t
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
    sa.sa_flags = SA_SIGINFO; // Required for accessing si_value

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Receiver process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    // Wait indefinitely for incoming signals
    while (1)
    {
        pause();
    }

    return 0;
}
