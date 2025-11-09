/**
 * @file        : research.c
 * @brief       : Demonstrates example usage of basic signal-related system calls.
 *
 * Details      :
 * - Example of using `kill()` to send a signal to another process.
 * - Example of using `raise()` to send a signal to the current process.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra research.c -o research
 * Usage        : ./research
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
    // Example of sending SIGTERM to another process using kill()
    pid_t pid = 1234;  // Replace this with an actual process ID if testing
    printf("Sending SIGTERM to process %d using kill().\n", pid);
    // kill(pid, SIGTERM);  // Uncomment to actually send the signal

    // Example of sending SIGINT to this process using raise()
    printf("Sending SIGINT to myself using raise().\n");
    raise(SIGINT);  // Sends SIGINT to the current process

    return 0;
}
