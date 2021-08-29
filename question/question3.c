#include <stdio.h>
#include <stdlib.h>

// 

typedef struct __list {
    int data;
    struct __list *next;
} list;

list *sort(list *start) {
    if (!start || !start->next) // return single node, or NULL;
        return start;
    list *left = start;
    list *right = left->next;
    left->next = NULL;
    /* 
        LL0; 
        left->next = NULL:
    */

    left = sort(left);
    right = sort(right);

    // recursion insertion sort, insert left element to sorted right list. 
    for(list *merge = NULL; left || right; ) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
                /* LL1; */
            } else {
                merge->next = left;
                /* LL2; */
                merge = merge->next;
            }
            left = left->next;
            /* LL3; */
        } else {
            if (!merge) {
                start = merge = right;
                /* LL4; */
            } else {
                merge->next = right;
                /* LL5; */
                merge = merge->next;
            }
            right = right->next;
            /* LL6; */
        }
    }
    return start;
}

int main() {
    list *head = malloc(sizeof(list));
    head->data = -10;

    list *n1 = malloc(sizeof(list));
    n1->data = 12;
    head->next = n1;

    list *n2 = malloc(sizeof(list));
    n2->data = -3;
    n1->next = n2;

    list *n3 = malloc(sizeof(list));
    n3->data = -18;
    n2->next = n3;

    list *iter = head;
    while(iter) {
        printf("%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");

    iter = sort(head);

    while(iter) {
        printf("%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");

    return 0;
}