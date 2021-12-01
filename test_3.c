//
// Created by Ryan.Zurrin001 on 11/30/2021.
// file name: test_3.c
//
#include <stdio.h>
#include <stdlib.h>
// struct node for linked list
struct node {
    int value;
    struct node *prev;
};
// struct list for linked list
struct list {
    int count;
    struct node *first;
    struct node *last;
};
// ___________________________function prototypes_______________________________
// initializes a new node
struct node* initialize_node(int);
// initializes a new list
struct list* initialize_list();
// prints the list
void print_list(struct list *);
// adds a node to the end of the list
void insert(struct list *, int);
// removes a node from the list
int remove_node_by_key(struct list**, int);
// free's the list
void free_list(struct list*);
// __________________________________main_______________________________________
int main() {
    struct list* l = initialize_list();
    int val;

    int toRemove= 0;
    int size = 0;
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        scanf("%d ", &val);
        insert(l, val);
    }
    scanf("%d", &toRemove);
    for (int i = 0; i < size; ++i) {
        remove_node_by_key(&l, toRemove);
    }
    print_list(l);
    free_list(l);
    l = NULL;
    return 0;
} //________________________________ end main___________________________________
// _____________________________function definitions____________________________
////////////////////////////////////////////////////////////////////////////////
struct node* initialize_node(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = data;
    newNode->prev = NULL;
    return newNode;
} // end initialize_node
struct list* initialize_list() {
    struct list *newList = malloc(sizeof(struct list));
    newList->first = NULL;
    newList->last = NULL;
    newList->count = 0;
    return newList;
} // end initialize_list
void insert(struct list *list, int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = data;
    newNode->prev = NULL;
    if (list->first == NULL) {
        list->first = newNode;
        list->last = newNode;
    } else {
        newNode->prev = NULL;
        list->first->prev = newNode;
        list->first = newNode;
    }
    list->count++;
} // end insert
void print_list(struct list *list) {
    if(list->first == NULL) {
        return;
    }
    struct node *current = list->last;
    while (current->prev != NULL) {
        printf("%d,", current->value);
        current = current->prev;
    }
    printf("%d ", current->value);
} // end print_list
int remove_node_by_key(struct list** l, int key) {
    if ((*l)->first == NULL) {
        return 0;
    }
    struct node *current = (*l)->last;
    int idx = 0;
    while (current != NULL) {
        if (current->value == key) {
            if (current == (*l)->first && current == (*l)->last) {
                (*l)->first = NULL;
                (*l)->last = NULL;
                free(current);
                (*l)->count--;
                return 1;
            } else if (current == (*l)->first) {
                struct node *temp = (*l)->last;
                struct node *temp2 = (*l)->first;
                for (int i = 0; i < idx - 1; i++) {
                    temp = temp->prev;
                }
                (*l)->first = temp;
                (*l)->first->prev = NULL;
                free(temp2);
                (*l)->count--;
            } else if (current == (*l)->last) {
                struct node *temp = current;
                struct node *temp2 = current->prev;
                (*l)->last = temp2;
                current = temp2;
                free(temp);
                (*l)->count--;
            } else {
                struct node* temp = current;
                struct node* place = (*l)->last;
                for (int i = 0; i < idx - 1; i++) {
                    place = place->prev;
                }
                place->prev = current->prev;
                current = current->prev;
                free(temp);
                (*l)->count--;
            }
        }
        idx++;
        if (idx > (*l)->count) {
            return 1;
        }
        current = current->prev;
    }
}// end remove_all_nodes_by_key
void free_list(struct list* l) {
    struct node* n = l->last;
    while (n != NULL) {
        struct node* temp = n;
        n = n->prev;
        temp->prev = NULL;
        free(temp);
        l->count -= 1;
    }
    l->first = NULL;
    l->last = NULL;
    l->count = 0;
    free(l);
    l = NULL;
} // end free_list