/**
 * @file signal_segfault.c
 * @brief Program that intentionally causes a segmentation fault (SIGSEGV)
 *        and installs a signal handler to catch it.
 */

/**
 * Modified by: Jesse Rost <rostj@msoe.edu>
 * 
 * Brief summary of modifications:
 * - Installed a signal handler for SIGSEGV.
 * - The handler prints a message when a segmentation fault occurs.
 * - The handler returns without exiting, demonstrating what happens
 *   when execution resumes after the fault.
 */

#include <stdio.h>
#include <signal.h>

// Handler for segmentation fault
void handle_sigsegv(int signum) {
    printf("Caught SIGSEGV: segmentation fault detected!\n");
}

int main(int argc, char* argv[]) {
    // Install the handler for SIGSEGV
    signal(SIGSEGV, handle_sigsegv);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}
