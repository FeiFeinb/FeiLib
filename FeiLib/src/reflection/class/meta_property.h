#pragma once

namespace class_reflection::details
{
	class meta_property
	{
	public:
	    std::string_view property_name;
	    std::size_t member_offset = 0;
	};
}