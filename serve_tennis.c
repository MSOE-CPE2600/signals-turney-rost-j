/**
 * @file        : serve_tennis.c
 * @brief       : "Signal Tennis" server player — initiates and rallies signals with another process.
 *
 * Details      :
 * - Registers a handler for SIGUSR1 ("the ball").
 * - Serves the first signal with volley count = 1.
 * - Each side randomly delays 1–2 seconds between hits.
 * - Ends the game cleanly after 10 volleys.
 *
 * Course       : CPE 2600 – Systems Programming
 * Section      : 112
 * Assignment   : Extra Credit – Signal Tennis
 * Author       : rostj@msoe.edu <Jesse Rost>
 * Date         : 11/10/25
 *
 * Compile      : gcc -Wall -Wextra serve_tennis.c -o serve_tennis
 * Usage        : ./serve_tennis <receiver_pid>
 *
 * Algorithm
 *  1. Parse the command-line argument to get the opponent’s PID.
 *  2. Install a signal handler for SIGUSR1 using sigaction().
 *  3. Print confirmation of setup (own PID and opponent PID).
 *  4. Wait one second, then “serve” the first volley by sending SIGUSR1
 *     with sival_int = 1 to the opponent process.
 *  5. Enter an infinite pause loop, waiting for incoming volleys handled
 *     by handle_ball().
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/** 
 * @brief This will hold the PID of the receiver process.
 */
static pid_t opponent_pid = 0;

/**
 * @brief Graceful exit handler for SIGUSR2.
 *        Prints message and exits cleanly instead of being killed.
 */
void handle_game_over(int signum)
{
    (void)signum;
    printf("\a[SERVER] Game over! Exiting cleanly.\n");
    exit(0);
}

/**
 * @brief Runs automatically whenever a SIGUSR1 signal arrives.
 *
 * @param signum   The signal number.
 * @param info     Pointer containing info about the signal (sender PID, sent data).
 * @param context  CPU context (unused, but required by function signature).
 */
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

/**
 * @brief Main function: sets up signal handler and starts the game.
 *
 * @param argc Number of command-line arguments.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char *argv[])
{
    // checks if you provided only one argument
    if (argc != 2) {
        // send an error if you forgot the PID
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    // converts the string (user input) to an int using atoi
    opponent_pid = (pid_t)atoi(argv[1]);

    // declares the new sigaction
    struct sigaction sa;
    // clears it with all zeros
    memset(&sa, 0, sizeof(sa));
    // sets handler function to handle_ball
    sa.sa_sigaction = handle_ball;
    // makes sure the handler receives extra info (siginfo_t)
    sa.sa_flags = SA_SIGINFO;

    // whenever process receives SIGUSR1, call sa.sa_sigaction
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // register graceful exit handler for SIGUSR2
    struct sigaction sa_end;
    memset(&sa_end, 0, sizeof(sa_end));
    sa_end.sa_handler = handle_game_over;
    sigaction(SIGUSR2, &sa_end, NULL);

    // confirmation print statement
    printf("[SERVER] Ready. PID: %d | Opponent PID: %d\n", getpid(), opponent_pid);

    // Serve the first volley, wait one second before starting
    sleep(1);
    // creates a container to hold data, needed for sigqueue
    union sigval sv;
    // sets that integer to 1 (first volley)
    sv.sival_int = 1;
    // prints that you’re serving volley #1, \a makes a beep sound
    printf("\a[SERVER] Serving volley #1 to PID %d\n", opponent_pid);
    // sigqueue(target process id, signal type, value(expects union))
    if (sigqueue(opponent_pid, SIGUSR1, sv) == -1) {
        perror("sigqueue");
    }

    // puts the process to sleep until next signal arrives
    while (1) {
        pause();
    }

    return 0;
}
