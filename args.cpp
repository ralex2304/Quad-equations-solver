#include "args.h"

void args_parse(int argc, char* argv[], char** filename) {
    assert(argv && filename && *filename == NULL);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], ARGS_TEST_FILE_PATH) == 0) {
            if (++i >= argc) {
                printf("No test file name found\n");
                break;
            }
            *filename = (char*)malloc(strlen(argv[i]) * sizeof(char));
            strcpy(*filename, argv[i]); 
        } else if (strcmp(argv[i], ARGS_HELP) == 0) {
            print_help();
        } else {
            printf("Wrong console argument: %s\nUse -h for help", argv[i]);
        }
    }
}