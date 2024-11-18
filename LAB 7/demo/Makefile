CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Numele executabilelor
EXECS = demo_string demo_bitwise_operations

# Regula implicită pentru a compila toate executabilele
all: $(EXECS)

# Reguli pentru fiecare executabil
demo_string: demo_string.c
	$(CC) $(CFLAGS) -o demo_string demo_string.c 

demo_bitwise_operations: demo_bitwise_operations.c
	$(CC) $(CFLAGS) -o demo_bitwise_operations demo_bitwise_operations.c

# Reguli pentru a rula fiecare executabil
run_demo_string: demo_string
	./demo_string

run_demo_bitwise_operations: demo_bitwise_operations
	./demo_bitwise_operations

# Curățare
clean:
	rm -f $(EXECS)
