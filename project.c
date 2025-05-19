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
    printf("8. Clear console (toggle)\n");
    printf("0. Exit\n");
}
void clear_console() {
    system("cls");
}