#include <stdio.h>
#include <stdlib.h>

#define get_length(arr) sizeof(arr) / sizeof(arr[0])

void bubble_sort(int *arr, const int length) 
{
    for(int i = 0; i < length - 1; i++) {
        int flag = 0;
        for(int j = 0; j < length - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
                flag = 1;
            }
        }
        if(!flag) break;
    }
}

int main() {
    int a[7] = {2, -3, 16, 5, 17, -4, 3};
    bubble_sort(a, get_length(a));
    for(int i = 0; i < 7; i++) printf("%d ", a[i]);
    printf("\n");
}