#include <stdio.h>

unsigned char *green(unsigned int color, unsigned char *green_value) {
    // Extract the green component (second byte)
    //*green_value = (color >> 8) & 0xFF;
    *green_value = *(((unsigned char *)&color + 1));
    
    return (unsigned char *)&color + 1;
}

int main() {
    unsigned int color = 0x12345678; // Example color
    unsigned char *green_value;
    unsigned char *green_address = green(color, green_value);
    
    printf("Color: %x\n", color);
    printf("Green value: %x\n", *green_value);
    printf("Green address: %p\n", green_address);
    
    return 0;
}