#pragma once
#include "utility/utility_string.h"
#include "utility/utility_func.h"
#include "utility/lazy_singleton.h"

namespace enum_reflection::details
{

	using enum_underlying_type = int;

	struct enum_min_max_range
	{
		static constexpr enum_underlying_type enum_min_index = -100;
		static constexpr enum_underlying_type enum_max_index = 100;
	};


	template<typename EnumType, EnumType>
	constexpr std::string_view get_enum_value_name()
	{
		// Consume That There Is A Enum In Namespace Called RBG::Color
		// If We Loop Through This Method, Then We May Have __FUNCSIG__ As
		// class std::basic_string_view<char,struct std::char_traits<char> > __cdecl enum_reflection::details::get_enum_value_name<enum RGB::Color,(enum RGB::Color)0x0>(void)
		// Or
		// class std::basic_string_view<char,struct std::char_traits<char> > __cdecl enum_reflection::details::get_enum_value_name<enum RGB::Color,RGB::Color::Red>(void)
		// So We Split It By "," And ">"
		return split_string_view_last_of(__FUNCSIG__, ',', '>');
	}

	template<typename>
	constexpr std::string_view get_enum_class_name()
	{
		// Consume That There Is A Enum In Namespace Called RBG::Color
		// If Call By get_enum_class_name<RGB::Color>, Then We Have __FUNCSIG__ As
		// class std::basic_string_view<char,struct std::char_traits<char> > __cdecl enum_reflection::details::get_enum_class_name<enum RGB::Color>(void)
		// So We Split It By "<enum" And ">"
		return split_string_view(__FUNCSIG__, "<enum ", ">");
	}

	__forceinline constexpr bool is_valid_enum_name(std::string_view enum_name)
	{
		return !enum_name.empty() && enum_name[0] != '(';
	}

	class meta_enum
	{
	private:
		std::vector<std::pair<enum_underlying_type, std::string_view>> enum_infos;

	public:
		template<typename EnumType>
		static meta_enum make_enum_reflection_data()
		{
			meta_enum NewEnum;
			constexpr_for<enum_min_max_range::enum_min_index, enum_min_max_range::enum_max_index>(
				[&]<auto Index>()
				{
					std::string_view sub_result = get_enum_value_name<EnumType, static_cast<EnumType>(Index)>();
					if (is_valid_enum_name(sub_result))
					{
						NewEnum.enum_infos.emplace_back(Index, sub_result);
					}
				});
			return NewEnum;
		}

		std::string_view get_name_from_value(enum_underlying_type value)
		{
			for (auto&& each_enum : enum_infos) 
			{
				if (each_enum.first == value)
					return each_enum.second;
			}
			// TODO: Throw Runtime Error?
			return {};
		}

		enum_underlying_type get_value_from_name(std::string_view name)
		{
			for (auto&& each_enum : enum_infos) 
			{
				if (each_enum.second == name)
					return each_enum.first;
			}
			// TODO: Throw Runtime Error?
			return {};
		}
	};

	class enum_manager
	{
	private:
		std::unordered_map<std::string_view, meta_enum> all_enum;

		template<typename EnumType>
		void register_enum(std::string_view enum_type_name)
		{
			all_enum.insert(std::make_pair(enum_type_name, meta_enum::make_enum_reflection_data<EnumType>()));
		}

	public:
		inline static enum_manager& get_instance()
		{
			return lazy_singleton<enum_manager>::get_instance();
		}

		template<typename EnumType>
		std::string_view get_enum_name(EnumType enum_value)
		{
			// we have string_view such like this: "enum RGB::Color",
			// but we just want "RGB::Color"
			const std::string_view enum_type_name = get_enum_class_name<EnumType>();
			// Search The Global Map
			auto cached_enum = all_enum.find(enum_type_name);
			if (cached_enum == all_enum.end()) {
				// Not Exist In Global Map
				// Add Reflection Data Into Global Map
				register_enum<EnumType>(enum_type_name);
			}
			// TODO: Should We Care About std::underlying_type_t<EnumType> And enum_underlying_type ?
			return all_enum[enum_type_name].get_name_from_value(static_cast<enum_underlying_type>(enum_value));
		}

		template<typename EnumType>
		EnumType get_enum_value(std::string_view enum_name)
		{
			const std::string_view enum_type_name = get_enum_class_name<EnumType>();
			const auto cached_enum = all_enum.find(enum_type_name);
			// TODO: Throw Runtime Error?
			if (cached_enum == all_enum.end())
				return EnumType{};
			return static_cast<EnumType>(cached_enum->second.get_value_from_name(enum_name));
		}

	public:
		/**
		 * \brief Register Meta_enum Data, Call By MACRO Automatically
		 */
		template<typename EnumType>
		void register_enum()
		{
			const std::string_view enum_type_name = get_enum_class_name<EnumType>();
			register_enum<EnumType>(enum_type_name);
		}
	};
}


