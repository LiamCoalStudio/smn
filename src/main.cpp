#include "simon.h"
#include <iostream>
#include <fstream>
#include <string>
#include <optionparser.h>
#include <vector>
#include <src/generators/generator.h>

using namespace std;
global_t global;
extern void parse(std::istream *input);
extern void use_init();

option::ArgStatus arg_req(const option::Option &option, bool msg) {
    if (option.arg != nullptr)
        return option::ARG_OK;
    if (msg) print_error("Option '" << option << "' requires an argument\n");
    return option::ARG_ILLEGAL;
}

enum optionIndex {
    UNKNOWN,
    HELP,
    OUTPUT,
    GENERATE_ONLY,
    PRINT_VERSION,
    NO_COMMENT,
};
const option::Descriptor usage[] =
        {
                {UNKNOWN, 0, "",  "", option::Arg::None,
                 "USAGE: simon [options] <file>\n\nOptions:"},
                {HELP, 0, "", "help", option::Arg::None,
                 "  --help            Print usage and exit."},
                {OUTPUT, 0, "o", "out", arg_req,
                 "  --out, -o         Output here."},
                {GENERATE_ONLY, 0, "g", "gen", option::Arg::None,
                 "  --gen, -g         Only generate source files."},
                {PRINT_VERSION, 0, "", "version", option::Arg::None,
                 "  --version         Print version."},
                {NO_COMMENT, 0, "n", "no-comment", option::Arg::None,
                 "  --no-comment, -n  Do not include original code comments in output."},
                {0, 0, 0, 0, 0, 0}
        };
list<std::string> libraries;

bool comments = true;

/**
 * @param argc Argument count.
 * @param argv Array of command line arguments.
 * @return 0 on success, 1 on failure
 */
int main(int argc, char **argv) {
    argc -= (argc > 0);
    argv += (argc > 0);
    option::Stats stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);
    if (parse.error())
        return 1;
    if (options[HELP] || argc == 0 || parse.nonOptionsCount() == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }
    if (options[PRINT_VERSION]) {
        std::cout << "smn is version " << VERSION << std::endl;
        return 0;
    }
    const char *output_name = options[OUTPUT].arg;
    istream *input = new ifstream(parse.nonOption(0), ifstream::in);
    auto *output = new fstream("/tmp/smn0.tmp", fstream::out | fstream::trunc | fstream::in);
    if (!input) {
        print_error("cannot open file");
        return 1;
    }

    global.language = NONE;
    global.output = output;
    global.output
            ->flush();
    global.line = 0;
    global.filename = parse.nonOption(0);

    comments = !options[NO_COMMENT];

    // Loop parse() until input has an error
    while (!!*input) ::parse(input);
    if (options[GENERATE_ONLY]) {
        std::ofstream dest(output_name, std::ios::binary);
        output->seekg(0);
        dest << output->rdbuf();
    } else {
        auto gen = for_language(global.language);
        output->flush();
        gen->compile("/tmp/smn0.tmp",
                     output_name);
    }

    global.output->flush();
    return 0;
}
