#include <stdbool.h>

// wezel
struct node{
    // wartosc
    int value;
    // wskaznik na nastepny element
    struct node* next;
};

typedef struct node* list;

void add(list* ptr,int value);
int find(list ptr,int value);
void rem(list* ptr,int position);
bool isEmpty(list ptr);
list merge(list l1,list l2);
void printList(list ptr);

