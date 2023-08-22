#include "args_parser.h"

ProgramMode args_parse(int argc, char* argv[], char** filename) {
    assert(argv && filename && *filename == NULL);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], ARGS_TEST_FILE_PATH) == 0) {
            if (++i >= argc) {
                printf("No test file name found\n");
                return ProgramMode::ERROR;
            }
            *filename = argv[i];
        } else if (strcmp(argv[i], ARGS_HELP) == 0) {
            print_help();
            return ProgramMode::HELP;
        } else {
            printf("Wrong console argument: %s\n"
                   "Use -h for help", argv[i]);
            return ProgramMode::HELP;
        }
    }
    return ProgramMode::NORMAL;
}

Error::Errors Error::raise(Errors err) {
    switch (err) {
    case OK:
        break;
    case ARGS:
        printf("Exiting. Args error\n");
        break;
    case COEFFS_INPUT:
        printf("Exiting. Coefficients input error");
        break;
    case TEST_INPUT:
        printf("Exiting. Test file input error");
        break;
    default:
        assert(0 && "Error::raise(): wrong error");
        break;
    };
    return err;
}