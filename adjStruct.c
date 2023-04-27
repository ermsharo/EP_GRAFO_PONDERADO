#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdjNode {
    char* value;
    struct AdjNode* next;
} AdjNode;

void addAdjNode(AdjNode** head, char* data) {
    AdjNode* newNode = (AdjNode*) malloc(sizeof(AdjNode));
    newNode->value = (char*) malloc((strlen(data) + 1) * sizeof(char));
    strcpy(newNode->value, data);
    newNode->next = *head;
    *head = newNode;
}

void printAdjList(AdjNode* head) {
    AdjNode* current = head;
    while (current != NULL) {
        printf("%s -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeAdjList(AdjNode* head) {
    AdjNode* current = head;
    while (current != NULL) {
        AdjNode* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

int main() {
    AdjNode* head = NULL;
    addAdjNode(&head, "world");
    addAdjNode(&head, "hello");
    printAdjList(head);
    freeAdjList(head);
    return 0;
}