#include "args.h"

void args_parse(int argc, char* argv[], char** filename) {
    assert(argv && filename && *filename == NULL);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (++i >= argc) {
                printf("No test file name found\n");
                break;
            }
            *filename = (char*)malloc(strlen(argv[i]) * sizeof(char));
            strcpy(*filename, argv[i]); 
            continue;
        }
        printf("Wrong console argument: %s\n", argv[i]);
    }
}