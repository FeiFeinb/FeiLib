#pragma once
#include "meta_class.h"
#include "utility/lazy_singleton.h"

#define DEBUG_BREAK() (__nop(), __debugbreak())
#define DEBUG_BREAK_ABORT() (__nop(), __debugbreak(), std::abort())

namespace class_reflection::details
{
    class class_manager
    {
    private:
	    /**
	     * \brief Manage by [name - meta_class]
	     */
	    std::unordered_map<std::string_view, meta_class> all_class;

    public:
        meta_class& get_class(std::string_view class_name)
        {
            const auto iterator = all_class.find(class_name);
            // Check if it's valid to get meta_class
            if (iterator == all_class.end())
            {
                DEBUG_BREAK();
            }
            return iterator->second;
        }

        template<typename ClassType, typename MemberType>
        MemberType* get_member(ClassType* class_pointer, std::string_view member_name)
        {
            auto iterator = all_class.find(class_pointer->class_name);
            for (const auto& property : iterator->second.member_infos)
            {
                if (property.property_name == member_name)
                    return reinterpret_cast<MemberType*>(reinterpret_cast<char*>(class_pointer) + property.member_offset);
            }
            return nullptr;
        }

        inline static class_manager& get_instance()
    	{
            return lazy_singleton<class_manager>::get_instance();
        }

    public:
	    /**
	     * \brief Register meta_class data, used by FEI_CLASS() automatically
	     */
	    void register_class(std::string_view class_name)
        {
            const auto iterator = all_class.find(class_name);
            if (iterator == all_class.end())
            {
                all_class.insert(std::make_pair(class_name, meta_class{ class_name }));
                return;
            }
            
            DEBUG_BREAK();
        }
    };
}