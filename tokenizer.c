#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* int count_char()
counts the number of occurences of c in string

args:
    c: character to be counted
    string: string to count from
return:
    number of occurences
*/
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

/* void shift_array_back_at
moves array elements one position back

args:
    original: array to be modified
    length: length of given array
return:

*/
void shift_array_back_at(char** original, int length) {
    for (int i = 0; i < length; i++) {
        original[i] = original[i + 1];
    }
}

/* char shift_string_back_at
moves characters one position back in string

args:
    original: string to be modified
return:
    character that was overwritten
*/
char shift_string_back_at(char* original) {
    char ret = original[0];
    for (int i = 0; i < strlen(original) + 1; i++) {
        original[i] = original[i + 1];
    }
    return ret;
}

/* char strip_by
looks for all occurences of delete_dis and removes the first character

args:
    original: string to be modified
    delete_dis: substring to look for
return:
    character that is overwritten
*/
char strip_by(char* original, char* delete_dis) {
    char* loc = strstr(original, delete_dis);
    char ret;
    while (loc) {
        ret = shift_string_back_at(loc);
        loc = strstr(original, delete_dis);
    }
    return ret;
}

/* char strip_front_by
looks for all occurences of delete_dis and removes the second character

args:
    original: string to be modified
    delete_dis: substring to look for
return:
    character that is overwritten
*/
char strip_front_by(char* original, char* delete_dis) {
    char* loc = strstr(original, delete_dis);
    char ret;
    while (loc) {
        ret = shift_string_back_at(loc + 1);
        loc = strstr(original, delete_dis);
    }
    return ret;
}

/* void strip_extra_blankspace
strips all unnecessary whitespace from string

args:
    original: string to be modified
return:

*/
void strip_extra_blankspace(char* original) {
    strip_by(original, "\t");
    strip_by(original, "\n");
    strip_by(original, "  ");
    strip_by(original, " ;");
    strip_by(original, " >");
    strip_by(original, " <");
    strip_front_by(original, "> ");
    strip_front_by(original, "< ");

    //remove trailing spaces
    for (int i = strlen(original) - 1; i >= 0; i--) {
        if (original[i] == ' ') {
            original[i] = 0;
        } else {
            break;
        }
    }
}

/* void printarr
prints out an array of strings

args:
    args: array of strings
return:

*/
void printarr(char** args) {
    int i;
    printf("[");
    while (args[i]) {
        printf("%s, ", args[i]);
        i++;
    }
    printf("]\n");
}

/*
parses through a string to separate arguments by ' '

args:
    line: line to be separated
return:
    array of strings
*/
char ** parse_args(char* line) {
    int len = count_char(' ', line) + 2;
    char ** args = (char **) calloc(len, sizeof(char*));
    int index = 0;
    while (line) {
        args[index] = strsep(&line, " ");
        index += 1;
    }
    // calloc makes sure the last thing will already be NULL
    //printf("len: %d", len);
    //printarr(args);
    while (len > 2 && !args[0][0]) {
        shift_array_back_at(args, len);
        len--;
    }
    return args;
}

/* char* get_stdin
gets the portion of the given input that should used for stdin

args:
    input: string to look through
return:
    filename to for stdin or NULL if not provided
*/
char* get_stdin(char* input) {
    char* less_than = strchr(input, '<');
    if (!less_than) {
        return NULL;
    }
    char* in = calloc(256, sizeof(char));
    strcpy(in, less_than + 1);
    char* space_loc = strchr(in, ' ');
    if (space_loc) {
        *space_loc = 0;
    }
    char* less_loc = strchr(in, '<');
    if (less_loc) {
        *less_loc = 0;
    }
    char* greater_loc = strchr(in, '>');
    if (greater_loc) {
        *greater_loc = 0;
    }
    return in;
}

/* char* get_stdout
gets the portion of the given input that should used for stdout

args:
    input: string to look through
return:
    filename to for stdout or NULL if not provided
*/
char* get_stdout(char* input) {
    char* less_than = strchr(input, '>');
    if (!less_than) {
        return NULL;
    }
    char* out = calloc(256, sizeof(char));
    strcpy(out, less_than + 1);
    char* space_loc = strchr(out, ' ');
    if (space_loc) {
        *space_loc = 0;
    }
    char* less_loc = strchr(out, '<');
    if (less_loc) {
        *less_loc = 0;
    }
    char* greater_loc = strchr(out, '>');
    if (greater_loc) {
        *greater_loc = 0;
    }
    return out;
}

/* void delete_stdin
deletes the portion of the given input that was used for stdin

args:
    input: string to look through
return:

*/
void delete_stdin(char* input) {
    char* less_than = strchr(input, '<');
    if (less_than) {
        //printf("deleting stdin portion: %s\n", less_than);
        while (*less_than && *less_than != ' ') {
            //printf("deleting portion: %s\n", less_than);
            shift_string_back_at(less_than);
        }
    }
}

/* void delete_stdout
deletes the portion of the given input that was used for stdout

args:
    input: string to look through
return:

*/
void delete_stdout(char* input) {
    char* greater_than = strchr(input, '>');
    if (greater_than) {
        //printf("deleting stdout portion: %s\n", greater_than);
        while (*greater_than && *greater_than != ' ') {
            //printf("deleting portion: %s\n", greater_than);
            shift_string_back_at(greater_than);
        }
    }
}
