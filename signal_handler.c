/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Jesse Rost <rostj@msoe.edu>
 * 
 * Brief summary of modifications: 
 * - Removed the exit() call from the SIGINT handler.
 * - The program now continues running after receiving SIGINT.
 * - The process must be forcefully terminated using SIGKILL (cannot be caught or ignored).
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message but does not exit.
 */
void handle_signal() {
    printf("Received a signal (SIGINT)\n");
}

int main() {
    // Register the signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_signal);

    // Loop indefinitely
    while (1) {
        printf("Sleeping...\n");
        sleep(1);
    }

    return 0;
}