# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11

# Executable targets
TARGETS = signal_alarm signal_handler signal_segfault signal_sigaction recv_signal send_signal serve_tennis recv_tennis

# Default build rule
all: $(TARGETS)

# -------------------------------
# Individual build rules
# -------------------------------
signal_alarm: signal_alarm.c
	$(CC) $(CFLAGS) -o $@ $<

signal_handler: signal_handler.c
	$(CC) $(CFLAGS) -o $@ $<

signal_segfault: signal_segfault.c
	$(CC) $(CFLAGS) -o $@ $<

signal_sigaction: signal_sigaction.c
	$(CC) $(CFLAGS) -o $@ $<

recv_signal: recv_signal.c
	$(CC) $(CFLAGS) -o $@ $<

send_signal: send_signal.c
	$(CC) $(CFLAGS) -o $@ $<

# -------------------------------
# Extra Credit – Signal Tennis
# -------------------------------
serve_tennis: serve_tennis.c
	$(CC) $(CFLAGS) -o $@ $<

recv_tennis: recv_tennis.c
	$(CC) $(CFLAGS) -o $@ $<

# -------------------------------
# Convenience run targets
# -------------------------------
run-alarm: signal_alarm
	./signal_alarm

run-handler: signal_handler
	./signal_handler

run-segfault: signal_segfault
	./signal_segfault

run-sigaction: signal_sigaction
	./signal_sigaction

run-recv: recv_signal
	./recv_signal

run-send: send_signal
	@echo "Usage: make run-send PID=<receiver_pid>"
	@if [ -n "$$PID" ]; then ./send_signal $$PID; fi

run-tennis:
	@echo "🏓 To play Signal Tennis:"
	@echo "  1. Run ./recv_tennis in one terminal."
	@echo "  2. Run ./serve_tennis <receiver_pid> in another terminal."
	@echo

# -------------------------------
# Cleanup
# -------------------------------
clean:
	rm -f $(TARGETS)
	@echo "Cleaned up all compiled binaries."