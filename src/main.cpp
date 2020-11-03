#include "elements.h"
#include "simon.h"
#include "elements/use_element.h"
#include "elements/include_element.h"
#include "elements/exec_function_element.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <optionparser.h>

using namespace std;
using namespace filesystem;

global_t global;

extern void parse(std::istream *input);
extern void use_init();

option::ArgStatus arg_req(const option::Option& option, bool msg)
{
    if (option.arg != nullptr)
        return option::ARG_OK;

    if (msg) print_error("Option '" << option << "' requires an argument\n");
    return option::ARG_ILLEGAL;
}

enum optionIndex
{ UNKNOWN, HELP, PLUS, OUTPUT };

const option::Descriptor usage[] =
{
        {UNKNOWN, 0, "", "", option::Arg::None,
         "USAGE: simon [options] <file>\n\nOptions:"},
        {HELP, 0, "", "help", option::Arg::None,
         "  --help            Print usage and exit." },
        {PLUS, 0, "p", "plus", option::Arg::None,
         "  --plus, -p        Increment count." },
        {OUTPUT, 0, "o", "out", arg_req,
         "  --out, -o         Output LLVM here." },
        {0, 0, 0, 0, 0, 0}
};

/**
 * @param argc Argument count.
 * @param argv Array of command line arguments.
 * @return 0 on success, 1 on failure
 */
int main(int argc, char** argv)
{
    argc -= (argc>0);
    argv += (argc>0);
    option::Stats  stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    if (parse.error())
        return 1;

    if (options[HELP] || argc == 0 || parse.nonOptionsCount() == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    const char* output_name = "output.ll";

    if(options[OUTPUT])
    {
        output_name = options[OUTPUT].arg;
    }

    istream* input = new ifstream(parse.nonOption(0), ifstream::in);
    ostream* output = new ofstream(output_name, ofstream::out | ofstream::trunc);

    if(!input)
    {
        print_error("cannot open file");
        return 1;
    }

    // Initialize `use`
    all_elements.emplace_back(new ExecFunctionElement);
    all_elements.emplace_back(new UseElement);
    all_elements.emplace_back(new IncludeElement);
    use_init();

    // Set global variables
    global.variable_context["@color.red"] = col_red;
    global.variable_context["@color.blue"] = col_blue;
    global.variable_context["@color.yellow"] = col_yellow;
    global.variable_context["@color.reset"] = col_clear;
    global.variable_context["@cmdline.file"] = str(parse.nonOption(0));
    global.variable_context["@simon.version"] = simon_version;

    // Loop parse() until input has an error
    while(!!*input) ::parse(input);

    return input->eof() ? 0 : 1;
}
