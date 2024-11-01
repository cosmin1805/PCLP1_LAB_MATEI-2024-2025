CC = gcc
CFLAGS = -Wall -Wextra -std=c11
MATH_LIB = -lm

# Numele executabilelor
EXECS = ex1_a ex1_b ex1_c ex2 ex3 ex4 ex5 ex6 ex7 ex8

# Regula implicită pentru a compila toate executabilele
all: $(EXECS)

# Reguli pentru fiecare executabil
ex1_a: ex1_a.c
	$(CC) $(CFLAGS) -o ex1_a ex1_a.c $(MATH_LIB)

ex1_b: ex1_b.c
	$(CC) $(CFLAGS) -o ex1_b ex1_b.c

ex1_c: ex1_c.c
	$(CC) $(CFLAGS) -o ex1_c ex1_c.c

ex2: ex2.c
	$(CC) $(CFLAGS) -o ex2 ex2.c

ex3: ex3.c
	$(CC) $(CFLAGS) -o ex3 ex3.c

ex4: ex4.c
	$(CC) $(CFLAGS) -o ex4 ex4.c

ex5: ex5.c
	$(CC) $(CFLAGS) -o ex5 ex5.c

ex6: ex6.c
	$(CC) $(CFLAGS) -o ex6 ex6.c

ex7: ex7.c
	$(CC) $(CFLAGS) -o ex7 ex7.c

ex8: ex8.c
	$(CC) $(CFLAGS) -o ex8 ex8.c

# Reguli pentru a rula fiecare executabil
run_ex1_a: ex1_a
	./ex1_a

run_ex1_b: ex1_b
	./ex1_b

run_ex1_c: ex1_c
	./ex1_c

run_ex2: ex2
	./ex2

run_ex3: ex3
	./ex3

run_ex4: ex4
	./ex4

run_ex5: ex5
	./ex5

run_ex6: ex6
	./ex6

run_ex7: ex7
	./ex7

run_ex8: ex8
	./ex8

# Regula pentru a curăța fișierele generate
clean:
	rm -f $(EXECS)

# Reguli pentru a rula testele
run_test_problema2_test1: ex2
	./ex2 < tests/problema2/test1/input.txt

run_test_problema2_test2: ex2
	./ex2 < tests/problema2/test2/input.txt

run_test_problema3_test1: ex3
	./ex3 < tests/problema3/test1/input.txt

run_test_problema3_test2: ex3
	./ex3 < tests/problema3/test2/input.txt

run_test_problema3_test3: ex3
	./ex3 < tests/problema3/test3/input.txt

run_test_problema4_test1: ex4
	./ex4 < tests/problema4/test1/input.txt

run_test_problema5_test1: ex5
	./ex5 < tests/problema5/test1/input.txt

run_test_problema6_test1: ex6
	./ex6 < tests/problema6/test1/input.txt

run_test_problema8_test2: ex8
	./ex8 < tests/problema8/test2/input.txt