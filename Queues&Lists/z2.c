#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list1.h"

// dodawanie elementu
void add(list* ptr,int value){
    // nowy element
    list new=malloc(sizeof(struct node));
    // nadajemy wartosc nowemu elementowi
    new->value=value;
    // dodajemy go na poczatek, wiec wskazuje on na pierwszy element listy
    new->next=*ptr;
    // teraz nowy element jest pierwszym elementem listy
    *ptr=new;
    //printf("Dodano element: %d\n",(*ptr)->value);
}

// szukanie podanego elementu 
int find(list ptr,int value){
    // licznik wezlow
    int i=1;
    // jesli lista jest pusta
    if(isEmpty(ptr)){
        // printf("Lista jest pusta\n");
        return 0;
    }
    else{
        // dopoki nie znajdziemy elementu z szukana wartoscia
        while(ptr->value!=value){
            // jesli istnieje kolejny element to przelaczamy wskaznik na niego
            if(ptr->next!=NULL){
                ptr=ptr->next;
                i++;
            }
            else{
                // printf("Nie ma takiego elementu: %d\n",value);
                return -1;
            }
        }
        // printf("Znaleziono element: %d na miejscu: %d",value,i-1);
        return i;
    }
}

// usuwanie elementu z pola o podanym indeksie
void rem(list* ptr,int position){
    // jesli pozycja jest mniejsza od 0
    if(position<0){
     //   printf("Nie ma takiej pozycji\n");
        return;
    }
    // jesli pozycja jest rowna 0
    if(position==0){
        // bierzemy wartosc pierwszego elementu
        int value=(*ptr)->value;
        // nasz ptr wskazuje teraz na drugi element, pierwszy usuwamy
        list tmp=(*ptr)->next;
        free(*ptr);
        (*ptr)=tmp;
     //   printf("Usunieto element o indeksie: %d i wartosci: %d\n",position,value);
        return;      
    }
    list help=*ptr;
    // chcemy aby help wskazywalo jeden element przed usuwanym
    for(int i=0;i<position-1;i++){
        if(help->next!=NULL){
            help=help->next;
        }
        else{
         //   printf("Nie ma takiej pozycji\n");
            return;
        }
    }
    // jesli istnieje nastepny element
    if(help->next!=NULL){   
        int value=help->next->value;
        // help wskazuje teraz na element na ktory wskazuje usuwany element
        list tmp=help->next->next;
        free(help->next);
        help->next=tmp;
     //   printf("Usunieto element o indeksie: %d i wartosci: %d\n",position,value);
    }
    else{
     //   printf("Nie ma takiej pozycji\n");
    }
}

// czy lista jest pusta
bool isEmpty(list ptr){
    if(ptr==NULL){
        return true;
    }
    return false;
}

// scalanie dwoch list
list merge(list l1,list l2){
    // wskaznik na poczatek l1
    list merged=l1;
    // poruszamy sie na koniec l1
    while(l1->next!=NULL){
        l1=l1->next;
    }
    // ostatni element l1 wskazuje na poczatek l2
    l1->next=l2;
    return merged;
}

// wypisywanie listy
void printList(list ptr){
    // poruszamy sie po calej liscie
    while(ptr!=NULL){
        printf("%d\n",ptr->value);
        ptr=ptr->next;
    }
}

// funkcja ustawiajaca elementy w tablicy w losowej kolejnosci
void randomize(int t[],int n){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        int j=1+rand()%n;
        int tmp=t[i];
        t[i]=t[j];
        t[j]=tmp;
    }
}

int main(){
    srand(time(NULL));
    int t[1000];
    // suma przejsc po elementach listy aby znalezc dany element
    int avgCon1=0;
    int avgCon2=0;
    int avgCon3=0;
    int avgRand=0;
    // tablica od 1 do 1000
    for(int i=0;i<1000;i++){
        t[i]=i+1;
    }
    // petla do testowania
    for(int j=0;j<100;j++){
        // za kazdym razem zerujemy liste i losujemy nowy uklad liczb w tablicy
        list ptr=NULL;
        randomize(t,1000);
        // wypelniamy liste
        for(int i=0;i<1000;i++){
            add(&ptr,t[i]);
        }
        // dodajemy miejsce wystapienia danego element
        avgCon1+=find(ptr,123);
        avgCon2+=find(ptr,1);
        avgCon3+=find(ptr,984);
        avgRand+=find(ptr,1+rand()%1000);
    }
    // wypisujemy srednia
    printf("Ten sam 1: %d\n",avgCon1/100);
    printf("Ten sam 2: %d\n",avgCon2/100);
    printf("Ten sam 3: %d\n",avgCon3/100);
    printf("Losowy: %d\n",avgRand/100);
    // tworzymy dwie nowe liste i dodajemy do nich pare elementow (ew.usuwamy dla testu)
    list ptr1=NULL;
    list ptr2=NULL;
    add(&ptr1,5);
    add(&ptr1,500);
    add(&ptr1,45);
    add(&ptr1,56);
    add(&ptr2,67);
    add(&ptr2,50);
    rem(&ptr1,3);
    add(&ptr2,189);
    add(&ptr2,228);
    rem(&ptr2,1);
    printf("Lista 1:\n");
    printList(ptr1);
    printf("Lista 2:\n");
    printList(ptr2);
    // tworzymy liste ktora jest ich polaczeniem
    list merged=merge(ptr1,ptr2);
    printf("Po złączeniu:\n");
    printList(merged);      
    return 0;
}