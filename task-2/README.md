# Task 2: Find Duplicates

## Statement

Given an array of _n_ elements, print the number of duplicates and list them

## Specifications

You must use pointers in your approach

## Code
```c
#include <stdio.h>
#include <string.h>

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 6, 3, 7, 8, 9, 9, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int frequency[100] = {0};

    int *ptr = arr;
    for (int i = 0; i < n; i++) {
        (*(frequency + *ptr))++;
        ptr++;
    }

    int duplicates = 0;
    char res[3*n];

    for (int i = 0; i < 100; i++) {
        if (*(frequency + i) > 1) {
            if (duplicates++) sprintf(res + strlen(res), "%d ", i);
            else sprintf(res, "%d ", i);
        }
    }

    printf("%d\n%s", duplicates, res);

    return 0;
}
```

## Runtime
```
4
2 3 5 9
```