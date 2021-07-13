#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list2.h"

void add(list* ptr,int value){
    list new=malloc(sizeof(struct node));
    new->value=value;
    // jesli lista jest pusta
    if(*ptr==NULL){
        // element poprzedni i nastepny to ten sam element 
        new->previous=new;
        new->next=new;
    }
    else{
        // poprzedni element wstawianego elementu to poprzedni element starego pierwszego elementu 
        new->previous=(*ptr)->previous;
        // nastepny element "ostatniego" elementu to wstawiany element 
        new->previous->next=new;
        // nastepny element wstawianego elementu to stary pierwszy element 
        new->next=*ptr; 
        // poprzedni element starego pierszego elementu to wstawiany element
        (*ptr)->previous=new;
         
    }
    *ptr=new;
    //printf("Dodano %d\n",(*ptr)->value);
}

int find(list ptr,int value){
    int i=1;
    if(isEmpty(ptr)){
        //printf("Lista jest pusta\n");
        return 0;
    }
    else{
        // wskaznik na pierwszy element zapamietujemy aby sprawdzac czy przeszlismy juz cala liste 
        list help=ptr;
        while(ptr->value!=value){
            if(ptr->next!=help){
                ptr=ptr->next;
                i++;
            }
            else{
                // printf("Nie ma takiego elementu: %d\n",value);
                return -1;
            }
        }
        // printf("Element o wartości: %d znajduje się na pozycji: %d",value,i-1);
        return i;
    }
}

void rem(list* ptr, int position){
    if(position<0){
      //  printf("Nie ma takiej pozycji\n");
        return;
    }
    if(position==0){
        // zapamiętujemy wartość usuwanego elementu 
        int value=(*ptr)->value;
        // wskaźnik na następny element
        list tmp=(*ptr)->next;
        // następny element jako poprzedni wskazuje poprzedni element usuwanego elementu 
        tmp->previous=(*ptr)->previous;
        // poprzedni element usuwanego elementu jako nastepny wskazuje nastepny element elementu usuwanego
        (*ptr)->previous->next=tmp;
        free(*ptr);
        *ptr=tmp;
      //  printf("Usunieto element o indeksie: %d i wartosci: %d\n",position,value);
        return;      
    }
    list help=*ptr;
    // sluzy do sprawdzenia czy przeszlismy cala liste
    list check=*ptr;
    // zatrzymujemy sie na elemencie do usuniecia
    for(int i=0;i<position;i++){
        if(help->next!=check){
            help=help->next;
        }
        else{
         //   printf("Nie ma takiej pozycji\n");
            return;
        }
    }
    // zapamietujemy wartosc
    int value=help->value;
    // poprzedni element nastepnego elementu to poprzedni element elementu usuwanego
    help->next->previous=help->previous;
    // nastepny element poprzedniego elementu elementu usuwanego to nastepny element elementu usuwanego
    help->previous->next=help->next;
    free(help);
   // printf("Usunieto element o indeksie: %d i wartosci: %d\n",position,value);   
}

bool isEmpty(list ptr){
    if(ptr==NULL){
        return true;
    }
    return false;
}

list merge(list l1, list l2){
    // wskaznik na poczatek l1
    list merged=l1;
    // do sprawdzenia czy przeszlismy cala l1
    list check1=l1;
    // idziemy do "konca" l1
    while(l1->next!=check1){
        l1=l1->next;
    }
    // nastepny element ostatniego elementu l1 to pierwszy element l2
    l1->next=l2;
    // poprzedni element pierwszego elementu l2 to ostatni element l1
    l1->next->previous=l1;
    // do sprawdzenia czy przeszlismy cala l2
    list check2=l2;
    // idziemy "do konca" l2
    while(l2->next!=check2){
        l2=l2->next;
    }
    // nastepny element ostatniego elementu l2 to pierwszy element l1
    l2->next=check1;
    // poprzedni element pierwszego elementu l1 to ostatni element l2
    merged->previous=l2;
    return merged;
}

void printList(list ptr){
    list check=ptr;
    while(ptr->next!=check){
        printf("%d\n",ptr->value);
        ptr=ptr->next;
    }
    printf("%d\n",ptr->value);
}

void printListSecond(list ptr){
    list check=ptr;
    while(ptr->previous!=check){
        printf("%d\n",ptr->value);
        ptr=ptr->previous;
    }
    printf("%d\n",ptr->value);
}

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
    int avgCon1=0;
    int avgCon2=0;
    int avgCon3=0;
    int avgRand=0;
    for(int i=0;i<1000;i++){
        t[i]=i+1;
    }
    for(int j=0;j<100;j++){
        list ptr=NULL;
        randomize(t,1000);
        for(int i=0;i<1000;i++){
            add(&ptr,t[i]);
        }
        avgCon1+=find(ptr,103);
        avgCon2+=find(ptr,12);
        avgCon3+=find(ptr,654);
        avgRand+=find(ptr,1+rand()%1000);
    }
    printf("Ten sam 1: %d\n",avgCon1/100);
    printf("Ten sam 2: %d\n",avgCon2/100);
    printf("Ten sam 3: %d\n",avgCon3/100);
    printf("Losowy: %d\n",avgRand/100);
    list ptr1=NULL;
    list ptr2=NULL;
    add(&ptr1,50);
    add(&ptr1,502);
    add(&ptr1,427);
    add(&ptr1,138);
    add(&ptr2,212);
    add(&ptr2,933);
    rem(&ptr1,1);
    add(&ptr2,125);
    rem(&ptr2,0);
    add(&ptr2,228);
    printf("Lista 1:\n");
    printList(ptr1);
    printf("Lista 2:\n");
    printList(ptr2);
    list merged=merge(ptr1,ptr2);
    printf("Po złączeniu:\n");
    printf("NEXT:\n");
    printList(merged);
    printf("PREVIOUS:\n");
    printListSecond(merged);      
    return 0;
}