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
int get_position(char* text, int line, int index) {
    int current_line = 0, position = 0;
    if (line < 0 || index < 0) return -1;

    for (int i = 0; text[i] != '\0'; i++) {
        if (current_line == line) {
            if (position == index) return i;
            position++;
        }
        if (text[i] == '\n') {
            current_line++;
            position = 0;
        }
    }
    return -1; 
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
        case 4: {
            char filename[100];
            printf("Enter the file name: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = '\0';
            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error opening file\n");
            }
            else {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                fseek(file, 0, SEEK_SET);
                if (file_size + 1 > capacity) {
                    capacity = (file_size + 1) * 2;
                    char* new_text = (char*)realloc(text, capacity * sizeof(char));
                    if (new_text == NULL) {
                        printf("Memory allocation failed\n");
                        fclose(file);
                        free(text);
                        return 1;
                    }
                    text = new_text;
                }
                text[0] = '\0';
                if (file_size > 0 && fread(text, 1, file_size, file) != file_size) {
                    printf("Error reading file\n");
                    fclose(file);
                    break;
                }
                text[file_size] = '\0';
                fclose(file);
                printf("Text has been loaded successfully\n");
            }
            break;
        }
        case 5: { 
        }
        case 6: { 
            int line, index;
            printf("Choose line and index: ");
            scanf("%d %d", &line, &index);
            getchar();
            int position = get_position(text, line, index);
            if (position == -1) {
                printf("Invalid line or index\n");
                break;
            }
            char buffer[100];
            printf("Enter text: ");
            fgets(buffer, 100, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            int len = strlen(buffer);
            int text_len = strlen(text);
            if (text_len + len + 1 > capacity) {
                capacity = (text_len + len + 1) * 2;
                char* new_text = (char*)realloc(text, capacity * sizeof(char));
                if (new_text == NULL) {
                    printf("Memory allocation failed\n");
                    free(text);
                    return 1;
                }
                text = new_text;
            }
            for (int i = text_len; i >= position; i--) {
                text[i + len] = text[i];
            }
            for (int i = 0; i < len; i++) {
                text[position + i] = buffer[i];
            }
            printf("Text added successfully\n");
            break;
        }
        case 7: {
        }