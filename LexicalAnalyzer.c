#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

// Function to check if a word is a keyword
int isKeyword(char *word) {
    char keywords[32][10] = {
        "int", "return", "if", "else", "while", "do", "break", "continue", 
        "double", "float", "char", "long", "short", "for", "void", "switch", 
        "case", "default", "const", "unsigned", "static", "struct", "goto", 
        "sizeof", "typedef", "enum", "volatile", "extern", "register", "union", "signed"
    };
    for (int i = 0; i < 32; ++i) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch;
    char word[20];
    int i = 0;
    FILE *fp;
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file: %s\n", strerror(errno));
        return 1;
    }

    printf("File opened successfully.\n");

    while ((ch = fgetc(fp)) != EOF) {
        // If alphanumeric, continue forming the word
        if (isalnum(ch) && i < 19) {
            word[i++] = ch;
        } else {
            // End of word, check if it's a keyword or identifier
            if (i != 0) {
                word[i] = '\0';
                if (isKeyword(word))
                    printf("%s is a keyword\n", word);
                else
                    printf("%s is an identifier\n", word);
                i = 0; // Reset word index
            }
            // Handle operators
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '%') {
                printf("%c is an operator\n", ch);
            }
        }
    }

    // Handle last word if necessary
    if (i != 0) {
        word[i] = '\0';
        if (isKeyword(word))
            printf("%s is a keyword\n", word);
        else
            printf("%s is an identifier\n", word);
    }

    fclose(fp);
    return 0;
}