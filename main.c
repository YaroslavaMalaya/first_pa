#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    char value;
    struct Node* next;
};

struct LinkedList{
    struct Node* head;
    struct Node* current;
};

void addCharElement(struct LinkedList* list, const char elements[1000])
{
    int i = 0;
    while (elements[i] != '\n')
    {
        if (list->head == NULL)
        {
            list->head = (struct Node*)malloc(sizeof(struct Node));
            list->head->value = elements[i];
            list->head->next = NULL;
            list->current = list->head;
        }
        else
        {
            list->current->next = (struct Node*)malloc(sizeof(struct Node));
            list->current->next->value = elements[i];
            list->current->next->next = NULL;
            list->current = list->current->next;
        }
        i++;
    }
//    list->current->next = (struct Node*)malloc(sizeof(struct Node));
//    list->current->next->value = '\0';
//    list->current->next->next = NULL;
//    list->current = list->current->next;
}

void addNewLine(struct LinkedList* list){
    if (list->head == NULL)
    {
        list->head = (struct Node*)malloc(sizeof(struct Node));
        list->head->value = '\n';
        list->head->next = NULL;
        list->current = list->head;
    }
    else
    {
        list->current->next = (struct Node*)malloc(sizeof(struct Node));
        list->current->next->value = '\n';
        list->current->next->next = NULL;
        list->current = list->current->next;
    }
}

void saveTextToFile(struct LinkedList* list, char* fileName)
{
    FILE* file = fopen(fileName, "a");
    struct Node* current = list->head;
    while (current != NULL)
    {
        fputc(current->value, file);
        current = current->next;
    }
    fclose(file);
}

void loadTextFromFile(struct LinkedList* list, char* fileName)
{
    // clear linked list (myList)
    struct Node* current = list->head;
    while (current != NULL)
    {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->current = NULL;

    FILE* file = fopen(fileName, "r");
    char block[1000];
    while (fgets(block, sizeof(block), file) != NULL)
    {
        addCharElement(list, block);
    }
    fclose(file);
}

void printLinkedList(struct LinkedList* list)
{
    struct Node* current = list->head;
    while (current != NULL)
    {
        printf("%c", current->value);
        current = current->next;
    }
}

int main()
{
    int command;
    struct LinkedList myList;
    myList.head = NULL;
    myList.current = NULL;
    char input[1000];
    char fileName[100];

    printf("All commands:\n1-enter new text.\n2-start the new line.\n3-saving the information to your file."
           "\n4-loading the information from your file.\n5-print the current text to console.\n6-insert the text by line and symbol index."
           "\n7-search by word.");
    while (1)
    {
        printf("\nChoose the command:\n");
        scanf("%d", &command);
        switch (command)
        {
            case 1:
                getchar(); // delete the new line character left in the buffer after typing
                printf("Enter text to append (please, no more than 1000 characters): ");
                fgets(input, sizeof(input), stdin);
                addCharElement(&myList, input);
                // printf("%s", input);
                printLinkedList(&myList);
                break;
            case 2:
                addNewLine(&myList);
                printf("New line is started.");
                break;
            case 3:
                printf("Enter the file name for saving: ");
                scanf("%s", fileName);
                saveTextToFile(&myList, fileName);
                printf("Text has been saved successfully.");
                break;
            case 4:
                printf("Enter the file name for loading: ");
                scanf("%s", fileName);
                if (fileName[0] != 0)
                {
                    loadTextFromFile(&myList, fileName);
                    printf("Text has been loaded successfully.");
                    break;
                }
                else
                {
                    printf("Choose command 3.");
                }
                break;
            case 5:
                printLinkedList(&myList);
                break;
            case 6:
                printf("Choose line and index: ");
                printf("Enter text to insert: ");
                break;
            case 7:
                printf("Enter text to search: ");
                printf("Text is present in this position: ");
                break;
            default:
                printf("The command is not implemented.");
                break;
        }
    }
}