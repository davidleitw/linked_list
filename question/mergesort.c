#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
};

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

void append_node(struct node **head, int value) {
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

void push_front(struct node **head, struct node *n) {
    n->prev = (*head)->prev;
    (*head)->prev->next = n;
    
    n->next = (*head);
    (*head)->prev = n;
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

struct node *find_middle(struct node *head, struct node *tail, int length) {
    struct node *fast = head;
    struct node *slow = head;
    if(length & 1) {
        while(fast != tail) {
            fast = fast->next->next;
            slow = slow->next;
        }
    } else {
        while(fast != tail->prev) {
            fast = fast->next->next;
            slow = slow->next;
        }
    }
    return slow;
}

struct node* remove_head(struct node **head) {
    struct node *h = *head;
    (*head)->prev->next = (*head)->next;
    (*head)->next->prev = (*head)->prev;
    (*head) = (*head)->next;
    return h;
}

void merge(struct node *lists, struct node *head, struct node *midd, struct node *tail) {
    struct node *l_head = head;
    struct node *r_head = midd->next;
    
    
    midd->next = l_head;
    l_head->prev = midd;
    tail->next = r_head;
    r_head->prev = tail;
    printf_nodes(&l_head);
    printf_nodes(&r_head);

    while(l_head != midd && r_head != tail) {
        if(l_head->data <= r_head->data) {
            struct node *lh = remove_head(&l_head);
            push_front(&r_head, lh);
        } else {
            struct node *rh = remove_head(&r_head);
            push_front(&l_head, rh);
        }
    }
    while(l_head != midd) {
        struct node *lh = remove_head(&l_head);
        push_front(&r_head, lh);
    }
    while(r_head != tail) {
        struct node *rh = remove_head(&r_head);
        push_front(&l_head, rh);
    }
}


void merge_sort(struct node *lists, struct node *head, struct node *tail, int length) {
    struct node *middle = find_middle(head, tail, length);
    printf("middle node data = %d\n", middle->data);    
    if(head != tail) {
        merge_sort(lists, head, middle, length/2 + length%2);
        merge_sort(lists, middle->next, tail, length/2);
        merge(lists, head, middle, tail);
    }
}



int main() {
    struct node *head = NULL;
    append_node(&head, 2);
    append_node(&head, -3);
    append_node(&head, 16);
    append_node(&head, 5);
    append_node(&head, 17);
    append_node(&head, -4);
    append_node(&head, 3);
    append_node(&head, 8);
    printf_nodes(&head);
    
    int length = get_lists_length(head);
    printf("length = %d\n", length);

    merge_sort(head, head, head->prev, length);
    return 0;
}