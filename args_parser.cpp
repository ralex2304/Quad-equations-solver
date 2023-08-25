#include "args_parser.h"

Status::Statuses args_parse(int argc, char* argv[], ArgsTest* args_test) {
    assert(argv);
    assert(argc);
    assert(args_test);
    assert(args_test->filename == nullptr);

    /**
     * @brief This array contains console options, their functions and descriptions
     */
    static Argument args_dict[] = {
        {"-h", print_help,         "#   -h - prints help information\n", true}, ///< Help option

        {"-t", read_test_filename, "#   -t - specify test file name after this (works only if test mode enabled)\n"
                                    "# Test file format (there might be several such sections):\n"
                                    "# <coeff a> <coeff b> <coeff c>\n"
                                    "# <solutions number>\n"
                                    "# <solution 1 (if exists)> <solution 2 (if exists)>\n"
                                    "# \n"
                                    "# <Next test>\n", false}                   ///< Test option
    };

    static const int ARGS_DICT_LEN = sizeof(args_dict) / sizeof(args_dict[0]); ///< args_dict array len

    if(args_test->is_enabled)
        enable_test_args(args_dict, ARGS_DICT_LEN);

    bool exit = false;
    for (int i = 1; i < argc; i++) {
        bool is_found = false;

        for (int j = 0; j < ARGS_DICT_LEN; j++) {
            if (args_dict[j].is_enabled && strcmp(argv[i], args_dict[j].arg) == 0) {
                switch (args_dict[j].func(args_dict, ARGS_DICT_LEN, &i, argc, argv, args_test)) {
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
               "Use -h for help\n", argv[i]);
        return Status::ARGS;
    }
    if (exit)
        return Status::OK_EXIT;

    return Status::NORMAL_WORK;
}

ArgsMode print_help(const Argument args_dict[], const int args_dict_len,
                    int* arg_i, const int argc, char* argv[], ArgsTest* args_test) {
    assert(args_dict);
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(args_test);

    printf("# This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "# Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n"
           "# Console args:\n");

    for (int i = 0; i < args_dict_len; i++) {
        if (!args_dict[i].is_enabled)
            continue;

        printf("%s", args_dict[i].description);
    }

    printf("# End of help. Good luck using this program!\n");
    return ArgsMode::EXIT;
}

ArgsMode read_test_filename(const Argument args_dict[], const int args_dict_len,
                            int* arg_i, int argc, char* argv[], ArgsTest* args_test) {
    (void) args_dict_len;

    assert(args_dict);
    assert(arg_i);
    assert(argv);
    assert(args_test);

    if (++(*arg_i) >= argc) {
        printf("No test file name found\n");
        return ArgsMode::ERROR;
    }

    args_test->filename = argv[*arg_i];
    return ArgsMode::CONTINUE;
}
