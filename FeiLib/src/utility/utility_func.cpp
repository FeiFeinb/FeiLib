#include "all_header.h"
#include "utility/utility_func.h"

std::string_view split_string_view_last_of(std::string_view source_view, std::string_view::value_type Left, std::string_view::value_type Right) {
    std::size_t first_pos = source_view.find_last_of(Left);
    std::size_t last_pos = source_view.find_last_of(Right);
    return source_view.substr(first_pos + 1, last_pos - first_pos - 1);
}

std::string_view split_string_view(std::string_view source_view, std::string_view Left, std::string_view Right) {
    std::size_t first_pos = source_view.find(Left);
    std::size_t last_pos = source_view.find(Right);
    return source_view.substr(first_pos + Left.size(), last_pos - first_pos - Left.size());
}

