#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** get_commands(char* line) {
    
}

int count_char(char c, char* string) {
    int counter = 0;
    //printf("counting '%c' in '%s'\n", c, string);
    while (*string) {
        //printf("%c", *string);
        if (c == *string) {
            counter++;
        }
        string++;
    }
    return counter;
}

int main() {
    char* s1 = "this is a sentence";
    printf("'%s' has %d spaces\n", s1, count_char(' ', s1));
    char* s2 = "this; is a line;;";
    printf("'%s' has %d ;\n", s2, count_char(';', s2));
    return 0;
}
