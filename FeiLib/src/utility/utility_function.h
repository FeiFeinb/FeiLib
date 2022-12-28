#pragma once
#include "all_header.h"

template<typename ContainerType, typename ReturnResult, typename... Args>
struct function_params_visitor
{
	const ContainerType& params_container;

	const std::function<ReturnResult(Args...)>& callback;

	function_params_visitor(const ContainerType& in_params_container, const std::function<ReturnResult(Args...)>& in_callback)
		: params_container(in_params_container), callback(in_callback) {}

	template<std::size_t... Index>
	void operator()(std::index_sequence<Index...>)
	{
		callback(params_container[Index]...);
	}
};

/**
 * Sample Code:
 *	std::function<void(int, int, int)> call_back = [](int a, int b, int c) { std::cout << a + b + c << std::endl; };
 *	std::vector<int> params = { 4, 3, 2, 1, 0 };
 *	function_invoker{ call_back }(params);
 * And then we will get result 9
 * TODO: Should we consider update the invoker like this?
 *
	template<typename ReturnResult, typename... Args>
	static void InvokeDelegate(const std::function<ReturnResult(Args...)> Delegate, const std::vector<int>& ParamString)
	{
		auto Visitor = [&Delegate, &ParamString]<std::size_t... Index>(std::index_sequence<Index...>)
		{
			Delegate(ParamString[Index]...);
		};

		Visitor(std::make_index_sequence<sizeof...(Args)>{});
	}
 *
 */
template<typename ReturnResult, typename... Args>
struct function_invoker
{
	const std::function<ReturnResult(Args...)>& function;

	function_invoker(const std::function<ReturnResult(Args...)>& in_function) : function(in_function) {}

	template<typename ContainerType>
	void operator()(const ContainerType& params_container)
	{
		function_params_visitor(params_container, function)(std::make_index_sequence<sizeof...(Args)>{});
	}
};


