CC = gcc
CFLAGS = -Wall -std=c99

all: sjf rr

# Build SJF executable
sjf: SJF_inital.o
	$(CC) SJF_inital.o -o sjf

# Build RR executable
rr: RR_inital.o
	$(CC) RR_inital.o -o rr

# Compile SJF object file
SJF_inital.o: SJF_inital.c
	$(CC) $(CFLAGS) -c SJF_inital.c

# Compile RR object file
RR_inital.o: RR_inital.c
	$(CC) $(CFLAGS) -c RR_inital.c

# Clean command
clean:
	rm -f *.o sjf rr


