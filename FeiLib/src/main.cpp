#include "all_header.h"

#include "reflection/reflection.h"
#include "utility/utility_func.h"
#include "utility/utility_string.h"
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
constexpr void get_type_name()
{
    std::string_view func_sig = __FUNCSIG__;
    std::string class_type_name = split_string_first_last<std::string_view>(func_sig, '<', '>');
    std::cout << class_type_name << std::endl;
    // std::vector<std::vector<int>>
    // class std::vector<class std::vector<int,class std::allocator<int> >,class std::allocator<class std::vector<int,class std::allocator<int> > > >
    // TODO: Remove "class " And " "
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

    // std::cout << get_type_name<std::vector<int>>();
}


int main()
{
    get_type_name<std::vector<std::vector<int>>>();
}
