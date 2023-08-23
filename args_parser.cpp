#include "args_parser.h"

Status::Statuses args_parse(int argc, char* argv[], ArgsTest* args_test) {
    assert(argv);
    assert(argc);
    assert(args_test);
    assert(args_test->filename == nullptr);

    bool exit = false;
    for (int i = 1; i < argc; i++) {
        bool is_found = false;

        for (int j = 0; j < ARGS_STRUCT_COUNT; j++) {
            if (strcmp(argv[i], args[j].arg) == 0) {
                switch (args[j].func(&i, argc, argv, args_test)) {
                    case ArgsMode::CONTINUE:
                        break;
                    case ArgsMode::EXIT:
                        exit = true;
                        break;
                    case ArgsMode::ERROR:
                        return Status::ARGS;
                    default:
                        assert(0 && "args[j].func() returned wrong ArgsMode");
                        break;
                }
                is_found = true;
                break;
            }
        }
        if (is_found)
            continue;

        printf("Wrong console argument: %s\n"
               "Use -h for help", argv[i]);
        return Status::ARGS;
    }
    if (exit)
        return Status::OK_EXIT;

    return Status::NORMAL_WORK;
}

ArgsMode print_help(int* arg_i, const int argc, char* argv[], ArgsTest* args_test) {
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(args_test);

    printf("# This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "# Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n"
           "# Console args:\n");

    for (int i = 0; i < ARGS_STRUCT_COUNT; i++) {
        if (!args_test->is_enabled && strcmp(args[i].arg, "-t") == 0)
            continue;
        printf("%s", args[i].description);
    }

    printf("# End of help. Good luck using this program!\n");
    return ArgsMode::EXIT;
}

ArgsMode read_test_filename(int* arg_i, int argc, char* argv[], ArgsTest* args_test) {
    assert(arg_i);
    assert(argv);
    assert(args_test);

    if (!args_test->is_enabled) {
        printf("Test mode is disabled! Wrong argument.\n");
        return ArgsMode::ERROR;
    }
    if (++(*arg_i) >= argc) {
        printf("No test file name found\n");
        return ArgsMode::ERROR;
    }
    args_test->filename = argv[*arg_i];
    return ArgsMode::CONTINUE;
}
