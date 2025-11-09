/**
 * @file        : signal_alarm.c
 * @brief       : Program that schedules an alarm to send SIGALRM after 5 seconds.
 *
 * Details      :
 * - Installs a handler for SIGALRM using signal().
 * - Schedules an alarm to fire after 5 seconds.
 * - Prints a message when SIGALRM is received, then continues waiting.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Signals Lab
 * Modified by  : Jesse Rost <rostj@msoe.edu>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra signal_alarm.c -o signal_alarm
 * Usage        : ./signal_alarm
 *
 * Algorithm
 *  - Register SIGALRM handler.
 *  - Start a 5-second alarm.
 *  - Pause in a loop waiting for signals.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Signal handler for SIGALRM */
void handle_alarm(int signum) {
    /* tells which signal arrived if needed */
    (void)signum;
    printf("Received SIGALRM signal! Alarm went off after 5 seconds.\n");
}

int main(void) {
    /* Register the handler for SIGALRM
       tells the OS to run handle_alarm() whenever SIGALRM is sent. */
    signal(SIGALRM, handle_alarm);

    /* Schedule the alarm for 5 seconds */
    alarm(5);

    printf("Alarm set for 5 seconds. Waiting...\n");

    /* Keep the program alive long enough for the alarm to trigger */
    while (1) {
        pause(); /* Wait for a signal */
    }

    return 0;
}
