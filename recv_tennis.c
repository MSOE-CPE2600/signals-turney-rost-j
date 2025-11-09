/**
 * @file        : recv_tennis.c
 * @brief       : "Signal Tennis" receiving player — waits for serve and rallies back using signals.
 *
 * Details      :
 * - Waits for SIGUSR1 ("the ball").
 * - When received, prints sender PID and volley count.
 * - Waits 1–2 seconds, then sends the signal back with an incremented volley count.
 * - Ends the game cleanly when volley reaches 10.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Extra Credit – Signal Tennis
 * Author       : rostj@msoe.edu <Jesse Rost>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra recv_tennis.c -o recv_tennis
 * Usage        : ./recv_tennis
 *
 * Algorithm
 *  1. Install a signal handler for SIGUSR1 using sigaction().
 *  2. Wait for the first volley (serve) from the opponent.
 *  3. When received, extract sender PID and volley count.
 *  4. Delay for 1–2 seconds, then increment the volley count.
 *  5. Send SIGUSR1 back to the opponent with the updated value.
 *  6. Continue until volley count reaches 10, then exit cleanly.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// stores the pid of the other player
static pid_t opponent_pid = 0;

/**
 * @brief Graceful exit handler for SIGUSR2.
 *        Prints message and exits cleanly instead of being killed.
 */
void handle_game_over(int signum)
{
    (void)signum;
    printf("\a[RECEIVER] Game over! Exiting cleanly.\n");
    exit(0);
}

// runs automatically whenever SIGUSR1 signal arrives
// all parameters are in place to match the standard function signature of sigaction()
void handle_ball(int signum, siginfo_t *info, void *context)
{
    // tell the compiler that you’re intentionally not using those parameters.
    // this avoids any compile errors
    (void)signum;
    (void)context;

    // reading the sender info and current volley
    // info->si_value.sival_int is the int value sent along with signal (volley count)
    int volley = info->si_value.sival_int;
    // info->si_pid is the PID of the sending process (opponent)
    opponent_pid = info->si_pid;

    // \a is a bell character which makes the terminal beep
    // then it prints the volley number, who was received, and who sent it
    printf("\a[RECEIVER] Received volley #%d from PID %d\n", volley, opponent_pid);

    // check if the game is over, end game after 10 volleys
    if (volley >= 10) {
        printf("[RECEIVER] Game over! Total volleys: %d\n", volley);
        kill(opponent_pid, SIGUSR2);   // send graceful "end" signal
        exit(0);
    }

    // Random delay between 1–2 seconds
    // use xor to combine the time and pid value for a better random value
    srand(time(NULL) ^ getpid());
    // gives a zero or one
    int delay = 1 + rand() % 2;
    // wait for 1–2 seconds
    sleep(delay);

    // Send the signal back with incremented volley count
    // union sigval is a structure that holds an int or pointer
    // you can send with a signal, needed for sending value with sigqueue
    union sigval sv;
    // increment volley count by one
    sv.sival_int = volley + 1;
    // sigqueue sends SIGUSR1 back to opponent with new value
    // sigqueue(target process id, signal type, value(expects union))
    if (sigqueue(opponent_pid, SIGUSR1, sv) == -1) {
        perror("sigqueue"); // print system error if fails
    }
    // otherwise print confirmation 
    printf("\a[RECEIVER] Returned volley #%d to PID %d\n", volley + 1, opponent_pid);
}

int main(void)
{
    // declare the struct that holds the configuration info for signal handler
    struct sigaction sa;
    // fill the entire struct with zeros
    // important because garbage values could make it non-zero
    // or cause undefined behavior when sigaction() tries to read it
    memset(&sa, 0, sizeof(sa));
    // when the signal arrives, call the function to handle the ball
    sa.sa_sigaction = handle_ball;

    // Use the extended handler that takes three arguments (signum, siginfo_t*, and context)
    // instead of the simple one-argument version
    sa.sa_flags = SA_SIGINFO;

    // sigaction(signal, new settings, old handler)
    // returns negative one when failure occurs 
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // register graceful exit handler for SIGUSR2
    struct sigaction sa_end;
    memset(&sa_end, 0, sizeof(sa_end));
    sa_end.sa_handler = handle_game_over;
    sigaction(SIGUSR2, &sa_end, NULL);

    // print updates
    printf("[RECEIVER] Ready. PID: %d\n", getpid());
    printf("[RECEIVER] Waiting for serve...\n");

    // puts process to sleep until next signal arrives
    while (1) {
        pause();
    }

    return 0;
}
