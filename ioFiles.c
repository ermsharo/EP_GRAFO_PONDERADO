#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000
#define MAX_SIZE 100000

#include "StronglyConnectedComponents.c"
// #include "Grafo.c"

struct listNode
{
    char *data;
    int index;
    struct listNode *next;
};

void insert_at_end(struct listNode **head, char *value)
{
    struct listNode *new_listNode = (struct listNode *)malloc(sizeof(struct listNode));
    new_listNode->data = value;
    new_listNode->next = NULL;

    if (*head == NULL)
    {
        *head = new_listNode;
    }
    else
    {
        struct listNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_listNode;
    }
}

void print_list(struct listNode *head)
{
    struct listNode *temp = head;
    while (temp != NULL)
    {
        printf("%s ", temp->data);
        temp = temp->next;
    }
}

void free_list(struct listNode *head)
{
    while (head != NULL)
    {
        struct listNode *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}


void print_string_array(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        printf(" (%s) ->", arr[i]);
    }
}
char *remove_last_element(const char *str) {
    int len = strlen(str);

    if (len == 0) {
        // empty string, return a copy
        char *result = malloc(1);
        result[0] = '\0';
        return result;
    }

    // find the index of the last non-space character
    int last_non_space = len - 1;
    while (last_non_space >= 0 && str[last_non_space] == ' ') {
        last_non_space--;
    }

    // find the index of the second-to-last non-space character
    int second_last_non_space = last_non_space - 1;
    while (second_last_non_space >= 0 && str[second_last_non_space] == ' ') {
        second_last_non_space--;
    }

    // allocate a new string with the correct length
    char *result = malloc(second_last_non_space + 2);
    if (result == NULL) {
        // malloc failed, return NULL
        return NULL;
    }

    // copy the first n-1 characters to the new string
    strncpy(result, str, second_last_non_space + 1);
    result[second_last_non_space + 1] = '\0';

    return result;
}

char **getWordsEndingWith(char **array, char endChar)
{
    int size = sizeof(array) / sizeof(char *);
    char **result = (char **)malloc(size * sizeof(char *)); // Allocate memory for the result array
    int count = 0;                                          // Counter for the number of words that end with the specified character

    for (int i = 0; i < size; i++)
    {
        printf(" \n -> %s ", array[i]);
        int len = strlen(array[i]); // Get the length of the current string

        if (array[i][len - 1] == endChar)
        { // Check if the last character of the string matches the specified character

            // Allocate memory for the string in the result array
            result[count] = array[i];
            printf("-> %s ", result[count]); // Copy the string from the input array to the result array
            count++;                         // Increment the counter
        }
    }


    // result = (char **)realloc(result, count * sizeof(char *)); // Shrink the result array to fit the exact number of words that end with the specified character
    return result;
}

char **readWordsFromFile(const char *fileName, int *numWords)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Failed to open file %s\n", fileName);
        return NULL;
    }

    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int i = 0;
    char line[MAX_WORD_LENGTH * 3];
    while (fgets(line, sizeof(line), fp) != NULL && i < MAX_WORDS)
    {
        char *word = strtok(line, " \t\n\r");
        while (word != NULL && i < MAX_WORDS)
        {
            words[i] = (char *)malloc((strlen(word) + 1) * sizeof(char));
            if (words[i] == NULL)
            {
                printf("Failed to allocate memory\n");
                return NULL;
            }
            strcpy(words[i], word);
            i++;
            word = strtok(NULL, " \t\n\r");
        }
    }

    *numWords = i;

    fclose(fp);
    return words;
}

char ***split_array(char **arr, int arr_size, int *idx, int idx_size)
{
    char ***result = (char ***)malloc(idx_size * sizeof(char **));
    for (int i = 0; i < idx_size; i++)
    {
        int start = idx[i] + 1;
        int end = (i == idx_size - 1) ? arr_size : idx[i + 1];
        int len = end - start;

        result[i] = (char **)malloc((len + 1) * sizeof(char *));
        for (int j = 0; j < len; j++)
        {
            result[i][j] = (char *)malloc((strlen(arr[start + j]) + 1) * sizeof(char));
            strncpy(result[i][j], arr[start + j], strlen(arr[start + j]));
            result[i][j][strlen(arr[start + j])] = '\0';
        }
        result[i][len] = NULL;
    }

    return result;
}

char **remove_first_last(char **arr, int size)
{
    if (size <= 2)
    {
        return NULL;
    }

    // Allocate memory for the new array
    char **new_arr = (char **)malloc((size - 2) * sizeof(char *));

    // Copy elements from the original array to the new array
    for (int i = 1; i < size - 1; i++)
    {
        new_arr[i - 1] = strdup(arr[i]);
    }

    // Free memory of the original array
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return new_arr;
}

char **remove_index(char **arr)
{
    int input_length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < input_length; i++)
    {
        char *current_str = arr[i];
        printf("current string : %s ", current_str);

        // if (strcmp(current_str, "jump") == 0) {

        // } else {
        //     // int* current_int = (int*)malloc(sizeof(int));
        //     // *current_int = atoi(current_str);
        //     // insert_at_end(&sublist_head, current_str);
        // }
    }
}

void remove_element_at_index(char **arr, int *len, int index)
{
    // Shift all elements after the index one position to the left
    for (int i = index; i < *len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    // Decrement the length of the array
    (*len)--;
}

char *remove_last_char(const char *str)
{
    size_t len = strlen(str);
    char *new_str = malloc(len);
    strncpy(new_str, str, len - 1);
    new_str[len - 1] = '\0';
    return new_str;
}

char** filter_by_ending_char(char** arr, int size, char c, int* new_size)
{
    // Allocate memory for the new array
    char** new_arr = malloc(size * sizeof(char*));
    if (new_arr == NULL) {
        // Memory allocation failed
        *new_size = 0;
        return NULL;
    }

    // Loop through the original array and copy the strings that end with the specified character
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i][strlen(arr[i]) - 1] == c) {
            new_arr[count] = malloc(strlen(arr[i]) + 1);
            if (new_arr[count] == NULL) {
                // Memory allocation failed
                for (int j = 0; j < count; j++) {
                    free(new_arr[j]);
                }
                free(new_arr);
                *new_size = 0;
                return NULL;
            }
            strcpy(new_arr[count], arr[i]);
            count++;
        }
    }

    // Update the size of the new array and return it
    *new_size = count;
    return new_arr;
}

char **add_array_label(char **array, char endChar, int size)
{
    char **result = (char **)malloc(size * sizeof(char *)); // Allocate memory for the result array
                                                            // Counter for the number of words that end with the specified character

    for (int i = 0; i < size; i++)
    {
        int len = strlen(array[i]); // Get the length of the current string

        if (array[i][len - 1] == endChar)
        {                      // Check if the last character of the string matches the specified character
            result[i] = "adj"; // Increment the counter
        }
        else
        {
            result[i] = array[i];
        }
    }

    // result = (char **)realloc(result, count * sizeof(char *)); // Shrink the result array to fit the exact number of words that end with the specified character
    return result;
}


int get_array_size(char **arr)
{
    int size = 0;

    // Loop through the array until a NULL pointer is encountered
    while (arr[size] != NULL)
    {
        size++;
    }
    return size;
}

void add_string_to_array(char ***arr_ptr, char *str)
{
    // Calculate the size of the array
    int size = 0;
    char **arr = *arr_ptr;
    while (arr[size] != NULL)
    {
        size++;
    }

    // Allocate memory for the new string and copy it in
    char *new_str = malloc(strlen(str) + 1);
    strcpy(new_str, str);

    // Reallocate memory for the array and add the new string
    *arr_ptr = realloc(arr, (size + 2) * sizeof(char *));
    (*arr_ptr)[size] = new_str;
    (*arr_ptr)[size + 1] = NULL;
}


void add_string_if_last_element_matches(char ***arr_ptr, char *last_element, char *str_to_add)
{
    printf(" \n aqui esta \n addstring ->");
    char **arr = *arr_ptr;
    int size = 0;
    while (arr[size] != NULL)
    {
        size++;
    }
    if (size > 0 && strcmp(arr[size - 1], last_element) == 0)
    {
        add_string_to_array(arr_ptr, str_to_add);
    }
}



char** insert_new_element(char** arr, int size) {
  char** new_arr = malloc(MAX_SIZE * sizeof(char*));
  int new_arr_size = 0;

  for (int i = 0; i < size; i++) {
    // Add the current string to the new array
    new_arr[new_arr_size++] = arr[i];
    // Check if the next string is the same as the current one
    if (i < size - 1 && strcmp(arr[i], arr[i+1]) == 0) {
      // Add the new element to the new array
      new_arr[new_arr_size++] = "empty";
    }
  }

  // Null-terminate the new array
  new_arr[new_arr_size] = NULL;

  return new_arr;
}


char **get_elements_ending_with_colon(char **arr, int n) {
    char **result = malloc((n+1) * sizeof(char *));
    int j = 0;

    for (int i = 0; i < n; i++) {
        int len = strlen(arr[i]);
        if (len > 0 && arr[i][len-1] == ':') {
            result[j] = malloc(len + 1);
            strcpy(result[j], remove_last_element(arr[i]));
            j++;
        }
    }

    result[j] = NULL;
    result = realloc(result, (j+1) * sizeof(char *));
    return result;
}



void runBasedInput(char *filename)
{
    char **words;
    int originalNumWords;

    words = readWordsFromFile(filename, &originalNumWords);

    if (words == NULL)
    {
        printf("Failed to read words from file\n");
    }


    int optionValue = atoi(words[originalNumWords - 1]);

    int dinamicSize = originalNumWords;

    printf(" \n \n The words in the graph:\n");
    print_string_array(words, dinamicSize);
    remove_element_at_index(words,&dinamicSize,originalNumWords);
    printf(" \n Aqui esta \n ");
    print_string_array(words, dinamicSize);
    printf(" \n Aqui esta \n ");
    remove_element_at_index(words,&dinamicSize,0);
    print_string_array(words, dinamicSize);
    int adjSize;
    char **output = filter_by_ending_char(words, dinamicSize, ':',&adjSize);
    int size = sizeof(output) - 2;
    printf("\n adj array:");
    print_string_array(output, size);
    printf("\n  -> size of adj array is %i ", size - 1);
    printf("\n\nOutput array:\n");
    char **array_label = add_array_label(words, ':', dinamicSize);
    print_string_array(array_label, dinamicSize);
    char **new_arr = insert_new_element(array_label, dinamicSize);
    int newArraySize = get_array_size(new_arr);
    printf(" \n aqui esta o numero : %i \n",newArraySize);

    print_string_array(new_arr, newArraySize);
    add_string_if_last_element_matches(&new_arr, "adj", "empty");
    printf(" \n -> with empty:");
    print_string_array(new_arr, newArraySize+1);




    // print_string_array(array_label, newArraySize-1);
    // char** new_arr = insert_new_element(arr, size);
    // add_string_if_last_element_matches(&array_label, "adj", "empty");
    // printf("\n print string \n");
    // newArraySize = get_array_size(array_label);
    // print_string_array(array_label, newArraySize-2);
}

int main()
{
    printf("Ola mundo");
    // redirect_stdout_to_file("output.txt");

    runBasedInput("entrada.txt");

    return 0;
}
