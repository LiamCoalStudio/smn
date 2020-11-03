#include "str.h"

/**
 * Unquotes a string, or if already unquoted and a
 * variable with that name exists, get that variable.
 * @param str String to process
 * @return
 * Unquoted if quoted. Variable content if unquoted
 * and variable exists. Otherwise return @c str.
 */
str string_from(const str& str)
{
    if (str.starts_with('"') && str.ends_with('"'))
        return str.substr(1, str.size() - 2);
    else if(global.variable_context.contains(str))
        return string_from(global.variable_context[str]);
    else
        return str;
}
