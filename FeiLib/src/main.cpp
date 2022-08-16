﻿#include "all_header.h"

#include "reflection/reflection.h"
#include "utility/utility_func.h"
#include "utility/utility_traits.h"
#include "color.h"

class Color_Manager
{
    FEI_CLASS(Color_Manager)

public:
    FEI_PROPERTY(int_data)
    int int_data = 30;
};

template<typename>
constexpr std::string_view get_type_name()
{
    std::string_view funcSig =__FUNCSIG__;
    return split_string_view_first_last(
        funcSig.substr(funcSig.find("get_type_name")), '<', '>');
}

void test_enum_reflection()
{
    auto& manager = enum_reflection::details::enum_manager::get_instance();

	auto result = enum_reflection::to_name(RGB::Color::Red);

	RGB::Color enum_value = enum_reflection::to_enum<RGB::Color>("RGB::Color::Red");
}

void test_class_reflection()
{
    Color_Manager colorManager;
    auto classManager = class_reflection::details::class_manager::get_instance();
    int* p = classManager.get_member<Color_Manager, int>(&colorManager, "int_data");

    std::cout << get_type_name<std::vector<int>>();
}



int main() {
    // int[2][2][2]
    using ArrayType = multi_dimensional_arrays_t<int, 2, 3>;

    using IS = std::index_sequence<2, 90, 2, 3>;



    // how to get std::index_sequence<2, 90, 2, 3>
    std::cout << index_sequence_element_v<0, std::index_sequence<2, 90, 2, 3>>;
    std::cout << index_sequence_element_v<1, std::index_sequence<2, 90, 2, 3>>;
    std::cout << index_sequence_element_v<2, std::index_sequence<2, 90, 2, 3>>;
    std::cout << index_sequence_element_v<3, std::index_sequence<2, 90, 2, 3>>;


    std::cout << index_args_element_v<3, 2, 90, 2, 3>;
    std::cout << index_args_element_v<3, 2, 90, 2, 3>;


    // std::cout << std::get<IS::size() - 1>(std::tuple<int, int>())

    // Actually It Is int[2][90][2][3]
    using ArrayType_Non_Regular = multi_dimensional_arrays_non_regular_t<int, 3, 2, 90, 2>;
}
