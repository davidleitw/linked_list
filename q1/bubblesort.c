#include <stdlib.h>
#include <stdio.h>

struct node {
    int data;
    struct node *next, *prev;
};

void insert_tail(struct node **head, int value) {
    if(!*head) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = value;
        new_node->next = new_node->prev = new_node;
        *head = new_node;
        return;
    }

    struct node *last_node = (*head)->prev;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = *head;
    (*head)->prev = new_node;
    new_node->prev = last_node;
    last_node->next = new_node;
}

int get_lists_length(struct node *head) {
    if(!head) return 0;
    int count = 1;
    struct node *iterator = head->next;
    while(iterator != head) {
        count++;
        iterator = iterator->next;
    }
    return count;
}

void swap_node(struct node **n1, struct node **n2) {
    (*n1)->prev->next = (*n2);
    (*n2)->prev = (*n1)->prev;
    
    (*n1)->next = (*n2)->next;
    (*n2)->next->prev = (*n1);
    
    (*n1)->prev = (*n2);
    (*n2)->next = (*n1);
}

void printf_nodes(struct node **head) {
    struct node *iter = (*head)->next;
    
    printf("%d ", (*head)->data);
    while(iter != *head) {
        printf("%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");
}

void bubble_sort(struct node **head, const int length) {
    if(!*head) return;
    struct node *tnode; // temp
    struct node *lnode = *head;
    struct node *rnode = lnode->next;

    for(int i = 0; i < length - 1; i++) {
        int flag = 0;
        for(int j = 0; j < length - i; j++) {
            if(lnode->data > rnode->data) {
                swap_node(&lnode, &rnode);
                tnode = rnode;
                rnode = lnode;
                lnode = tnode;
                flag = 1;
            }
            lnode = lnode->next;
            rnode = rnode->next;
        }
        for(int j = 0; j < i+1; j++)
            lnode = lnode->next;
        rnode = lnode->next;
        if(!flag) break;
    }
    *head = lnode;
}


int main() {
    // int a[7] = {2, -3, 16, 5, 17, -4, 3};
    struct node *head = NULL;
    insert_tail(&head, 2);
    insert_tail(&head, -3);
    insert_tail(&head, 16);
    insert_tail(&head, 5);
    insert_tail(&head, 17);
    insert_tail(&head, -4);
    insert_tail(&head, 3);

    printf_nodes(&head);
    
    int length = get_lists_length(head);
    printf("length = %d\n", length);

    bubble_sort(&head, length);
    printf_nodes(&head);
}