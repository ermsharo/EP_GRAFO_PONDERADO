#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

typedef struct adjNode
{
    char value[120];
    struct adjNode *next;
} AdjNode;

char **split(char *str, char delim)
{
    int i, j, k;
    int count = 1;
    int len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == delim)
        {
            count++;
        }
    }
    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL)
    {
        return NULL;
    }
    j = 0;
    k = 0;
    for (i = 0; i < len + 1; i++)
    {
        if (str[i] == delim || str[i] == '\0')
        {
            result[j] = (char *)malloc((k + 1) * sizeof(char));
            if (result[j] == NULL)
            {
                return NULL;
            }
            strncpy(result[j], str + i - k, k);
            result[j][k] = '\0';
            k = 0;
            j++;
        }
        else
        {
            k++;
        }
    }
    return result;
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

void split_string(char *str, char delim, char **tokens, int *token_count)
{
    char *token = strtok(str, &delim);

    while (token != NULL)
    {
        tokens[*token_count] = token;
        (*token_count)++;
        token = strtok(NULL, &delim);
    }
}

void printList(AdjNode *head)
{
    while (head != NULL)
    {
        printf("%s ", head->value);
        head = head->next;
    }
    printf("\n");
}

void fillStructures()
{

    char lines[1000][MAX_LENGTH];
    int line_count = read_file_lines("entrada.txt", lines);
    if (line_count == -1)
    {
        printf("Unable to open file.\n");
        return 1;
    }

    for (int i = 0; i < line_count; i++)
    {
        // Precisamos pegar este string
        // printf("%s\n", lines[i]);
        char **arr = split(lines[i], ':');
        for (int j = 0; arr[j] != NULL; j++)
        {
            printf("%s\n ", arr[j]);
        }
        // Dividir os termos
        // Jogar o valor de adjacencia para uma estrutura
        // Jogar os demais valores para outra estrutura
    }
}

int main()
{
    fillStructures();

    return 0;
}