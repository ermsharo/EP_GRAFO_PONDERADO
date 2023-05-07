#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LENGTH 1000
#define vertex int

struct Node
{
    char label[MAX_LENGTH];
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insert(int x)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = head;
    head = temp;
}

void deleteAtIndex(int index)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;

    if (index == 0)
    {
        head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < index - 1; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Index out of range.\n");
        return;
    }

    struct Node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

int getValueAtIndex(int index)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return -1;
    }

    struct Node *temp = head;

    for (int i = 0; temp != NULL && i < index; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Index out of range.\n");
        return -1;
    }

    return temp->data;
}

void printList()
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void splitString(char *str, char delimiter)
{
    char *token = strtok(str, &delimiter);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, &delimiter);
    }
}

int getListSize()
{
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int read_file_lines(const char *filename, char lines[][MAX_LENGTH])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return -1;
    }

    int line_count = 0;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, file))
    {
        // remove newline character from buffer
        buffer[strcspn(buffer, "\n")] = '\0';

        // copy buffer to current line in lines array
        strcpy(lines[line_count], buffer);
        line_count++;

        // break out of loop if blank line is encountered
        if (buffer[0] == '\0')
        {
            break;
        }
    }

    fclose(file);

    return line_count;
}

void readInputFile(const char *filename)
{

    char lines[1000][MAX_LENGTH];
    int line_count = read_file_lines(filename, lines);

    if (line_count == -1)
    {
        printf("Unable to open file.\n");
        return 1;
    }

    // Iniciando o novo grafo

    // print out each line in the lines array
    for (int i = 0; i < line_count; i++)
    {

        if (i == 0)
        {
            printf("[ primeiro ] %s\n ", lines[i]);
            // Pega o primeiro item
        }

        else if (i == line_count - 1)
        {
            // Pega o utlimo item
            printf(" [ultimo] %s\n", lines[i]);
        }
        else
        {
            printf("%s\n", lines[i]);
        }
    }

    //    imprimeGrafo(g);
}

void push(int x)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = x;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
}

int main()
{
    // push(1);
    // push(2);
    // push(3);
    // printf("Initialized list: ");
    // printList();
    // printf("Size of list: %d\n", getListSize());
    // printf("Value at index 2: %d\n", getValueAtIndex(2));
    // deleteAtIndex(2);

    // printList();

    readInputFile("input.txt");
    return 0;
}