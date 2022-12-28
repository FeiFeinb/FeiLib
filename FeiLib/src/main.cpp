#include "all_header.h"

#include "reflection/reflection.h"
#include "utility/utility_func.h"
#include "utility/utility_string.h"
#include "utility/utility_traits.h"
#include "utility/utility_function.h"
#include "color.h"



template<typename T>
bool GetMemberNameCheck(const T&);

#define GetMemberName(ClassName, MemberName) \
    ((void)sizeof(GetMemberNameCheck(((ClassName*)nullptr)->MemberName)), std::string(#MemberName))

class Color_Manager
{


    FEI_CLASS(Color_Manager)
public:
    struct Color_Manager_wrapper : public meyers_static<Color_Manager_wrapper>
    {
        Color_Manager_wrapper()
        {
            class_reflection::details::class_manager::get_instance().register_class(class_name);
        }
    };

    static class_reflection::details::meta_class& get_static_class()
    {
        return class_reflection::details::class_manager::get_instance().get_class(class_name);
    }
private:



    struct int_data_wrapper : public meyers_static<int_data_wrapper>
    {
        int_data_wrapper()
		{
			const class_reflection::details::meta_property property = { "int_data", offsetof(ClassType, int_data) };

            class_reflection::details::meta_class& static_class = get_static_class();
			static_class.register_property(property);
		}
    };
    const int int_data = 30;

};


template<typename>
constexpr void get_type_name()
{
    std::string_view func_sig = __FUNCSIG__;
    std::string class_type_name{ split_string_first_last(func_sig, '<', '>') };

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



struct static_check
{
    int normal_data = 300;

    int ddd;

    inline static int static_data = 100;
};

template<typename T>
struct static_wrapper
{
    static_wrapper() = default;

    int data = T::static_data;
};

template<typename, typename = void>
constexpr bool is_static_v = false;

template<typename T>
constexpr bool is_static_v<T, std::void_t<decltype(static_wrapper<static_check>{})>> = true;


int main()
{
	// get_type_name<std::vector<std::vector<int>>>();
	// test_class_reflection();

    // static_wrapper<static_check> a;

    std::cout << is_static_v<static_wrapper<static_check>>;

	// std::cout << Color_Manager::get_static_class().member_infos[0].property_name;
}

