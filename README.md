Хід роботи
Крок 1: Створення меню для вибору команд
void print_menu() {
    printf("1. Append text\n");
    printf("2. Start new line\n");
    printf("3. Save to file\n");
    printf("4. Load from file\n");
    printf("5. Print current text\n");
    printf("6. Insert text by line and index\n");
    printf("7. Search text\n");
    printf("0. Exit\n");
    printf("Choose the command:\n");
}
Крок 2:Створення команди для додавання тексту
int main() {
    char* text = (char*)malloc(1 * sizeof(char));
    text[0] = '\0';
    int capacity = 1;

    while (1) {
        print_menu();
        int command;
        scanf("%d", &command);
        getchar();

        if (command == 0) {
            break;
        }

        switch (command) {
        case 1:
        {
            char buffer[100];
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
        }
        break;

Крок 3: Створення команди для переходу на новий рядок 
case 2:
{
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
}
break;
Крок 4: Реалізація збереження у файл
  case 3:
  {
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
          printf("Error with opening file\n");
      }
  }
  break;

Крок 5: Реалізація вивантаження з файлу
 case 4:
 {
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
         printf("Text loaded \n");
     }
 }
 break;

Крок 6: Виведення тексту
 case 5:
     if (text[0] == '\0') {
         printf("(Empty line)\n");
     }
     else {
         printf("%s\n", text);
     }
     break;
     
Крок 7: Вставка тексту по індексу і рядку
  case 6:
  {
      int line, index;
      printf("Choose line and index: ");
      scanf("%d %d", &line, &index);
      getchar();
      int position = get_position(text, line, index);
      if (position == -1) {
          printf("Invalid data\n");
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
  }
  break;

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

Крок 8: Реалізація пошуку тексту
    case 7:
    {
        char buffer[30];
        printf("Enter text to search: ");
        fgets(buffer, 30, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '\0') {
            printf("Empty search string\n");
            break;
        }
        int line = 1, col = 0;
        int found = 0;
        for (int i = 0; text[i] != '\0'; i++) {
            if (text[i] == '\n') {
                line++;
                col = 0;
                continue;
            }
            int j = 0;
            while (buffer[j] != '\0' && text[i + j] != '\0' && text[i + j] == buffer[j]) {
                j++;
            }
            if (buffer[j] == '\0') {
                printf("Found \"%s\" at line %d, column %d\n", buffer, line, col);
                found = 1;
            }
            col++;
        }
        if (!found) {
            printf("Text \"%s\" not found\n", buffer);
        }
    }
    break;

    default:
        printf("Invalid command\n");
        break;
    }
}
 



