/**
 * @file send_signal.c
 * @brief Program that sends SIGUSR1 along with a random integer value to a target PID.
 *
 * Modified by: Jesse Rost <rostj@msoe.edu>
 *
 * Brief summary of program:
 * - Takes the target process PID as a command-line argument.
 * - Generates a random integer using rand(), seeded with current time.
 * - Prints the random value before sending.
 * - Sends SIGUSR1 with the integer payload to the receiver using sigqueue().
 *
 * Compile with:
 *     gcc -Wall -Wextra send_signal.c -o send_signal
 *
 * Usage:
 *     ./send_signal <pid>
 * Example:
 *     ./send_signal 12345
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    // Convert command-line argument to PID
    pid_t target_pid = (pid_t)atoi(argv[1]);

    // Seed random number generator
    srand(time(NULL));

    // Generate random integer
    int random_value = rand() % 100; // 0–99 range for simplicity
    printf("Sending SIGUSR1 with value: %d to PID %d\n", random_value, target_pid);

    // Prepare the union for sigqueue
    union sigval sig_data;
    sig_data.sival_int = random_value;

    // Send the signal
    if (sigqueue(target_pid, SIGUSR1, sig_data) == -1)
    {
        perror("sigqueue");
        return 1;
    }

    printf("Signal sent successfully!\n");
    return 0;
}
