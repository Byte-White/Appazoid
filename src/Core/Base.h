#pragma once
#include "PlatformDetection.h"
#include "Input.h"
#include "KeyCodes.h"
#include "MouseCodes.h"
#include "../Logging/Log.h"
#include <memory>
#include <functional>


#define BIT(n) (1<<n)

#define AZ_BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define AZ_BIND_EVENT_FN(fn) AZ_BIND_FN(fn)
#define AZ_BIND_CALLBACK_FN(fn) AZ_BIND_FN(fn)

namespace az
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Types>
	Ref<T> make_ref(Types&&... Args)
	{
		return std::make_shared<T>(std::forward<Types>(Args)...);
	}


	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Types>
	Scope<T> make_scope(Types&&... Args)
	{
		return std::make_unique<T>(std::forward<Types>(Args)...);
	}
}