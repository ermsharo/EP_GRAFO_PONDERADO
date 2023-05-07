#include <stdio.h>
#include "linkedlist.c"

int main() {
    struct LinkedList* list = createLinkedList();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    printList(list);
    return 0;
}






