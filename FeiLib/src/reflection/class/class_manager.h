#pragma once
#include "meta_class.h"
#include "utility/lazy_singleton.h"

namespace class_reflection::details
{



    class class_manager
    {
    private:
        std::unordered_map<std::string_view, meta_class> all_class;
    public:
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

        inline static class_manager& get_instance() {
            return lazy_singleton<class_manager>::get_instance();
        }

    public:
        /**
         * \brief register meta_class data, auto use by MACRO
         */
        void register_class(std::string_view class_name, const meta_property& meta_property)
        {
            const auto iterator = all_class.find(class_name);
            if (iterator == all_class.end())
            {
                all_class.insert(std::make_pair(class_name, meta_class{class_name}));
            }
            all_class[class_name].member_infos.push_back(meta_property);
        }

    };

}