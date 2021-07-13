#include <stdbool.h>

// wezel
struct node{
    // wartosc
    int value;
    // wskaznik na nastepny element
    struct node* next;
};
typedef struct node* queue;

// wskazniki na pierwszy i ostatni element
// dodajemy do tail
// pobieramy z head
struct fifo_pointers{
    queue head,tail;
};
typedef struct fifo_pointers* fifo;

// wskaznik na pierwszy element
// dodajemy i pobieramy z head
struct lifo_pointers{
    queue head;
};
typedef struct lifo_pointers* lifo;

void findFIFO(fifo ptr,int value);
void addFIFO(fifo* ptr,int value);
void remFIFO(fifo* ptr);
bool isEmptyFIFO(fifo ptr);

void findLIFO(lifo ptr,int value);
void addLIFO(lifo* ptr,int value);
void remLIFO(lifo* ptr);
bool isEmptyLIFO(lifo ptr);