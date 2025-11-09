/**
 * @file        : signal_segfault.c
 * @brief       : Program that intentionally causes a segmentation fault (SIGSEGV)
 *                and installs a signal handler to catch it.
 *
 * Details      :
 * - Installs a handler for SIGSEGV using signal().
 * - The handler prints a message when a segmentation fault occurs.
 * - The handler returns without exiting, demonstrating resuming behavior.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra signal_segfault.c -o signal_segfault
 * Usage        : ./signal_segfault
 *
 * Algorithm
 *  - Register SIGSEGV handler.
 *  - Dereference a NULL pointer to trigger SIGSEGV.
 *  - Observe handler print and program behavior.
 */

#include <stdio.h>
#include <signal.h>

/* Handler for segmentation fault */
void handle_sigsegv(int signum) {
    (void)signum;
    printf("Caught SIGSEGV: segmentation fault detected!\n");
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    /* Install the handler for SIGSEGV */
    signal(SIGSEGV, handle_sigsegv);

    /* Declare a null pointer */
    int *i = NULL;

    /* Dereference the null pointer */
    printf("The value of i is: %d\n", *i);

    /* Return to exit the program */
    return 0;
}
