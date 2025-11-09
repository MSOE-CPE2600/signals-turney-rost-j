/**
 * @file        : send_signal.c
 * @brief       : Sends SIGUSR1 along with a random integer value to a target PID.
 *
 * Details      :
 * - Takes the target process PID as a command-line argument.
 * - Seeds PRNG with current time and generates a random int (0–99).
 * - Sends SIGUSR1 with integer payload via sigqueue().
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra send_signal.c -o send_signal
 * Usage        : ./send_signal <pid>
 * Example      : ./send_signal 12345
 *
 * Algorithm
 *  - Parse PID from argv.
 *  - Seed PRNG and generate a random int.
 *  - Populate union sigval and call sigqueue().
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

    /* Convert command-line argument to PID */
    pid_t target_pid = (pid_t)atoi(argv[1]);

    /* Seed random number generator */
    srand((unsigned int)time(NULL));

    /* Generate random integer */
    int random_value = rand() % 100; /* 0–99 range for simplicity */
    printf("Sending SIGUSR1 with value: %d to PID %d\n", random_value, target_pid);

    /* Prepare the union for sigqueue */
    union sigval sig_data;
    sig_data.sival_int = random_value;

    /* Send the signal */
    if (sigqueue(target_pid, SIGUSR1, sig_data) == -1)
    {
        perror("sigqueue");
        return 1;
    }

    printf("Signal sent successfully!\n");
    return 0;
}
