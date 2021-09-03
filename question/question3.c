#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

void print(list *head) {
    list *tmp = head;
    while(tmp) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

list *sort(list *start) {
    if (!start || !start->next) // return single node, or NULL;
        return start;
    list *left = start;
    list *right = left->next;
    left->next = NULL;
    /* LL0; */
    left = sort(left);
    right = sort(right);
    print(left);
    print(right);

    for(list *merge = NULL; left || right; ) {
        /*
            right 是已經排列好的, 如果 left->data < right->data, 則應該要把 left 當作新的 head;.
        */
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
            // left->data >= right->data    
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
    head->data = 1;

    list *n1 = malloc(sizeof(list));
    n1->data = -3;
    head->next = n1;

    list *n2 = malloc(sizeof(list));
    n2->data = 2;
    n1->next = n2;

    list *n3 = malloc(sizeof(list));
    n3->data = -4;
    n2->next = n3;

    list *n4 = malloc(sizeof(list));
    n4->data = 5;
    n3->next = n4;

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