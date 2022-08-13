#include "all_header.h"

#include "reflection/reflection.h"
#include "utility/utility_func.h"

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


int main() {
    //auto& manager = enum_reflection::details::enum_manager::get_instance();

    //auto result = enum_reflection::to_name(RGB::Color::Red);

    //RGB::Color enum_value = enum_reflection::to_enum<RGB::Color>("RGB::Color::Red");


    // metaClass.member_infos.push_back({"int_data", get_member_offset(&Color_Manager::int_data)});
    // metaClass.member_infos.push_back({"float_data", get_member_offset(&Color_Manager::float_data)});
    // metaClass.member_infos.push_back({"bool_data", get_member_offset(&Color_Manager::bool_data)});

    Color_Manager colorManager;
    auto classManager = class_reflection::details::class_manager::get_instance();
    int* p = classManager.get_member<Color_Manager, int>(&colorManager, "int_data");

    std::cout << get_type_name<std::vector<int>>();

    return 0;
}
