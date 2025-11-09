# Lab Week 10 – Signals Lab  
**Course:** CPE 2600 – Systems Programming  
**Author:** Jesse Rost  
**Date:** 11/10/2025  

---

## Overview
This lab explores UNIX signal handling through a series of small C programs.  
Each demonstrates a different aspect of signals — how they are sent, caught, and handled using both traditional and advanced techniques (`signal`, `sigaction`, `sigqueue`, etc.).  

---

## Programs
| Program | Description |
|----------|-------------|
| **signal_alarm** | Demonstrates the use of `alarm()` and `SIGALRM` to schedule an event. |
| **signal_handler** | Handles `SIGINT` (Ctrl+C) without terminating immediately. |
| **signal_segfault** | Intentionally causes and catches a segmentation fault (`SIGSEGV`). |
| **signal_sigaction** | Installs a `SIGUSR1` handler using `sigaction()` and prints the sender PID. |
| **recv_signal** | Waits for a `SIGUSR1` signal and prints the integer value received. |
| **send_signal** | Sends a `SIGUSR1` signal with an integer value to another process using `sigqueue()`. |

---

## Extra Credit: Signal Tennis
Two programs simulate a tennis rally using signals:
- **recv_tennis.c** — waits for a “serve,” then returns it.
- **serve_tennis.c** — initiates the serve, and both rally signals until 10 volleys are complete.

### How to Play
1. Compile everything:
   ```bash
   make
