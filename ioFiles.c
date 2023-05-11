#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000
#define MAX_SIZE 100000



struct listNode
{
    char *data;
    int index;
    struct listNode *next;
};


void remove_last_char(char **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        int len = strlen(arr[i]);
        if (len > 0) // make sure the string is not empty
        {
            arr[i][len - 1] = '\0'; // remove last character
        }
    }
}


char **remove_nulls(char *arr[], int size, int *new_size)
{
    char **new_arr = (char **)malloc(size * sizeof(char *));
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != NULL)
        {
        
            new_arr[j++] = arr[i];
        }
    }
    *new_size = j;
    return new_arr;
}

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

void print_list(struct listNode *head, char *label, Graph g)
{
    struct listNode *temp = head;
    while (temp != NULL)
    {
        //printf("%s %s ", temp->data, label);
        if(strcmp(temp->data, "empty") != 0){
         GRAPHinsertArcByLabel(g, temp->data, label);
        }
       
        temp = temp->next;
    }
}

char **getValidStrings(char **arr, int size) {
    int validCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i][0] != '\0') {
            validCount++;
        }
    }

    char **validArr = (char **)calloc(validCount, sizeof(char *));
    for (int i = 0, j = 0; i < size && j < validCount; i++) {
        if (arr[i][0] != '\0') {
            validArr[j] = (char *)calloc(strlen(arr[i]) + 1, sizeof(char));
            strcpy(validArr[j], arr[i]);
            j++;
        }
    }

    return validArr;
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

void print_string_array(char **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" (%s) ->", arr[i]);
    }
}
char *remove_last_element(const char *str)
{
    int len = strlen(str);

    if (len == 0)
    {
        char *result = malloc(1);
        result[0] = '\0';
        return result;
    }

    int last_non_space = len - 1;
    while (last_non_space >= 0 && str[last_non_space] == ' ')
    {
        last_non_space--;
    }

    int second_last_non_space = last_non_space - 1;
    while (second_last_non_space >= 0 && str[second_last_non_space] == ' ')
    {
        second_last_non_space--;
    }

    char *result = malloc(second_last_non_space + 2);
    if (result == NULL)
    {
        return NULL;
    }

    strncpy(result, str, second_last_non_space + 1);
    result[second_last_non_space + 1] = '\0';

    return result;
}

char **getWordsEndingWith(char **array, char endChar)
{
    int size = sizeof(array) / sizeof(char *);
    char **result = (char **)malloc(size * sizeof(char *));
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        //printf(" \n -> %s ", array[i]);
        int len = strlen(array[i]);

        if (array[i][len - 1] == endChar)
        {

            result[count] = array[i];
            //printf("-> %s ", result[count]);
            count++;
        }
    }

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
                //printf("Failed to allocate memory\n");
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

    char **new_arr = (char **)malloc((size - 2) * sizeof(char *));

    for (int i = 1; i < size - 1; i++)
    {
        new_arr[i - 1] = strdup(arr[i]);
    }

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
    }
}

void remove_element_at_index(char **arr, int *len, int index)
{

    for (int i = index; i < *len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    (*len)--;
}



char **filter_by_ending_char(char **arr, int size, char c, int *new_size)
{

    char **new_arr = malloc(size * sizeof(char *));
    if (new_arr == NULL)
    {

        *new_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i][strlen(arr[i]) - 1] == c)
        {
            new_arr[count] = malloc(strlen(arr[i]) + 1);
            if (new_arr[count] == NULL)
            {

                for (int j = 0; j < count; j++)
                {
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

    *new_size = count;
    return new_arr;
}

char **add_array_label(char **array, char endChar, int size)
{
    char **result = (char **)malloc(size * sizeof(char *));

    for (int i = 0; i < size; i++)
    {
        int len = strlen(array[i]);

        if (array[i][len - 1] == endChar)
        {
            result[i] = "adj";
        }
        else
        {
            result[i] = array[i];
        }
    }

    return result;
}

int get_array_size(char **arr)
{
    int size = 0;

    while (arr[size] != NULL)
    {
        size++;
    }
    return size;
}

void add_string_to_array(char ***arr_ptr, char *str)
{

    int size = 0;
    char **arr = *arr_ptr;
    while (arr[size] != NULL)
    {
        size++;
    }

    char *new_str = malloc(strlen(str) + 1);
    strcpy(new_str, str);

    *arr_ptr = realloc(arr, (size + 2) * sizeof(char *));
    (*arr_ptr)[size] = new_str;
    (*arr_ptr)[size + 1] = NULL;
}

void add_string_if_last_element_matches(char ***arr_ptr, char *last_element, char *str_to_add)
{

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

char **insert_new_element(char **arr, int size)
{
    char **new_arr = malloc(MAX_SIZE * sizeof(char *));
    int new_arr_size = 0;

    for (int i = 0; i < size; i++)
    {

        new_arr[new_arr_size++] = arr[i];

        if (i < size - 1 && strcmp(arr[i], arr[i + 1]) == 0)
        {

            new_arr[new_arr_size++] = "empty";
        }
    }

    new_arr[new_arr_size] = NULL;

    return new_arr;
}

char **get_elements_ending_with_colon(char **arr, int n)
{
    char **result = malloc((n + 1) * sizeof(char *));
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        int len = strlen(arr[i]);
        if (len > 0 && arr[i][len - 1] == ':')
        {
            result[j] = malloc(len + 1);
            strcpy(result[j], remove_last_element(arr[i]));
            j++;
        }
    }

    result[j] = NULL;
    result = realloc(result, (j + 1) * sizeof(char *));
    return result;
}

char **remove_char(char **arr, int arr_size, char c)
{
    char **new_arr = (char **)malloc(arr_size * sizeof(char *));
    for (int i = 0; i < arr_size; i++)
    {
        int len = strlen(arr[i]);
        new_arr[i] = (char *)malloc((len + 1) * sizeof(char));
        int j = 0;
        for (int k = 0; k < len; k++)
        {
            if (arr[i][k] != c)
            {
                new_arr[i][j] = arr[i][k];
                j++;
            }
        }
        new_arr[i][j] = '\0';
    }
    return new_arr;
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
    int adjListSize = atoi(words[0]);
    int dinamicSize = originalNumWords;

    remove_element_at_index(words, &dinamicSize, originalNumWords);

    remove_element_at_index(words, &dinamicSize, 0);

    int adjSize;
    char **output = filter_by_ending_char(words, dinamicSize, ':', &adjSize);
    int new_output_size = 0;
    char **cleanOutput = remove_nulls(output, dinamicSize, &new_output_size);
    int size = sizeof(output) - 2;
    char **array_label = add_array_label(words, ':', dinamicSize);

    char **validArr = getValidStrings(output, adjListSize);
     //print_string_array(validArr, adjListSize);
    remove_last_char(validArr,adjListSize);
     // print_string_array(validArr, adjListSize);
    Graph g = GRAPHinit(adjListSize);
  
    setLabels(g, validArr, adjListSize);

    char **new_arr = insert_new_element(array_label, dinamicSize);
    int newArraySize = get_array_size(new_arr);

    char **clean_relations = remove_char(new_arr, newArraySize, ';');

    int new_size = 0;
    char **cleanedFit = remove_nulls(clean_relations, newArraySize, &new_size);
    add_string_if_last_element_matches(&cleanedFit, "adj", "empty");
    int new_size_after = 0;
    char **cleanedFitAfter = remove_nulls(clean_relations, newArraySize, &new_size_after);
   // printf(" \n \n \n ");
   // print_string_array(cleanedFitAfter,new_size_after);
    struct listNode *head = NULL;
    struct listNode *sublist_head = NULL;

    for (int i = 0; i < new_size_after; i++)
    {
        char *current_str = cleanedFitAfter[i];

        if (strcmp(current_str, "adj") == 0)
        {
            if (sublist_head != NULL)
            {
                insert_at_end(&head, sublist_head);
            }
            sublist_head = NULL;
        }
        else
        {

            insert_at_end(&sublist_head, current_str);
        }
    }

    if (sublist_head != NULL)
    {
        insert_at_end(&head, sublist_head);
    }

    struct listNode *temp = head;
    int sublist_number = 0;
    while (temp != NULL)
    {
        //printf(" \n %s: ", output[sublist_number]);
        print_list((struct listNode *)temp->data, validArr[sublist_number], g);
        temp = temp->next;
        sublist_number++;
    }

    free_list(head);

    executeKosarajuApproach(optionValue, g);
}

