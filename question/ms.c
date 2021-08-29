#include <stdio.h>
#include <stdlib.h>

#define get_length(arr) sizeof(arr) / sizeof(arr[0])

void merge(int *arr, int head, int midd, int tail);

void merge_sort(int *arr, int head, int tail) {
    if(head < tail) {
        int midd = (head + tail) / 2;
        merge_sort(arr, head, midd);
        merge_sort(arr, midd+1, tail);
        merge(arr, head, midd, tail);
    }
}

void merge(int *arr, int head, int midd, int tail) {
    int l_length = midd - head + 1;
    int r_length = tail - midd;

    int l_run[l_length];
    int r_run[r_length];

    for(int i = 0; i < l_length; i++) {
        l_run[i] = arr[head+i];
    }
    for(int i = 0; i < r_length; i++) {
        r_run[i] = arr[midd+i+1];
    }
    
    int l_index = 0;
    int r_index = 0;
    int arr_index = 0;
    while(l_index < l_length && r_index < r_length) {
        if(l_run[l_index] > r_run[r_index]) {
            arr[head+arr_index] = r_run[r_index++];
        } else {
            arr[head+arr_index] = l_run[l_index++];
        }
        arr_index++;
    }

    while(l_index < l_length) {
        arr[head+arr_index++] = l_run[l_index++];
    }
    while(r_index < r_length) {
        arr[head+arr_index++] = r_run[r_index++];
    }
}

int main() {
    // int arr[8] = {5,3,8,6,2,7,1,4};
    int arr[7] = {38, 27, 43, 3, 9, 82, 10};
    merge_sort(arr, 0, get_length(arr)-1);
    for(int i = 0; i < 7 ; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}