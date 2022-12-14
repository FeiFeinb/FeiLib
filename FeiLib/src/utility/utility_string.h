#pragma once

std::string_view split_string_view_last_of(std::string_view source_view, std::string_view::value_type Left, std::string_view::value_type Right);

std::string_view split_string_view_first_last(std::string_view source_view, std::string_view::value_type Left, std::string_view::value_type Right);

std::string_view split_string_view(std::string_view source_view, std::string_view Left, std::string_view Right);


template<typename StringType> requires std::is_same_v<StringType, std::string> || std::is_same_v<StringType, std::string_view>
decltype(auto) split_string_first_last(const StringType& source, typename StringType::value_type left, typename StringType::value_type right)
{
    const std::size_t first_pos = source.find_first_of(left);
    const std::size_t last_pos = source.find_last_of(right);
    return source.substr(first_pos + 1, last_pos - first_pos - 1);
}