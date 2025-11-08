/**
 * @file signal_alarm.c
 * @brief Program that schedules an alarm to send SIGALRM after 5 seconds
 */

/**
 * Modified by: Jesse Rost <rostj@msoe.edu>
 * 
 * Brief summary of modifications:
 * - Added a signal handler for SIGALRM.
 * - Scheduled an alarm to go off after 5 seconds.
 * - Program prints a message when SIGALRM is received.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGALRM
void handle_alarm(int signum) {
    printf("Received SIGALRM signal! Alarm went off after 5 seconds.\n");
}

int main(void) {
    // Register the handler for SIGALRM
    // tells the OS to run handle_alarm() whenever SIGALRM is sent.
    signal(SIGALRM, handle_alarm);

    // Schedule the alarm for 5 seconds
    alarm(5);

    printf("Alarm set for 5 seconds. Waiting...\n");

    // Keep the program alive long enough for the alarm to trigger
    while (1) {
        pause(); // Wait for a signal
    }

    return 0;
}
