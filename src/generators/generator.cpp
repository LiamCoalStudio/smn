#include "generator.h"
#include <utility>

class_info_t class_info;
int _indent = 0;

str indent() {
    str out;
    for (int i = 0; i < _indent; ++i) out += "    ";
    return out;
}

UnsupportedFeatureException::UnsupportedFeatureException(str what) {
    _what = std::move(what);
}

const char *UnsupportedFeatureException::what() const noexcept {
    return _what.c_str();
}
