// References:
// - https://www.w3schools.com/c/c_structs.php
// - https://www.tutorialesprogramacionya.com/cya/detalleconcepto.php?punto=45&codigo=45&inicio=30

#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

void insertSorted(struct Node** listReference, int value){

    // Create a new node using dynamic memory.
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    if(newNode == NULL){
        printf("Error --> Memory allocation failed. \n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    // Empty list 
    if(*listReference == NULL || value < (*listReference)->data){
        newNode->next = *listReference;
        *listReference = newNode;
        return;
    }

    struct Node* current = *listReference;

    while(current->next != NULL && current->next->data < value){
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void printList (struct Node* listReference){
    printf("\n>> Ordered list: ");
    struct Node* current = listReference;

    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
}

void freeList(struct Node* listReference){
    printf("\nFreeing memory \n");
    struct Node* current = listReference;
    struct Node* temporalNode;

    while(current != NULL){
        temporalNode = current;
        current = current->next;
        free(temporalNode);
    }
}

void onStart(struct Node** list){
    int userValue, userQuantity;

    printf("Enter quantity of numbers: ");
    scanf("%d", &userQuantity);

    for(int i = 0; i < userQuantity; i++){
        printf("\nEnter a number %d: ", i + 1);
        scanf("%d", &userValue);

        insertSorted(list, userValue);
    }
}

int main (){

    // Variable initialization
    struct Node* list = NULL;

    printf("######################## ORDER LIST AND POINTERS IN C ######################## \n");

    // Insert values
    onStart(&list);

    // Ordered list
    printList(list);

    // Free memory
    freeList(list);

    printf("######################## END ORDER LIST AND POINTERS IN C ######################## \n");

    return 0;
}