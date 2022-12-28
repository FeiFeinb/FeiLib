#pragma once
#include "reflection/class/meta_property.h"

namespace class_reflection::details
{
	class meta_class
	{
	public:
	    meta_class() = default;
	    explicit meta_class(std::string_view name) : class_name(name), member_infos() {}

	    std::string_view class_name;
	    std::vector<meta_property> member_infos;

        /**
		 * \brief Register meta_property data, used by FEI_PROPERTY() automatically
		 */
        void register_property(const meta_property& meta_property)
        {
            member_infos.push_back(meta_property);
        }
	};
}