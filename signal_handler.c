/**
 * @file        : signal_handler.c
 * @brief       : Sets a signal handler for SIGINT; handler prints a message and continues.
 *
 * Details      :
 * - Installs a SIGINT handler using signal().
 * - The handler prints a message but does not exit.
 * - The program loops and sleeps, demonstrating continued execution.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra signal_handler.c -o signal_handler
 * Usage        : ./signal_handler
 *
 * Algorithm
 *  - Register SIGINT handler.
 *  - Loop forever printing and sleeping.
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message but does not exit.
 */
void handle_signal(int signum) {
    (void)signum;
    printf("Received a signal (SIGINT)\n");
}

int main(void) {
    /* Register the signal handler for SIGINT (Ctrl+C) */
    signal(SIGINT, handle_signal);

    /* Loop indefinitely */
    while (1) {
        printf("Sleeping...\n");
        sleep(1);
    }

    return 0;
}
