#include "args_parser.h"

ProgramMode args_parse(int argc, char* argv[], ArgsTest* args_test) {
    assert(argv && args_test && args_test->filename == nullptr);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], ARGS_HELP) == 0) {
            return ProgramMode::HELP;
        } else if (args_test->is_enabled && strcmp(argv[i], ARGS_TEST_FILE_PATH) == 0) {
            if (++i >= argc) {
                printf("No test file name found\n");
                return ProgramMode::ERROR;
            }
            args_test->filename = argv[i];
        } else {
            printf("Wrong console argument: %s\n"
                   "Use -h for help", argv[i]);
            return ProgramMode::ERROR;
        }
    }
    return ProgramMode::NORMAL;
}
