#include <stdio.h>
#include <stdlib.h>

typedef struct InnerNode {
    char value;
    struct InnerNode* next;
} InnerNode;

typedef struct OuterNode {
    InnerNode* innerList;
    struct OuterNode* next;
} OuterNode;

void addInnerNode(InnerNode** head, char data) {
    InnerNode* newNode = (InnerNode*) malloc(sizeof(InnerNode));
    newNode->value = data;
    newNode->next = *head;
    *head = newNode;
}

void addOuterNode(OuterNode** head, InnerNode* innerList) {
    OuterNode* newNode = (OuterNode*) malloc(sizeof(OuterNode));
    newNode->innerList = innerList;
    newNode->next = *head;
    *head = newNode;
}

void printDataStructure(OuterNode* head) {
    OuterNode* currentOuter = head;
    while (currentOuter != NULL) {
        InnerNode* currentInner = currentOuter->innerList;
        printf("(");
        while (currentInner != NULL) {
            printf("%c", currentInner->value);
            if (currentInner->next != NULL) {
                printf("->");
            }
            currentInner = currentInner->next;
        }
        printf(")");
        if (currentOuter->next != NULL) {
            printf("->");
        }
        currentOuter = currentOuter->next;
    }
    printf("\n");
}

void freeDataStructure(OuterNode* head) {
    OuterNode* currentOuter = head;
    while (currentOuter != NULL) {
        InnerNode* currentInner = currentOuter->innerList;
        while (currentInner != NULL) {
            InnerNode* next = currentInner->next;
            free(currentInner);
            currentInner = next;
        }
        OuterNode* next = currentOuter->next;
        free(currentOuter);
        currentOuter = next;
    }
}

int main() {
    InnerNode* innerList1 = NULL;
    addInnerNode(&innerList1, 'c');
    addInnerNode(&innerList1, 'b');
    addInnerNode(&innerList1, 'a');
    
    InnerNode* innerList2 = NULL;
    addInnerNode(&innerList2, 'f');
    addInnerNode(&innerList2, 'e');
    addInnerNode(&innerList2, 'd');
    
    InnerNode* innerList3 = NULL;
    addInnerNode(&innerList3, 'i');
    addInnerNode(&innerList3, 'h');
    addInnerNode(&innerList3, 'g');
    
    OuterNode* outerList = NULL;
    addOuterNode(&outerList, innerList1);
    addOuterNode(&outerList, innerList2);
    addOuterNode(&outerList, innerList3);
    
    printDataStructure(outerList);
    freeDataStructure(outerList);
    return 0;
}
