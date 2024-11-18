#include <stdio.h>
#include <string.h>

char* findMostPopularBestFriend(char* persons[], char* bestFriends[], int nrPersons, int* count) {
    int maxCount = 0;
    char* mostPopular = NULL;

    for (int i = 0; i < nrPersons; i++) {
        int currentCount = 0;
        for (int j = 0; j < nrPersons; j++) {
            if (bestFriends[j] == persons[i]) {
                currentCount++;
            }
        }
        if (currentCount > maxCount) {
            maxCount = currentCount;
            mostPopular = persons[i];
        }
    }

    *count = maxCount;
    return mostPopular;
}

int main() {
    int nrPersons = 5;
    char* persons[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    char* bestFriends[] = {persons[1], persons[1], persons[2], persons[1], persons[3]};

    int count;
    char* mostPopular = findMostPopularBestFriend(persons, bestFriends, nrPersons, &count);

    if (mostPopular != NULL) {
        printf("The most popular best friend is %s with %d people considering them as best friend.\n", mostPopular, count);
    } else {
        printf("No best friend found.\n");
    }

    return 0;
}
