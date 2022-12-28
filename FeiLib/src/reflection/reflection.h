#pragma once

#include "reflection/enum/enum_reflection.h"
#include "reflection/class/meta_class.h"
#include "reflection/class/class_manager.h"

#ifdef _MSC_VER
constexpr bool can_use_reflection = true;
#elif
constexpr bool can_use_reflection = false;
#endif
static_assert(can_use_reflection, "Only Use For MSVC");


namespace enum_reflection {

#define FEI_ENUM(ENUM_CLASS_NAME) \
    enum class ENUM_CLASS_NAME; \
    struct enum_reflection_register_##ENUM_CLASS_NAME : public meyers_static<enum_reflection_register_##ENUM_CLASS_NAME>{ \
        enum_reflection_register_##ENUM_CLASS_NAME() { \
            enum_reflection::details::enum_manager::get_instance().register_enum<ENUM_CLASS_NAME>(); \
        } \
    }; \

    template<typename EnumType>
    std::string_view to_name(EnumType enum_value) requires std::is_enum_v<EnumType> {
        return details::enum_manager::get_instance().get_enum_name(enum_value);
    }

    template<typename EnumType>
    EnumType to_enum(const std::string& enum_name) requires std::is_enum_v<EnumType> {
        return details::enum_manager::get_instance().template get_enum_value<EnumType>(enum_name);
    }
}

namespace class_reflection
{

#define FEI_CLASS(CLASS_NAME) \
private: \
	friend class_reflection::details::class_manager; \
    constexpr static std::string_view class_name = #CLASS_NAME; \
	using ClassType = CLASS_NAME;

#define FEI_PROPERTY(PROPERTY_NAME) \
	struct PROPERTY_NAME##_wrapper : public meyers_static<PROPERTY_NAME##_wrapper> \
    { \
		PROPERTY_NAME##_wrapper() \
        { \
			const class_reflection::details::meta_property property = { #PROPERTY_NAME, offsetof(ClassType, PROPERTY_NAME)}; \
			class_reflection::details::class_manager::get_instance().register_property(class_name, property); \
        } \
    };


}