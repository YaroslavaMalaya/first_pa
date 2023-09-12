#include <stdio.h>
#include <string.h>

int main()
{
    int command;
    char text[100];
    char text2[100];
    char fileName[100];
    char myText[100];
    int i = 0;
    int j = 0;
    FILE *fileSave;
    FILE *fileRead;

    while (1)
    {
        printf("\nChoose the command:\n");
        scanf("%d", &command);
        switch (command)
        {
            case 1:
                getchar(); // delete the new line character left in the buffer after typing
                printf("Enter text to append: ");
                if (text[0] != 0)
                {
                    fgets(text2, sizeof(text2), stdin);
                    while (text[j] != 0)
                        j++;
                    if (text[j - 1] == '\n')
                    {
                        text[j - 1] = '\0';
                    }
                    strcat(text, text2);
                }
                else
                    fgets(text, sizeof(text), stdin);
                printf("%s", text);
                j = 0;
                break;
            case 2:
                while (text[i] != 0)
                {
                    i++;
                }
                text[i] = '\n';
                //printf("%s", text);
                printf("New line is started.");
                i = 0;
                break;
            case 3:
                printf("Enter the file name for saving: ");
                scanf("%s", fileName);
                printf("\nText has been saved successfully.");
                break;
            case 4:
                printf("Enter the file name for loading: ");
                scanf("%s", fileName);
                if (fileName[0] != 0)
                {
                    fileSave = fopen(fileName, "a");
                    fprintf(fileSave, text);
                    fclose(fileSave);
                    printf("Text has been loaded successfully.");
                    break;
                }
                else
                {
                    printf("Choose command 3.");
                }
                break;
            case 5:
                if (fileName[0] != 0)
                {
                    fileRead = fopen(fileName, "r");
                    if (fileRead == NULL)
                    {
                        printf("Error opening file.");
                    }
                    else
                    {
                        while(fgets(myText, 100, fileRead)) {
                            printf("%s", myText);
                        }
                        fclose(fileRead);
                    }
                }
                else
                {
                    printf("Choose command 3.");
                }
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
    return 0;
}