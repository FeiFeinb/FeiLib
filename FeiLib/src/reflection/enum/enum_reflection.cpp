#include "all_header.h"
#include "enum_reflection.h"

namespace enum_reflection::details {
    bool is_valid_enum_name(std::string_view enum_name) {
        return !enum_name.empty() && enum_name[0] != '(';
    }
}
