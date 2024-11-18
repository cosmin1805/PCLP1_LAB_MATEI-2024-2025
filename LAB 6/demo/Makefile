CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
MATH_LIB = -lm

# Numele executabilelor
EXECS = demo_pointers demo_pointers_casting demo_pointers_vector demo_malloc

# Regula implicită pentru a compila toate executabilele
all: $(EXECS)

# Reguli pentru fiecare executabil
demo_pointers: demo_pointers.c
	$(CC) $(CFLAGS) -o demo_pointers demo_pointers.c

# Reguli pentru a rula fiecare executabil
run_demo_pointers: demo_pointers
	./demo_pointers

demo_pointers_casting: demo_pointers_casting.c
	$(CC) $(CFLAGS) -o demo_pointers_casting demo_pointers_casting.c

run_demo_pointers_casting: demo_pointers_casting
	./demo_pointers_casting

demo_pointers_vector: demo_pointers_vector.c
	$(CC) $(CFLAGS) -o demo_pointers_vector demo_pointers_vector.c

run_demo_pointers_vector: demo_pointers_vector
	./demo_pointers_vector

demo_malloc: demo_malloc.c
	$(CC) $(CFLAGS) -o demo_malloc demo_malloc.c

run_demo_malloc: demo_malloc
	./demo_malloc

# Regula pentru a curăța fișierele generate
clean:
	rm -f $(EXECS)