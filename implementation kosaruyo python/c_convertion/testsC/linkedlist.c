


#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    bool visited;
    struct Node* next_element;
};

struct LinkedList {
    struct Node* head;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->visited = false;
    newNode->next_element = NULL;
    return newNode;
}

struct LinkedList* createLinkedList() {
    struct LinkedList* newLinkedList = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    newLinkedList->head = NULL;
    return newLinkedList;
}

struct Node* getHead(struct LinkedList* linkedList) {
    return linkedList->head;
}

bool isEmpty(struct LinkedList* linkedList) {
    return getHead(linkedList) == NULL;
}

bool insertAtHead(struct LinkedList* linkedList, int data) {
    struct Node* newNode = createNode(data);
    newNode->next_element = getHead(linkedList);
    linkedList->head = newNode;
    return true;
}

bool insertAtTail(struct LinkedList* linkedList, int data) {
    if (isEmpty(linkedList)) {
        return insertAtHead(linkedList, data);
    }
    struct Node* newNode = createNode(data);
    struct Node* temp = getHead(linkedList);
    while (temp->next_element != NULL) {
        temp = temp->next_element;
    }
    temp->next_element = newNode;
    return true;
}

void printList(struct LinkedList* linkedList) {
    if (isEmpty(linkedList)) {
        printf("List is empty\n");
        return;
    }
    printf("Printing list : ");
    struct Node* temp = getHead(linkedList);
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next_element;
    }
    printf("None\n");
}

int deleteAtHead(struct LinkedList* linkedList) {
    if (isEmpty(linkedList)) {
        return false;
    }
    int deleted = getHead(linkedList)->data;
    linkedList->head = getHead(linkedList)->next_element;
    return deleted;
}

bool delete(struct LinkedList* linkedList, int data) {
    if (getHead(linkedList)->data == data) {
        return deleteAtHead(linkedList);
    }
    struct Node* previous = NULL;
    struct Node* current = getHead(linkedList);
    while (current->next_element != NULL) {
        if (current->data == data) {
            previous->next_element = current->next_element;
            free(current);
            return true;
        }
        previous = current;
        current = current->next_element;
    }
    return false;
}

void pop(struct LinkedList* linkedList) {
    if (getHead(linkedList)== NULL) {
        printf("Nothing to pop\n");
        return;
    }
    if (getHead(linkedList)->next_element == NULL) {
        printf("Pop First : %d\n", getHead(linkedList)->data);
        deleteAtHead(linkedList);
        return;
    }
    struct Node* tempRef = getHead(linkedList);
    struct Node* previous = NULL;
    struct Node* current = getHead(linkedList);
    while (current->next_element != NULL) {
        previous = current;
        current = current->next_element;
    }
    printf("Poping : %d\n", previous->next_element->data);
    previous->next_element = NULL;
    linkedList->head = tempRef;
}

int main(void)
{
   LinkedList* list = createLinkedList();
   return 0;
}
