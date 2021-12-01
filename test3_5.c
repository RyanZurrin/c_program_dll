//
// Created by Ryan.Zurrin001 on 11/30/2021.
//
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev;
};

struct list {
    int count;
    struct node *first;
    struct node *last;
};

struct node* initialize_node(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->prev = NULL;
    return newNode;
}
struct list* initialize_list() {
    struct list *newList = malloc(sizeof(struct list));
    newList->first = NULL;
    newList->last = NULL;
    newList->count = 0;
    return newList;
}

void insert(struct list *list, int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
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
}

void print_list(struct list *list) {
    struct node *current = list->last;
    while (current->prev != NULL) {
        printf("%d,", current->data);
        current = current->prev;
    }
    printf("%d ", current->data);
    printf("\n");
}
int remove_at_index(struct list** l, int index) {
    struct node *current;
    current = (*l)->last;
    struct node* p2 = NULL;
    for (int i=0; i < index; i++) {
        if (i == index-1) {
            p2 = current;
        }
        if (current == NULL) {
            // reach end of list before seeing position pos
            return -1;
        } else {
            current = current->prev;
        }
    }
    struct node* p1 = (*current).prev;
    if (p1 == NULL) {
        // p is first node in list
        (*p2).prev = NULL;
        (*l)->first = p2;
    } else {
        (*p1).prev = p2;
        (*p2).prev = p1;
    }
    int item = (*current).data;
    free(current);
    (*l)->count -= 1;
    return item;
} // end removeNode

void removeIndex(struct list** l, int index) {
    struct node *current;
    current = (*l)->last;
    struct node* p2 = NULL;
    for (int i=0; i < index; i++) {
        if (i == index-1) {
            p2 = current;
        }
        if (current == NULL) {
            // reach end of list before seeing position pos
            return;
        } else {
            current = current->prev;
        }
    }
    struct node* p1 = (*current).prev;
    if (p1 == NULL) {
        // p is first node in list
        (*p2).prev = NULL;
        (*l)->first = p2;
    } else {
        (*p1).prev = p2;
        (*p2).prev = p1;
    }
    free(current);
    (*l)->count -= 1;
} // end removeNode

int remove_all_nodes_by_key(struct list** l, int key) {
    if ((*l)->first == NULL) {
        return 0;
    }
    struct node *current = (*l)->last;
    int idx = 0;
    while (current != NULL) {
        if (current->data == key) {
            if (current == (*l)->first && current == (*l)->last) {
                (*l)->first = NULL;
                (*l)->last = NULL;
                free(current);
                (*l)->count--;
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
}

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
    removeIndex(&l, toRemove);
    struct node* n = l->last;
    for (int i = 0; i < l->count; i++) {
        printf("%d ", n->data);
        n = n->prev;
    }
    //print_list(l);
    free_list(l);
    l = NULL;
    return 0;
}