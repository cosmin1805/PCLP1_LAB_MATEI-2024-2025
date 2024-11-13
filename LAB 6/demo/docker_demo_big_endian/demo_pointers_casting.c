#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void print_byte_as_binary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
    printf(" ");
}

void print_bytes(void *ptr, size_t size) {
    unsigned char *byte_ptr = (unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        print_byte_as_binary(byte_ptr[i]);
    }
    printf("\n");
}

int main() {
	// Desired fixed start address (can be adjusted as per requirements)
    void *desired_address = (void *)0x10000000;

    // Define the size of the memory region (size of array + extra space for alignment)
    size_t region_size = 4096; // A typical page size on x86 and ARM architectures

    // Allocate memory using mmap with the desired address
    void *mapped_region = mmap(desired_address, region_size,
                               PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
                               -1, 0);

    if (mapped_region == MAP_FAILED) {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

    // Ensure the mapped region is at the desired address
    if (mapped_region != desired_address) {
        fprintf(stderr, "Failed to map to the desired address\n");
        munmap(mapped_region, region_size);
        return EXIT_FAILURE;
    }

    // Cast the mapped region to an integer array
    int *a = (int *)mapped_region;

    // Initialize array elements
    a[0] = 10;  // Binary: 00000000 00000000 00000000 00001010
    a[1] = 20;  // Binary: 00000000 00000000 00000000 00010100
    a[2] = 30;  // Binary: 00000000 00000000 00000000 00011110
    a[3] = 40;  // Binary: 00000000 00000000 00000000 00101000
    a[4] = 50;  // Binary: 00000000 00000000 00000000 00110010

	void *p = a;

	printf("%d\n", *((char *)p + 4));
	printf("%d\n", *((char *)p + 8));
	printf("%d\n", *((char *)p + 1));

	// on little endian
    printf("\n%p\n", (char *)p + 0);
	printf("%d\n", *((int *)((char *)p + 0)));
    print_bytes((char *)p + 0, sizeof(int));

    printf("\n%p\n", (char *)p + 1);
	printf("%d\n", *((int *)((char *)p + 1)));
    print_bytes((char *)p + 1, sizeof(int)); // Print bytes for this specific statement

    printf("\n%p\n", (char *)p + 2);
	printf("%d\n", *((int *)((char *)p + 2)));
    print_bytes((char *)p + 2, sizeof(int)); // Print bytes for this specific statement

    printf("\n%p\n", (char *)p + 3);
	printf("%d\n", *((int *)((char *)p + 3)));
    print_bytes((char *)p + 3, sizeof(int)); // Print bytes for this specific statement

    printf("\n%p\n", (char *)p + 4);
	printf("%d\n", *((int *)((char *)p + 4)));
    print_bytes((char *)p + 4, sizeof(int)); // Print bytes for this specific statement

	// on big endian
	// 00000000 00000000 00000000 00001010 will be 10
	// 00000000 00000000 00001010 00000000 will be 2560
	// 00000000 00010100 00000000 00000000 will be 655360
	// 00011110 00000000 00000000 00000000 will be 167772160
	// 00000000 00000000 00000000 00010100 will be 20

	return 0;
}