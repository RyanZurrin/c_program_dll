/*
* author: Ryan Zurrin
* filename: HW4.c
* description: Use a doubly linked list to add a number into a sorted list
* into its proper location and then print the list in ascending as well as
* reversed order. I decided to build this DS to have a bit of flexibility so
* if we were to try taking in other types besides just integers such as chars,
* doubles or floats we can change the defines below to the proper types we wish to
* use, and we can then read in chars, floats, doubles, and ints. I have not got
* the sting or char* to work correctly yet but it is being worked on still.
*
* due-date: 11/25/21
*/
#include <stdio.h>
#include <stdlib.h>
// ______________________Specify program input types below_____________________
// PRINT_TYPE is used to set the lists print type to one of the following
// *print_float
// *print_double
// *print_char
// *print_int
#define PRINT_TYPE print_int // set to type you will be printing
// set T to the type of data you will be  reading in
#define T int // change data type (should match print type)
#define IN_TYPE " %d" // define the format specifier to use in scanf
//___________________________End Type specification____________________________
// ______________________structures to be used in program______________________
// node structure to hold data and pointer to next node and previous node______
struct NODE {
    T data;
    struct NODE *next;
    struct NODE *prev;
};
// list to maintain pointers to first and last nodes in list___________________
struct LIST {
    int count;
    struct NODE *first;
    struct NODE *last;
    void (*print)(struct NODE*);
};
//_____________________________________________________________________________
// ___________________________function prototypes______________________________
struct NODE *initialize_node(T element);
struct LIST *initialize_list(void (*p)(struct NODE *));
void insert_front(T element, struct LIST **l);
void insert_back(T element, struct LIST **l);
void insert_element(T element, struct LIST **l);
void insert_at_index(T element, int index, struct LIST **l);
__attribute__((unused)) void removeNodeAtIndex(struct LIST**, int);
__attribute__((unused)) int removeNodeByKey(struct LIST**, T);
__attribute__((unused)) int getKeyCount(struct LIST**, T);
__attribute__((unused)) void print_float(struct NODE*);
__attribute__((unused)) void print_double(struct NODE*);
__attribute__((unused)) void print_char(struct NODE*);
__attribute__((unused)) void print_int(struct NODE*);
//__attribute__((unused)) void print_str(struct NODE*);
void print_list(struct LIST**);
void print_list_reversed(struct LIST**);
void free_list(struct LIST*);
//*****************************************************************************
// ________________________starting point of program___________________________
int main() {
    struct LIST* l = initialize_list(PRINT_TYPE);
    T val;

    if (IN_TYPE == " %c") {
        while((val = (T)getchar()) != EOF) {
            insert_back(val, &l);
        }

    } else {
        int size = 0;
        scanf("%d", &size);
        size++;
        for (int i = 0; i < size; i++) {
            scanf(IN_TYPE, &val);
            insert_element(val, &l);
        }
    }
    print_list(&l);
    printf("\n");
    print_list_reversed(&l);
    free_list(l);
    l = NULL;
    return 0;
}
//______________________________end main function______________________________
//*****************************************************************************
//_____________________________Function Definitions____________________________
// initializes a new node for the list
struct NODE *initialize_node(T element) {
    struct NODE* n = (struct NODE*)malloc(sizeof(struct NODE));
    n->data = element;
    n->next = NULL;
    n->prev = NULL;
    return n;
} // end initialize_node
// initializes a linked list with dummy head/tail
struct LIST *initialize_list(void (*p)(struct NODE *)) {
    struct LIST* l = (struct LIST*)malloc(sizeof(struct LIST));
    if (l != NULL) {
        l->first = NULL;
        l->last = NULL;
        l->count = 0;
        l->print = p;
    }
    return l;
} // end initialize_list
// adds a new node to front of list
void insert_front(T element, struct LIST **l) {
    struct NODE* n = initialize_node(element);
    if ((*l)->count != 0) {
        struct NODE *temp = (*l)->first;
        n->next = (*l)->first;
        (*l)->first = n;
        temp->prev = n;
    } else {
        (*l)->first = n;
        (*l)->last = n;
    }
    (*l)->count += 1;
} // end insertFront
// adds a new node to back of list
void insert_back(T element, struct LIST **l) {
    struct NODE* n = initialize_node(element);
    if ((*l)->count != 0) {
        struct NODE *temp = (*l)->last;
        n->prev = (*l)->last;
        (*l)->last = n;
        temp->next = n;
    } else {
        (*l)->first = n;
        (*l)->last = n;
    }
    (*l)->count += 1;
} // end insert_back
// inserts an element in its proper ascending order location within the
// doubly linked list
void insert_element(T element, struct LIST **l) {
    // if node is first to be inserted in list
    if (((*l)->first) == NULL) {
        insert_front(element, l);
        return;
    }
    // if node to be inserted has a less value then the first
    // it will become the new first
    if (element <= ((*l)->first->data)) {
        insert_front(element, l);
        return;
    }
    // if node to be inserted has a greator value then the last
    // it will become the new last node
    if (element >= ((*l)->last->data))  {
        insert_back(element, l);
        return;
    }
    // if node is in middle of list find its place and insert into
    // list so it maintains ascending order
    struct NODE* n = initialize_node(element);
    struct NODE* current = (*l)->first->next;
    while(current->next != NULL && (current->data) < (n->data)) {
        current = current->next;
    }
    (current->prev)->next = n;
    n->prev = current->prev;
    current->prev = n;
    n->next = current;
} // end insert_element

void insert_at_index(T element, int index, struct LIST **l) {
    if (index == 0) {
        insert_front(element, l);
        return;
    }
    if (index == (*l)->count) {
        insert_back(element, l);
        return;
    }
    struct NODE* n = initialize_node(element);
    struct NODE* current = (*l)->first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    (current->prev)->next = n;
    n->prev = current->prev;
    current->prev = n;
    n->next = current;
    (*l)->count += 1;
}

// removes the node at the given index
__attribute__((unused)) void removeNodeAtIndex(struct LIST** l, int index) {
    struct NODE *current;
    current = (*l)->first;
    for (int i=0; i < index; i++) {
        if (current == NULL) {
            // reach end of list before seeing position pos
            return;
        } else {
            current = (*current).next;
        }
    }
    struct NODE* p1 = (*current).prev;
    struct NODE* p2 = (*current).next;
    if (p1 == NULL) {
        // p is first node in list
        (*p2).prev = NULL;
        (*l)->first = p2;
    } else {
        (*p1).next = p2;
        (*p2).prev = p1;
    }
    free(current);
    (*l)->count -= 1;
} // end removeNode
// removes the first node found in the list that is equal to the given key
// returns 1 if successful, 0 if not
__attribute__((unused)) int removeNodeByKey(struct LIST** l, T key) {
    struct NODE *current = (*l)->first;
    if (current == NULL) {
        // list is empty
        return 0;
    }
    for (; (*current).next != NULL && (*current).next->data < key ;
                                             current = (*current).next) {
        if ((*current).data == key) {
            struct NODE* p1 = (*current).prev;
            struct NODE* p2 = (*current).next;
            if (p1 == NULL) {
                // p is first node in list
                (*p2).prev = NULL;
                (*l)->first = p2;
            } else {
                (*p1).next = p2;
                (*p2).prev = p1;
            }
            free(current);
            (*l)->count -= 1;
            return 1;
        }
    }
    return 0;
} // end removeNodeByKey

__attribute__((unused)) int getKeyCount(struct LIST** l, T key) {
    struct NODE *current = (*l)->first;
    int count = 0;
    for (; current->next != NULL; current = current->next) {
        if ( (*current).data == key) {
            count++;
        }
    }
    return count;
} // end getKeyCount
// print functions for function pointer argument used while initializing
// the list for the first time
__attribute__((unused)) void print_float(struct NODE *n) {
    printf("%f ", (float)n->data);
}
__attribute__((unused)) void print_double(struct NODE *n) {
    printf("%lf ", (double)n->data);
}
__attribute__((unused)) void print_char(struct NODE *n) {
    printf("%c", (char)n->data);
}
//__attribute__((unused)) void print_str(struct NODE *n) {
//    printf("%s ", n->data);
//}
__attribute__((unused)) void print_int(struct NODE *n) {
    printf("%d ", (int) n->data);
} // end generic print functions
// prints the lists elements using one of the above print methods
void print_list(struct LIST** l) {
    struct NODE* current = (*l)->first;
    while (current != NULL) {
        (*l)->print(current);
        current = current->next;
    }
}// end print_list
// prints the list in reversed order starting at last node using one
// of the above print functions
void print_list_reversed(struct LIST** l) {
    struct NODE *current = (*l)->last;
    while (current != NULL) {
        (*l)->print(current);
        current = current->prev;
    }
} // end print_list_reversed
// frees the lists elements releasing memory back to system
void free_list(struct LIST* l) {
    struct NODE* n = l->first;
    while (n != NULL) {
        struct NODE* temp = n;
        n = n->next;
        temp->prev = NULL;
        temp->next = NULL;
        free(temp);
        l->count -= 1;
    }
    l->first = NULL;
    l->last = NULL;
    l->count = 0;
    free(l);
    l = NULL;
} // end free_list