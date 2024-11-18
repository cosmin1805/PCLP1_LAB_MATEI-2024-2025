#include <stdio.h>
#include <string.h>

int main() {
    char str1[50] = "Hello";
    char str2[50] = "World";
    char str3[50];
    int len;

    // print the strings
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    // strcpy example
    strcpy(str3, "Hello");
    printf("\nstrcpy(str3, \"Hello\"): %s\n", str3);

    // strncpy example
    strncpy(str3, "World", 3);
    str3[3] = '\0'; // null-terminate the string
    printf("\nstrncpy(str3, \"World\", 3): %s\n", str3);

    // strcat example
    strcat(str1, "World");
    printf("\nstrcat(str1, \"World\"): %s\n", str1);

    // strncat example
    strncat(str1, "World", 3);
    printf("\nstrncat(str1, \"World\", 3): %s\n", str1);

    // strlen example
    len = strlen("HelloWorldWor");
    printf("\nstrlen(\"HelloWorldWor\"): %d\n", len);

    // strcmp example
    int cmp = strcmp("HelloWorldWor", "World");
    printf("\nstrcmp(\"HelloWorldWor\", \"World\"): %d\n", cmp);

    // strncmp example
    cmp = strncmp("HelloWorldWor", "World", 3);
    printf("\nstrncmp(\"HelloWorldWor\", \"World\", 3): %d\n", cmp);

    // strchr example
    char *chr = strchr("HelloWorldWor", 'o');
    printf("\nstrchr(\"HelloWorldWor\", 'o'): %s\n", chr);

    // strrchr example
    chr = strrchr("HelloWorldWor", 'o');
    printf("\nstrrchr(\"HelloWorldWor\", 'o'): %s\n", chr);

    // strstr example
    char *substr = strstr("HelloWorldWor", "World");
    printf("\nstrstr(\"HelloWorldWor\", \"World\"): %s\n", substr);

    // memset example
    char str4[50] = "HelloWorld";
    memset(str4, 'a', 5 * sizeof(char));
    printf("\nmemset(str4, 'a', 5): %s\n", str4);

    // memcpy example
    char str5[50];
    memcpy(str5, str4, 5 * sizeof(char));
    printf("\nmemcpy(str5, str4, 5): %s\n", str5);

    // memmove example
    char str6[50] = "HelloWorld";
    memmove(str6 + 5, str6, 5);
    printf("\nmemmove(str6 + 5, str6, 5): %s\n", str6);

    return 0;
}