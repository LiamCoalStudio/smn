#include "simon.h"
#include "elements.h"
#include "functions/functions.h"
#include <iostream>

bool comment_mode;

void parse_line(const str& str);

/**
 * Parses a smn file, and does stuff with it.
 */
void parse(std::istream *input)
{
    str obj;
    *input >> obj;
    if(obj.empty()) return;

    // Comments
    if(obj == "#[" && !comment_mode) comment_mode = true;
    if(obj == "]#" && comment_mode) comment_mode = false;
    if(obj == "#[" || obj == "]#" || (comment_mode && obj != "]#")) return;

    bool body = obj[obj.size() - 1] == ':';

    while(body ? obj.find(";;") > obj.size() : !obj.ends_with(';') && !input->eof())
    {
        obj += ' ';
        str add;
        *input >> add;
        obj += add;
    }

    parse_line(obj);

    // Flush outputs
    std::cout.flush();
    std::cerr.flush();
}

enum ParsePart
{Name, Arguments, Body, Finished};

void parse_line(const str& s)
{
#if TESTING == true
    print_info(s);
#endif

    std::list<str> args, lines;
    str name;

    str buf;
    ParsePart part = Name;
    bool started;
    LanguageElement* element;
    char l = '\x00';

    for(auto& c : s)
    {
        switch (part)
        {
            case Name:
                if(c == ' ')
                {
                    element = get(name);
                    part = Arguments;
                }
                else if(c == ';' && l != ';' && l != '\x00')
                {
                    element = get(name);
                    part = Finished;
                }
                else name += c;

                goto out_of_switch;

            case Arguments:
                if(c == ',')
                {
                    args.emplace_back(buf);
                    buf = "";
                    started = false;
                }
                else if(c == ';' && !element->has_body())
                {
                    part = Finished;
                    args.emplace_back(buf);
                }
                else if(c == ';' && l != ';' && element->has_body())
                {
                    lines.emplace_back(buf + ";");
                    buf = "";
                }
                else if(c == ';' && l == ';')
                {
                    part = Finished;
                    lines.pop_back();
                }
                else if(c == ' ' && !started);
                else
                {
                    buf += c;
                    started = true;
                }

                goto out_of_switch;

            case Body:
                if(c == ';' && l == ';') part = Finished;
                else if(c == '\n' || c == '\r')
                {
                    lines.emplace_back(buf);
                    buf = "";
                }
                else if(c == ' ' && started) buf += c;
                else
                {
                    buf += c;
                    started = true;
                }
                goto out_of_switch;

            default: goto out_of_switch;
        }
        out_of_switch:
            if(part == Finished) break;
            l = c;
    }

    if(element == nullptr)
    {
        print_error("invalid -> " << name);
        return;
    }

    if(element->has_body()) element->execute(args, args.size(), &global, lines);
    else element->execute(args, args.size(), &global);

    std::cout.flush();
    std::cerr.flush();
}
