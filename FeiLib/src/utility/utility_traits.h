#pragma once

/*
 * Is Type enum class?
 */
template<typename EnumType>
inline constexpr bool is_enum_class_v = std::is_enum_v<EnumType> &&
!std::is_convertible_v<EnumType, std::underlying_type_t<EnumType>>;



template<std::size_t Index, std::size_t I, std::size_t... Is>
struct index_sequence_element_impl : index_sequence_element_impl<Index - 1, Is...>
{
};

template<std::size_t I, std::size_t... Is>
struct index_sequence_element_impl<0, I, Is...>
{
	constexpr static std::size_t value = I;
};

template<std::size_t Index, typename>
struct index_sequence_element;

template<std::size_t Index, template<typename T, T...> typename IndexSequence, std::size_t... Is>
struct index_sequence_element<Index, IndexSequence<std::size_t, Is...>>
{
	static_assert(Index < sizeof...(Is), "Index Out Of Range");
	constexpr static std::size_t value = index_sequence_element_impl<Index, Is...>::value;
};

template<std::size_t Index, typename IndexSequenceType>
constexpr std::size_t index_sequence_element_v = index_sequence_element<Index, IndexSequenceType>::value;

template<std::size_t Index, std::size_t... Is>
constexpr std::size_t index_args_element_v = index_sequence_element_impl<Index, Is...>::value;



template<typename ArrayElementType, std::size_t Size, std::size_t Dimension, typename ArrayType = ArrayElementType[Size]>
struct multi_dimensional_arrays_impl : multi_dimensional_arrays_impl<ArrayElementType, Size, Dimension - 1, ArrayType[Size]>
{	
};

template<typename ArrayElementType, std::size_t Size, typename ArrayType>
struct multi_dimensional_arrays_impl<ArrayElementType, Size, 1, ArrayType>
{
	using type = ArrayType;
};

template<typename ArrayElementType, std::size_t Count, std::size_t Dimension>
struct multi_dimensional_arrays
{
	using type = typename multi_dimensional_arrays_impl<ArrayElementType, Count, Dimension>::type;
};


/*
 * Sample Code:
 * using ArrayType = multi_dimensional_arrays_t<int, 2, 5>
 * Now We Get ArrayType As int[2][2][2][2][2]
 */
template<typename ArrayElementType, std::size_t Count, std::size_t Dimension>
using multi_dimensional_arrays_t = typename multi_dimensional_arrays<ArrayElementType, Count, Dimension>::type;



template<typename ArrayType, std::size_t I, std::size_t... Is>
struct multi_dimensional_arrays_non_regular_reversed_impl : multi_dimensional_arrays_non_regular_reversed_impl<ArrayType[I], Is...>
{
};

template<typename ArrayType, std::size_t I>
struct multi_dimensional_arrays_non_regular_reversed_impl<ArrayType, I>
{
	using type = ArrayType[I];
};

template<typename ArrayElementType, std::size_t... Is>
struct multi_dimensional_arrays_non_regular_reversed
{
	static_assert(sizeof...(Is) > 0, "This Is Not An Array");
	using type = typename multi_dimensional_arrays_non_regular_reversed_impl<ArrayElementType, Is...>::type;
};

/*
 * Sample Code:
 * using ArrayTypeNonRegular = multi_dimensional_arrays_non_regular_reversed_t<int, 1, 2, 3, 4>;
 * Now We Get ArrayTypeNonRegular As int[4][3][2][1]
 */
template<typename ArrayElementType, std::size_t... Is>
using multi_dimensional_arrays_non_regular_reversed_t = typename multi_dimensional_arrays_non_regular_reversed<ArrayElementType, Is...>::type;



template<typename ArrayType, std::size_t Index, std::size_t... Is>
struct multi_dimensional_arrays_non_regular_impl : multi_dimensional_arrays_non_regular_impl<ArrayType[index_args_element_v<Index, Is...>], Index - 1, Is...>
{
};

template<typename ArrayType, std::size_t... Is>
struct multi_dimensional_arrays_non_regular_impl<ArrayType, 0, Is...>
{
	using type = ArrayType[index_args_element_v<0, Is...>];
};

template<typename ArrayElementType, std::size_t... Is>
struct multi_dimensional_arrays_non_regular
{
	static_assert(sizeof...(Is) > 0, "This Is Not An Array");
	using type = typename multi_dimensional_arrays_non_regular_impl<ArrayElementType, sizeof...(Is) - 1, Is...>::type;
};

/*
 * Sample Code:
 * using ArrayTypeNonRegular_Reverse = multi_dimensional_arrays_non_regular_t<int, 1, 2, 3, 4>;
 * Now We Get ArrayTypeNonRegular_Reverse As int[1][2][3][4]
 */
template<typename ArrayElementType, std::size_t... Is>
using multi_dimensional_arrays_non_regular_t = typename multi_dimensional_arrays_non_regular<ArrayElementType, Is...>::type;