#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char value;
    struct Node* next;
};

struct LinkedList{
    struct Node* head;
    struct Node* current;
};

void addCharElement(struct LinkedList* list, const char elements[100]){
    int i = 0;
    while (elements[i] != '\n')
    {
        // if linked list is empty, create the first node (head, current) and assign the value
        if (list->head == NULL)
        {
            list->head = (struct Node*)malloc(sizeof(struct Node)); // allocating memory for a new Node in the linked list
            list->head->value = elements[i];
            list->head->next = NULL;
            list->current = list->head;
        }
        else
        {
            // if linked list isn`t empty, crete next new node after current and assign the value
            list->current->next = (struct Node*)malloc(sizeof(struct Node)); // allocating memory for a new Node in the linked list
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
    // if linked list is empty, create the first node (head, current) and assign the value \n (new line)
    if (list->head == NULL)
    {
        list->head = (struct Node*)malloc(sizeof(struct Node));
        list->head->value = '\n';
        list->head->next = NULL;
        list->current = list->head;
    }
    else
    {
        // if linked list isn`t empty, create next new node and assign the value \n (new line)
        list->current->next = (struct Node*)malloc(sizeof(struct Node));
        list->current->next->value = '\n';
        list->current->next->next = NULL;
        list->current = list->current->next;
    }
}

void saveTextToFile(struct LinkedList* list, char* fileName)
{
    FILE* file = fopen(fileName, "a");
    struct Node* current = list->head; // move to the beginning linked list
    while (current != NULL)
    {
        fputc(current->value, file); // append each value to the file while current node has it
        current = current->next;
    }
    fclose(file);
}

void loadTextFromFile(struct LinkedList* list, char* fileName)
{
    // clear linked list (myList) for rewriting
    struct Node* current = list->head;
    while (current != NULL)
    {
        struct Node* next = current->next;
        free(current); // freeing memory that was previously allocated using the malloc function
        current = next;
    }
    list->head = NULL;
    list->current = NULL;

    FILE* file = fopen(fileName, "r");
    char block[100];
    int i = 0;

    // while file contains data (100 characters in each step of while)
    while (fgets(block, sizeof(block), file) != NULL)
    {
        while (block[i] != NULL)
        {
            // the same as addCharElement();
            if (list->head == NULL)
            {
                list->head = (struct Node*)malloc(sizeof(struct Node));
                list->head->value = block[i];
                list->head->next = NULL;
                list->current = list->head;
            }
            else
            {
                list->current->next = (struct Node*)malloc(sizeof(struct Node));
                list->current->next->value = block[i];
                list->current->next->next = NULL;
                list->current = list->current->next;
            }
            i++;
        }
        i = 0;
    }
    fclose(file);
}

void insertText(struct LinkedList* list, int lineIndex, int symbolIndex, char* text){
    if (lineIndex == 0 && symbolIndex == 0) // if user wants to write something at the beginning
    {
        list->current = list->head;
        addCharElement(list, text);
    }
    else
    {
        list->current = list->head;
        struct Node* previous = NULL;
        int currentLine = 0;
        int currentSymbol = 0;

        // find line that has the same index
        while (currentLine < lineIndex)
        {
            previous = list->current;
            list->current = previous->next; // the same as list->current = list->current->next;
            if (list->current == NULL)
            {
                printf("\nIncorrect line index."); // so the line does not exist
                break;
            }
            if (list->current->value == '\n')
            {
                currentLine++;
            }
        }

        // find symbol in the line that has the same index
        while (currentSymbol < symbolIndex)
        {
            previous = list->current;
            list->current = previous->next;
            if (list->current == NULL)
            {
                printf("\nIncorrect symbol index."); // so the symbol index does not exist
                break;
            }
            currentSymbol++;
        }

        struct Node* temp = NULL;
        temp = list->current->next; // remember the node that must then be added to the newly added node
        int i = 0;

        while (text[i] != '\n')
        {
            list->current->next = (struct Node*)malloc(sizeof(struct Node)); // allocating memory for a new Node in the linked list
            list->current->next->value = text[i];
            list->current->next->next = NULL;
            list->current = list->current->next;
            i++;
        }
        list->current->next = temp; // add the node with other connections that should be here
    }
}

void searchInText(struct LinkedList* list, const char* text){
    struct Node* current = list->head;
    int lineIndex = 0;
    int symbolIndex = 1;
    int textIndex = 0;
    int checkLength = 0;

    while (current != NULL)
    {
        if (current->value == '\n')
        {
            lineIndex++; // count line index
            symbolIndex = 0;
            textIndex = 0;
            checkLength = 0;
        }
        else if (current->value == text[textIndex])
        {
            textIndex++;
            checkLength++; // check how long this text

            if (text[textIndex] == '\n')
            {
                printf("line %d  symbol %d; ", lineIndex, symbolIndex - checkLength);
                // clear everything that was found and continue searching
                textIndex = 0;
                checkLength = 0;
            }
        }
        else if (current->value == text[0])
        {
            textIndex = 1;
            checkLength = 1;
        }
        else
        {
            textIndex = 0;
            checkLength = 0;
        }
        current = current->next; // move to the next node
        symbolIndex++; // count symbol index
    }
}

void printLinkedList(struct LinkedList* list){
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
    char input[100];
    char fileName[100];
    int lineIndex;
    int symbolIndex;
    char searchText[100];

    while (1)
    {
        system("clear"); // clear the console

        // describe all commands
        printf("\n\nAll commands:\n1-enter new text.\n2-start the new line.\n3-saving the information to your file."
               "\n4-loading the information from your file.\n5-print the current text to console.\n6-insert the text "
               "by line and symbol index.\n7-search by word.");

        printf("\nChoose the command:\n");
        scanf("%d", &command);
        switch (command)
        {
            case 1:
                getchar(); // delete the new line character left in the buffer after typing
                printf("Enter text to append (please, no more than 100 characters): ");
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
                if (fileName != NULL)
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
                scanf("%d %d", &lineIndex, &symbolIndex);
                getchar(); // delete the new line character left in the buffer after typing
                printf("Enter text to insert (please, no more than 100 characters): ");
                fgets(input, sizeof(input), stdin);
                insertText(&myList, lineIndex, symbolIndex, input);
                break;
            case 7:
                getchar(); // delete the new line character left in the buffer after typing
                printf("Enter text to search: ");
                fgets(searchText, sizeof(searchText), stdin);
                printf("Text is present in this position: ");
                searchInText(&myList, searchText);
                break;
            default:
                printf("The command is not implemented.");
                break;
        }
    }
}