#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// List of C keywords
char keywords[32][10] = {
    "auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto",
    "if","int","long","register","return","short","signed",
    "sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while"
};

// List of valid single-character operators
char operators[] = "+-*/%=<>!&|";

int isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char filename[] = "input.txt";  // Input from text file
    char ch, buffer[MAX];
    int i = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    printf("Lexical Analysis of '%s':\n", filename);

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch)) {
            buffer[i++] = ch;
        } else if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (i != 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer)) {
                    printf("[Keyword]    %s\n", buffer);
                } else {
                    printf("[Identifier] %s\n", buffer);
                }
                i = 0;
            }
        } else if (isOperator(ch)) {
            if (i != 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer)) {
                    printf("[Keyword]    %s\n", buffer);
                } else {
                    printf("[Identifier] %s\n", buffer);
                }
                i = 0;
            }
            printf("[Operator]   %c\n", ch);
        }
    }

    // Final buffer flush
    if (i != 0) {
        buffer[i] = '\0';
        if (isKeyword(buffer)) {
            printf("[Keyword]    %s\n", buffer);
        } else {
            printf("[Identifier] %s\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}
