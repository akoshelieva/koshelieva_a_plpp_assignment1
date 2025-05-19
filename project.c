#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_menu() {
    printf("Choose the command:\n");
    printf("1. Append text\n");
    printf("2. Start new line\n");
    printf("3. Save to file\n");
    printf("4. Load from file\n");
    printf("5. Print current text\n");
    printf("6. Insert text by line and index\n");
    printf("7. Search text\n");
    printf("0. Exit\n");
}
void clear_console() {
    system("cls");
}
int main() {
    char* text = (char*)malloc(1 * sizeof(char));
    text[0] = '\0';
    int capacity = 1;
    

    while (1) {
        if (clear_enabled) {
            clear_console();
        }
        print_menu();
        int command;
        scanf("%d", &command);
        getchar(); 

        if (command == 0) {
            break;
        }

        switch (command) {
        case 1: { 
            char buffer[1000];
            printf("Enter your text: ");
            fgets(buffer, 1000, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            int len = strlen(text);
            int new_text_len = strlen(buffer);
            if (len + new_text_len + 1 > capacity) {
                capacity = (len + new_text_len + 1) * 2;
                char* new_text = (char*)realloc(text, capacity * sizeof(char));
                if (new_text == NULL) {
                    printf("Memory allocation failed\n");
                    free(text);
                    return 1;
                }
                text = new_text;
            }
            strcat(text, buffer);
            printf("Text appended: %s\n", text);
            break;
        }
        case 2: { 
            int len = strlen(text);
            if (len + 2 > capacity) {
                capacity = (len + 2) * 2;
                char* new_text = (char*)realloc(text, capacity * sizeof(char));
                if (new_text == NULL) {
                    printf("Memory allocation failed\n");
                    free(text);
                    return 1;
                }
                text = new_text;
            }
            strcat(text, "\n");
            printf("You started a new line\n");
            break;
        }
        case 3: 
            char filename[100];
            printf("Enter the file name: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = '\0';
            FILE* file = fopen(filename, "w");
            if (file != NULL) {
                fputs(text, file);
                fclose(file);
                printf("Text saved to %s\n", filename);
            }
            else {
                printf("Error opening file\n");
            }
            break;
        }