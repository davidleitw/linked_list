#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next, *prev;
};

void append_node(struct node **start, int value) {
    if (!*start) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = value;
        new_node->next = new_node->prev = new_node;
        *start = new_node;
        return;
    }
    struct node *last = (*start)->prev;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = *start;
    (*start)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}

struct node *find_mid(struct node *start) {
    int count = 1;
    struct node *temp = start->next;
    while (start != temp) {
        temp = temp->next;
        count++;
    }

    if (count == 1) {
        return NULL;
    }
    
    for (int i = 0; i < count/2; i++) {
        start = start->next;
    }
    return start;
}

struct node* sep_linked_list(struct node *start) {
    struct node *mid = find_mid(start);
    struct node *end = start->prev;
    start->prev = mid->prev;
    mid->prev->next = start;
    mid->prev = end;
    end->next = mid;
    return mid;
}

struct node* merge_linked_list(struct node* start1, struct node* start2) {
    struct node *result = start1->data < start2->data ? start1 : start2;
    struct node *temp1 = start1;
    struct node *temp2 = start2;

    // TODO: add condition on while loop
    while () {
        result->prev = result;
        if (temp1->data <= temp2->data) {
            result->next = temp1;
            temp1 = temp1->next;
            temp1->next = result;
            temp1->prev = result->next;
        } else {
            result->next = temp2;
            temp2 = temp2->next;
            temp2->next = result;
            temp2->prev = result->next;
        }
        result = result->next;
    }
    return result;
}

void merge_sort(struct node **start) {
    struct node* temp = sep_linked_list(*start);
    if (temp == NULL) {
        return;
    }
    merge_sort(temp);
    merge_linked_list(start, temp);
}

int main() {
    struct node *start = NULL;

    // create a linked list with 51, 48, 72, 23, 86
    append_node(&start, 51);
    append_node(&start, 48);
    append_node(&start, 72);
    append_node(&start, 23);
    append_node(&start, 86);

    // merge sort
    merge_sort(&start);
    return 0;
}