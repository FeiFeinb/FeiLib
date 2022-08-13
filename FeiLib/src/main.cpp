#include "all_header.h"

#include "reflection/reflection.h"
#include "utility/utility_func.h"

class Color_Manager
{
public:
    constexpr static std::string_view class_name = "Color_Manager";
private:
    struct int_data_wrapper : public meyers_static<int_data_wrapper>
    {
        int_data_wrapper()
        {
            class_reflection::details::meta_property property = {"int_data", get_member_offset(&Color_Manager::int_data)};
            class_reflection::details::class_manager::get_instance().register_class(class_name, property);
        }
    };
    int int_data = 10;

    int int_data2 = 20;

    float float_data = 3.14f;

    bool bool_data = true;
};

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

    std::cout << sizeof(Color_Manager);

    return 0;
}
