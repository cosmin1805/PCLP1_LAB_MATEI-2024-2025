#include <stdio.h>

void print_bits(int num) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main() {
    int a = 5;  // Binary: 0101
    int b = 9;  // Binary: 1001
    int result;

    // Bitwise AND: Performs a logical AND operation on each bit of the operands.
    // Bitwise OR: Performs a logical OR operation on each bit of the operands.
    // Bitwise XOR: Performs a logical XOR operation on each bit of the operands.
    // Bitwise NOT: Inverts all the bits of the operand.
    // Bitwise left shift: Shifts the bits of the operand to the left by the specified number of positions.
    // Bitwise right shift: Shifts the bits of the operand to the right by the specified number of positions.
    // Get the n-th bit: Retrieves the value of the n-th bit of the operand.
    // Set the n-th bit: Sets the n-th bit of the operand to 1.
    // Clear the n-th bit: Sets the n-th bit of the operand to 0.
    // Toggle the n-th bit: Inverts the value of the n-th bit of the operand.

    // Bitwise AND
    result = a & b;
    printf("\nBitwise AND of %d and %d is %d\n", a, b, result);
    printf("a  : ");
    print_bits(a);
    printf("b  : ");
    print_bits(b);
    printf("res: ");
    print_bits(result);

    // Bitwise OR
    result = a | b;
    printf("\nBitwise OR of %d and %d is %d\n", a, b, result);
    printf("a  : ");
    print_bits(a);
    printf("b  : ");
    print_bits(b);
    printf("res: ");
    print_bits(result);

    // Bitwise XOR
    result = a ^ b;
    printf("\nBitwise XOR of %d and %d is %d\n", a, b, result);
    printf("a  : ");
    print_bits(a);
    printf("b  : ");
    print_bits(b);
    printf("res: ");
    print_bits(result);

    // Bitwise NOT
    result = ~a;
    printf("\nBitwise NOT of %d is %d\n", a, result);
    printf("a  : ");
    print_bits(a);
    printf("res: ");
    print_bits(result);

    // Bitwise left shift
    result = a << 1;
    printf("\nBitwise left shift of %d by 1 is %d\n", a, result);
    printf("a  : ");
    print_bits(a);
    printf("res: ");
    print_bits(result);

    // Bitwise right shift
    result = b >> 1;
    printf("\nBitwise right shift of %d by 1 is %d\n", b, result);
    printf("b  : ");
    print_bits(b);
    printf("res: ");
    print_bits(result);

    // get the n bit of a
    int n = 2;
    result = (a >> n) & 1;
    printf("\nBit %d of %d is %d\n", n, a, result);
    printf("a  : ");
    print_bits(a);
    printf("res: ");
    print_bits(result);

    // set n bit of a
    n = 1;
    result = a | (1 << n);
    printf("\nSetting bit %d of %d is %d\n", n, a, result);
    printf("a  : ");
    print_bits(a);
    printf("res: ");
    print_bits(result);

    // clear n bit of a
    n = 2;
    result = a & ~(1 << n);
    printf("\nClearing bit %d of %d is %d\n", n, a, result);
    printf("a  : ");
    print_bits(a);
    printf("res: ");
    print_bits(result);

    // toggle n bit of a
    n = 1;
    result = a ^ (1 << n);
    printf("\nToggling bit %d of %d is %d\n", n, a, result);
    printf("a  : ");
    print_bits(a);
    printf("res: ");
    print_bits(result);

    return 0;
}
