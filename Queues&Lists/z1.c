#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void addFIFO(fifo* ptr, int value){
    // rezerwujemy miejsce na nowy element kolejki
    queue new_queue=malloc(sizeof(struct node));
    // nadajemu mu wartosc
    new_queue->value=value;
    // jest on ostatni wiec nic nie wskazuje
    new_queue->next=NULL;
    // jesli nie ma innego elementu w kolejce
    if((isEmptyFIFO(*ptr))){
        *ptr=malloc(sizeof(struct fifo_pointers));
        // nowy element jest jednoczesnie glowa i ogonem
        (*ptr)->head=new_queue;
        (*ptr)->tail=new_queue;       
    }
    // jesli jest juz jakis element w kolejce
    else{
        // ogon kolejki przed zmiana musi wskazywac nowy element
        (*ptr)->tail->next=new_queue;
        // nowym ogonem staje sie nowy element
        (*ptr)->tail=new_queue;
    } 
    printf("Dodano: %d\n",(*ptr)->tail->value);
}

void findFIFO(fifo ptr,int value){
    // licznik miejsca
    int i=1;
    // jesli kolejka jest pusta
    if(isEmptyFIFO(ptr)){
        printf("Kolejka jest pusta\n");
    }
    else{
        // element ktory jest na poczatku kolejki
        queue help=ptr->head;
        // dopoki wartosc elementu nie jest rowna szukanej wartosci
        while(help->value!=value){
            // przeskakujemy na kolejny element jesli istnieje
            if(help->next!=NULL){
                help=help->next;
                // zwiekszamy licznik
                i++;
            }
            else{
                printf("Nie ma takiego elementu: %d\n",value);
                return;
            }
        }
        // jesli wyszlismy z petli znaczy ze znalezlismy szukana wartosc
        printf("Element %d znajduje się na pozycji %d\n",value,i-1);
    }
}

void remFIFO(fifo* ptr){
    // jesli kolejka jest pusta
    if(isEmptyFIFO(*ptr)){
        printf("Kolejka jest pusta\n");
    }
    else{
        // usuwany element to glowa
        queue delete=(*ptr)->head;
        // poczatek kolejki wskazuje teraz na drugi element
        (*ptr)->head=delete->next;
        int value=delete->value;
        // usuwamy pierwszy element
        free(delete);
        printf("Usunięto %d\n",value);
    }
}

bool isEmptyFIFO(fifo ptr){
    // jesli nasz wskaznik jesy nullem
    if(ptr==NULL){
        return true;
    }
    return false;
}

void addLIFO(lifo* ptr, int value){
    // rezerwujemy miejsce na nowy element kolejki
    queue new_queue=malloc(sizeof(struct node));
    // nadajemu mu wartosc
    new_queue->value=value;
    // jesli nie ma innego elementu w kolejce
    if((isEmptyLIFO(*ptr))){
       *ptr=malloc(sizeof(struct lifo_pointers));
        // nowy element jest glowa
        (*ptr)->head=new_queue;  
        // nowy element na nic nie wskazuje
        new_queue->next=NULL;       
    }
    // jesli jest juz jakis element w kolejce
    else{
        // nowy element wskazuje na glowe kolejki
        queue help=new_queue;
        new_queue->next=(*ptr)->head;
        // nowy element staje sie nowa glowa kolejki
        (*ptr)->head=help;
    } 
    printf("Dodano: %d\n",(*ptr)->head->value);
}

void findLIFO(lifo ptr,int value){
    // licznik miejsca
    int i=1;
    // jesli kolejka jest pusta
    if(isEmptyLIFO(ptr)){
        printf("Kolejka jest pusta\n");
    }
    else{
        // element ktory jest na poczatku kolejki
        queue help=ptr->head;
        // dopoki wartosc elementu nie jest rowna szukanej wartosci
        while(help->value!=value){
            // przeskakujemy na kolejny element jesli istnieje
            if(help->next!=NULL){
                help=help->next;
                // zwiekszamy licznik
                i++;
            }
            else{
                printf("Nie ma takiego elementu: %d\n",value);
                return;
            }
        }
        // jesli wyszlismy z petli znaczy ze znalezlismy szukana wartosc
        printf("Element %d znajduje się na pozycji %d\n",value,i-1);
    }
}

void remLIFO(lifo* ptr){
    // jesli kolejka jest pusta
    if(isEmptyLIFO(*ptr)){
        printf("Kolejka jest pusta\n");
    }
    else{
        // usuwany element to glowa
        queue delete=(*ptr)->head;
        // poczatek kolejki wskazuje teraz na drugi element
        (*ptr)->head=delete->next;
        int value=delete->value;
        // usuwamy pierwszy element
        free(delete);
        printf("Usunięto %d\n",value);
    }
}

bool isEmptyLIFO(lifo ptr){
    // jesli nasz wskaznik jesy nullem
    if(ptr==NULL){
        return true;
    }
    return false;
}


int main(){
    fifo ptrFIFO=NULL;
    lifo ptrLIFO=NULL;
    printf("FIFO\n");
    for(int i=1;i<=100;i++){
        addFIFO(&ptrFIFO,i);
    }
    for(int i=1;i<=100;i++){
        remFIFO(&ptrFIFO);
    }
    printf("LIFO\n");
    for(int i=1;i<=100;i++){
       addLIFO(&ptrLIFO,i);
    }
    for(int i=1;i<=100;i++){
       remLIFO(&ptrLIFO);
    }
    return 0;
}