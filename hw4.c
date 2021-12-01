/*
* author: Ryan Zurrin
* filename: HW4.c
* description: Use a doubly linked list to add a number into a sorted list
* into its proper location and then print the list in ascending as well as
* reversed order. I decided to build this DS to have a bit of flexibility so
* if we were to try taking in other types besides just integers such as chars,
* doubles or floats we can change the defines below to the proper types we wish to
* use, and we can then read in chars, floats, doubles, and ints. I have not got
* the sting or char* to work correctly yet, but it is being worked on still.
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
// initializes a new node for the list
struct NODE *initialize_node(T element);
// initializes a linked list with dummy head/tail
struct LIST *initialize_list(void (*p)(struct NODE *));
// adds a new node to front of list
void insert_front(T element, struct LIST**);
// adds a new node to back of list
void insert_back(T element, struct LIST**);
// inserts an element in its proper ascending order location within the
// doubly linked list
__attribute__((unused))
void insert_element_ascending(T, struct LIST**);
// inserts an element in its proper index maintaining descending order
__attribute__((unused))
void insert_element_descending(T, struct LIST**);
// inserts an element in the specified index if the index is within the
// bounds of the list and returns 1 if successful and 0 if not
__attribute__((unused))
int insert_element_at_index(T, int, struct LIST**);
// inserts an element in its proper descending order location within the
// maintaining all unique elements and returns 1 if successful and 0 if not
__attribute__((unused))
int insert_element_ascending_no_duplicates(T, struct LIST**);
// inserts an element in its proper descending order location within the list
// maintaining all unique elements and returns 1 if successful and 0 if not
__attribute__((unused)) __attribute__((unused))
int insert_element_descending_no_duplicates(T, struct LIST**);
// inserts the given elements starting at the given index and returns 1 if
// successful and 0 if not
__attribute__((unused)) int insert_elements_starting_at_index(
        T*, int, int, struct LIST**);
// changes the data of the node at the given index and returns 1 if successful
// and 0 if not
__attribute__((unused)) int modify_element_at_index(T, int, struct LIST**);
// removes the node at the given index and returns the data of the removed
// node else returns -1
__attribute__((unused)) T remove_node_at_index(struct LIST**, int);
// removes the first node found in the list that is equal to the given key
// returns 1 if successful and 0 if not
__attribute__((unused)) int remove_first_node_by_key(struct LIST**, T);
// removes all the nodes with the given key and returns the number of nodes
// removed
__attribute__((unused)) int remove_all_nodes_by_key(struct LIST**, T);
// removes all the nodes from the list
__attribute__((unused)) void make_list_empty(struct LIST**);
// returns the number of times the given key is found in the list
__attribute__((unused)) int get_key_count(struct LIST**, T);
// returns the index of the first node found in the list
__attribute__((unused)) T get_first_element(struct LIST**);
// returns the index of the last node found in the list
__attribute__((unused)) T get_last_element(struct LIST**);
// returns the size of the list
__attribute__((unused)) int get_list_count(struct LIST**);
// returns the index of the first node found in the list that is equal to the
// given key or -1 if not found
__attribute__((unused)) int get_first_index_of_key(struct LIST**, T);
// returns the index of the last node found in the list that is equal to the
// given key or -1 if not found
__attribute__((unused)) int get_last_index_of_key(struct LIST**, T);

// print functions for function pointer argument used while initializing
// the list for the first time
__attribute__((unused)) void print_float(struct NODE*);
__attribute__((unused)) void print_double(struct NODE*);
__attribute__((unused)) void print_char(struct NODE*);
__attribute__((unused)) void print_int(struct NODE*);
//__attribute__((unused)) void print_str(struct NODE*);
// prints the lists elements using one of the above print methods
void print_list(struct LIST**);
// prints the list in reversed order starting at last node using one
// of the above print functions
void print_list_reversed(struct LIST**);
// frees the lists elements releasing memory back to system
void free_list(struct LIST*);
//*****************************************************************************
// ________________________starting point of program___________________________
int main() {
    struct LIST* l = initialize_list(PRINT_TYPE);
    T val;

    int toRemove= 0;
    if (IN_TYPE == " %c") {
        while((val = (T)getchar()) != EOF) {
            insert_back(val, &l);
        }

    } else {
        int size = 0;
        scanf("%d", &size);
        for (int i = 0; i < size; i++) {
            scanf(IN_TYPE, &val);
            insert_back(val, &l);
        }
    }
    scanf("%d", &toRemove);
    remove_all_nodes_by_key(l, toRemove);
    print_list(&l);
    free_list(l);
    l = NULL;
    return 0;
}
//______________________________end main function______________________________
//*****************************************************************************
//_____________________________Function Definitions____________________________

struct NODE *initialize_node(T element) {
    struct NODE* n = (struct NODE*)malloc(sizeof(struct NODE));
    n->data = element;
    n->next = NULL;
    n->prev = NULL;
    return n;
} // end initialize_node

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

__attribute__((unused))
void insert_element_ascending(T element, struct LIST **l) {
    // if node is first to be inserted in list
    if (((*l)->first) == NULL) {
        insert_front(element, l);
        return;
    }
    // if node to be inserted has a less value than the first
    // it will become the new first
    if (element <= ((*l)->first->data)) {
        insert_front(element, l);
        return;
    }
    // if node to be inserted has a greater value then the last
    // it will become the new last node
    if (element >= ((*l)->last->data))  {
        insert_back(element, l);
        return;
    }
    // if node is in middle of list find its place and insert into
    // list, so it maintains ascending order
    struct NODE* n = initialize_node(element);
    struct NODE* current = (*l)->first->next;
    while(current->next != NULL && (current->data) < (n->data)) {
        current = current->next;
    }
    (current->prev)->next = n;
    n->prev = current->prev;
    current->prev = n;
    n->next = current;
    (*l)->count += 1;
} // end insert_element

__attribute__((unused))
void insert_element_descending(T element, struct LIST **l) {
    // if node is first to be inserted in list
    if (((*l)->first) == NULL) {
        insert_front(element, l);
        return;
    }
    // if node to be inserted has a larger value than the first
    // it will become the new first
    if (element >= ((*l)->first->data)) {
        insert_front(element, l);
        return;
    }
    // if node to be inserted has a lessor value then the last
    // it will become the new last node
    if (element <= ((*l)->last->data))  {
        insert_back(element, l);
        return;
    }
    // if node is in middle of list find its place and insert into
    // list, so it maintains descending order
    struct NODE* n = initialize_node(element);
    struct NODE* current = (*l)->first->next;
    while(current->next != NULL && (current->data) > (n->data)) {
        current = current->next;
    }
    (current->prev)->next = n;
    n->prev = current->prev;
    current->prev = n;
    n->next = current;
    (*l)->count += 1;
} // end insert_element_descending

__attribute__((unused))
int insert_element_at_index(T element, int index, struct LIST **l) {
    if (index == 0) {
        insert_front(element, l);
        return 1;
    }
    if (index > (*l)->count +1 || index < 0) {
        return 0;
    }
    if (index == (*l)->count) {
        insert_back(element, l);
        return 1;
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
    return 1;
}

__attribute__((unused))
int insert_element_ascending_no_duplicates(T element, struct LIST **l) {
    if (((*l)->first) == NULL) {
        insert_front(element, l);
        return 1;
    }
    if (get_key_count(&(*l), element) > 0) {
        return 0;
    }
    if (element < ((*l)->first->data)) {
        insert_front(element, l);
        return 1;
    }
    if (element > ((*l)->last->data))  {
        insert_back(element, l);
        return 1;
    }
    struct NODE* current = (*l)->first->next;
    struct NODE* n = initialize_node(element);
    while(current->next != NULL && (current->data) < (n->data)) {
        current = current->next;
    }
    (current->prev)->next = n;
    n->prev = current->prev;
    current->prev = n;
    n->next = current;
    (*l)->count += 1;
    return 1;
}  // end insert_elements_no_duplicates

__attribute__((unused))
int insert_element_descending_no_duplicates(T element, struct LIST **l) {
    if (((*l)->first) == NULL) {
        insert_front(element, l);
        return 1;
    }
    if (get_key_count(&(*l), element) > 0) {
        return 0;
    }
    if (element > ((*l)->first->data)) {
        insert_front(element, l);
        return 1;
    }
    if (element < ((*l)->last->data))  {
        insert_back(element, l);
        return 1;
    }
    struct NODE* current = (*l)->first->next;
    struct NODE* n = initialize_node(element);
    while(current->next != NULL && (current->data) > (n->data)) {
        current = current->next;
    }
    (current->prev)->next = n;
    n->prev = current->prev;
    current->prev = n;
    n->next = current;
    (*l)->count += 1;
    return 1;
}  // end insert_elements_no_duplicates

__attribute__((unused)) int insert_elements_starting_at_index(
        T* elements, int num_elements, int index, struct LIST **l) {
    if (index == 0) {
        for (int i = num_elements-1; i >= 0; i--) {
            insert_front(elements[i], l);
        }
        return 1;
    }
    if (index > (*l)->count +1 || index < 0) {
        return 0;
    }
    if (index == (*l)->count) {
        for (int i = 0; i < num_elements; i++) {
            insert_back(elements[i], l);
        }
        return 1;
    }
    int j = index;
    for (int i = 0; i < num_elements; i++) {
        insert_element_at_index(elements[i], j++, l);
        (*l)->count += 1;
    }
    return 1;
} // end insert_elements_ascending_staring_at_index

__attribute__((unused))
int modify_element_at_index(T element, int index, struct LIST **l) {
    if (index > (*l)->count || index < 0) {
        return 0;
    }
    struct NODE* current = (*l)->first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = element;
    return 1;
}
__attribute__((unused))
T remove_node_at_index(struct LIST** l, int index) {
    struct NODE *current;
    current = (*l)->first;
    for (int i=0; i < index; i++) {
        if (current == NULL) {
            // reach end of list before seeing position pos
            return -1;
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
    T item = (*current).data;
    free(current);
    (*l)->count -= 1;
    return item;
} // end removeNode

__attribute__((unused))
int remove_first_node_by_key(struct LIST** l, T key) {
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

__attribute__((unused)) int remove_all_nodes_by_key(struct LIST** l, T key) {
    int count = 0;
    struct NODE *current = (*l)->first;
    if (current == NULL) {
        // list is empty
        return 0;
    }
    for (int i = 0; i < (*l)->count; i++) {
        struct NODE* temp = (*current).next;
        if ((*current).data == key) {

            if ((*current).next != NULL) {
                temp = (*current).next;
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
            count += 1;
        }
        current = temp;
    }
    return count;
} // end removeNodeByKey

__attribute__((unused)) void make_list_empty(struct LIST** l) {
    struct NODE* current = (*l)->first;
    struct NODE* temp;
    while (current != NULL) {
        temp = (*current).next;
        free(current);
        current = temp;
    }
    (*l)->first = NULL;
    (*l)->last = NULL;
    (*l)->count = 0;
} // end makeListEmpty

__attribute__((unused))
int get_key_count(struct LIST** l, T key) {
    struct NODE *current = (*l)->first;
    int count = 0;
    for (; current->next != NULL; current = current->next) {
        if ( (*current).data == key) {
            count++;
        }
    }
    return count;
} // end getKeyCount

__attribute__((unused)) T get_first_element(struct LIST** l) {
    if ((*l)->first == NULL) {
        return -1;
    }
    return (*(*l)->first).data;
} // end getFirstElement

__attribute__((unused)) T get_last_element(struct LIST** l) {
    if ((*l)->last == NULL) {
        return -1;
    }
    return (*(*l)->last).data;
} // end getLastElement

__attribute__((unused)) int get_list_count(struct LIST** l) {
    return (*l)->count;
} // end getListCount

__attribute__((unused)) int get_first_index_of_key(struct LIST** l, T key) {
    if ((*l)->first->data == key) {
        return 0;
    }
    if ((*l)->last->data == key) {
        return (*l)->count - 1;
    }
    struct NODE* current = (*l)->first;
    int index = 0;
    for (; current->next != NULL; current = current->next) {
        if ( (*current).data == key) {
            return index;
        }
        index++;
    }
    return -1;
} // end getFirstIndexOfKey

__attribute__((unused)) int get_last_index_of_key(struct LIST** l, T key) {
    int index = get_first_index_of_key(l, key);
    if (index != -1) {
        return  index + get_key_count(l, key) - 1;
    }
    return -1;
} // end getLastIndexOfKey

__attribute__((unused))
void print_float(struct NODE *n) {
    printf("%f ", (float)n->data);
}
__attribute__((unused))
void print_double(struct NODE *n) {
    printf("%lf ", (double)n->data);
}
__attribute__((unused))
void print_char(struct NODE *n) {
    printf("%c", (char)n->data);
}
//__attribute__((unused)) void print_str(struct NODE *n) {
//    printf("%s ", n->data);
//}
__attribute__((unused))
void print_int(struct NODE *n) {
    printf("%d ", (int) n->data);
} // end generic print functions

void print_list(struct LIST** l) {
    struct NODE* current = (*l)->first;
    while (current != NULL) {
        (*l)->print(current);
        current = current->next;
    }
}// end print_list

void print_list_reversed(struct LIST** l) {
    struct NODE *current = (*l)->last;
    while (current != NULL) {
        (*l)->print(current);
        current = current->prev;
    }
} // end print_list_reversed

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