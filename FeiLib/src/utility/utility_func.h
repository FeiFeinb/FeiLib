#pragma once

template<auto StartIndex, auto EndIndex, typename FunctionType>
void constexpr_for(const FunctionType& for_callback) {
    if constexpr (StartIndex < EndIndex) {
        for_callback.template operator()<StartIndex>();
        constexpr_for<StartIndex + 1, EndIndex>(for_callback);
    }
}

std::string_view split_string_view_last_of(std::string_view source_view, std::string_view::value_type Left,std::string_view::value_type Right);

std::string_view split_string_view_first_last(std::string_view source_view, std::string_view::value_type Left, std::string_view::value_type Right);

std::string_view split_string_view(std::string_view source_view, std::string_view Left, std::string_view Right);


template<typename StaticMemberType>
struct meyers_static {
    meyers_static()
    {
        (void)meyers_static_member;
    }
    static StaticMemberType meyers_static_member;
};

template<typename StaticMemberType>
StaticMemberType meyers_static<StaticMemberType>::meyers_static_member;
