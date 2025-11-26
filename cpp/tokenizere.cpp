// Write a C/C++ code to Identify all the tokens from a given file.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *keywords[] = {
    "int", "float", "return", "if", "else", "while",
    "for", "main", "void", NULL
};

int isKeyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '‐' || ch == '*' || ch == '/' || ch == '=' ||
            ch == '<' || ch == '>');
}

int isPunctuation(char ch) {
    return (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ',' ||
            ch == ';');
}

int main() {
    FILE *fp;
    char ch, word[100];
    int i = 0;

    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Cannot open file.\n");
        return 1;
    }

    printf("Tokens:\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            word[i++] = ch;
        } else {
            // Process the accumulated word if it exists
            if (i > 0) {
                word[i] = '\0';
                i = 0;
                if (isKeyword(word))
                    printf("KEYWORD : %s\n", word);
                else if (isdigit(word[0]))
                    printf("NUMBER : %s\n", word);
                else
                    printf("IDENTIFIER : %s\n", word);
            }

            // Process the current delimiter character
            if (isOperator(ch)) {
                printf("OPERATOR : %c\n", ch);
            } else if (isPunctuation(ch)) {
                printf("PUNCTUATION : %c\n", ch);
            } else if (isspace(ch)) {
                // Ignore whitespace
            } else if (!isalnum(ch) && ch != '\n' && ch != ' ') {
                printf("UNKNOWN : %c\n", ch);
            }
        }
    }

    // Process any remaining word after EOF
    if (i > 0) {
        word[i] = '\0';
        if (isKeyword(word))
            printf("KEYWORD : %s\n", word);
        else if (isdigit(word[0]))
            printf("NUMBER : %s\n", word);
        else
            printf("IDENTIFIER : %s\n", word);
    }

    fclose(fp);
    return 0;
}
