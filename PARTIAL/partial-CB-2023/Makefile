CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Numele executabilelor
EXECS = ex1 ex2

# Regula implicită pentru a compila toate executabilele
all: $(EXECS)

# Reguli pentru fiecare executabil
ex1: ex1.c
	$(CC) $(CFLAGS) -o ex1 ex1.c

ex2: ex2.c
	$(CC) $(CFLAGS) -o ex2 ex2.c

# Reguli pentru a rula fiecare executabil
run_ex1: ex1
	./ex1

run_ex2: ex2
	./ex2

# Curățare
clean:
	rm -f $(EXECS)
