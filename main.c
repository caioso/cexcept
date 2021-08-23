#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cexcept.h"

void read_file(FILE *, char *);
void check_file_validity(FILE *);
void print_file_content(FILE * file, char *);
void show_error(int);

enum file_exception {
    FILE_NOT_FOUND = 1,
    PERMISSION_DENIED = 2
};

int main(int argc, char * argv[argc + 1]) {
    FILE * text_file = fopen(argv[1], "r");

    try {
        read_file(text_file, argv[1]);
    }
    catch {
        printf("Unable to open file '%s'\n", argv[1]);
        show_error(exception);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void read_file(FILE* file, char* name) {
    check_file_validity(file);
    print_file_content(file, name);
}

void check_file_validity(FILE* file) {
    if (file == NULL) {
        throw(FILE_NOT_FOUND);
    }
}

void print_file_content(FILE* file, char * name) { 
    char buffer[100];
    fread(buffer, 100, 1, file);
    printf("'%s' content: %s", name, buffer);
}

void show_error(int error_code) {
    switch (error_code) {
        case FILE_NOT_FOUND: printf("\terror: file not found\n");
                             break;
        case PERMISSION_DENIED: printf("\terror: permission denied\n");
                                break;
        default: printf("\terror: unknown error\n");
    }
}   