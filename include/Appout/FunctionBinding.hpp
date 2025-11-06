#pragma once

#include "HookInfo.hpp"
#include <vector>
#include <utility>
#include "Log.hpp"
#include "Debug.hpp"
#include <format>

namespace Appout
{
	class IFunctionBinding
	{
	private:

	public:
		size_t GetStackSize() const;

	};

	template <typename Ret, typename...Args>
	class FunctionBinding : IFunctionBinding
	{
	public:
		using OrigType = Ret(*)(Args...);
		using CallbackType = Ret(*)(FunctionBinding<Ret, Args...>, Args...);

		FunctionBinding(uintptr_t address);
		FunctionBinding(OrigType orig);


		FunctionBinding<Ret, Args...>& operator +=(CallbackType function)
		{
			m_hooks.push_back(function);
			return *this;
		}
		FunctionBinding<Ret, Args...>& operator -=(CallbackType function)
		{
			return *this;
		}

		Ret operator()(Args... args)
		{
			if (m_hookIndex == m_hooks.size())
			{
				m_hookIndex = 0;

				if constexpr (std::is_same_v<void, Args...>)
				{
					if constexpr (std::is_same_v<void, Ret>)
						reinterpret_cast<OrigType>(m_hookInfo.GetAddress())();
					else
						return reinterpret_cast<OrigType>(m_hookInfo.GetAddress())();
				}
				else
				{
					if constexpr (std::is_same_v<void, Ret>)
						reinterpret_cast<OrigType>(m_hookInfo.GetAddress())(args...);
					else
						return reinterpret_cast<OrigType>(m_hookInfo.GetAddress())(args...);
				}
			}
			else
			{
				if constexpr (std::is_same_v<void, Args...>)
				{
					if constexpr (std::is_same_v<void, Ret>)
						m_hooks[m_hookIndex++](*this);
					else
						return m_hooks[m_hookIndex++](*this);
				}
				else
				{
					if constexpr (std::is_same_v<void, Ret>)
						m_hooks[m_hookIndex++](*this, args...);
					else
						return m_hooks[m_hookIndex++](*this, args...);
				}

			}
		}

		int GetHookCount()
		{
			return m_hooks.size();
		}

		size_t GetStackSize() const override
		{
			return m_paramStackSize;
		}

		void createWrapper();
	private:

		size_t m_paramStackSize = (sizeof(Args) + ...);
		HookInfo m_hookInfo;
		size_t m_hookIndex = 0;
		std::vector<CallbackType> m_hooks = { };
	};
}


template <typename Ret, typename...Args>
Appout::FunctionBinding<Ret, Args...>::FunctionBinding(uintptr_t address) : m_hookInfo(address)
{

}

template <typename Ret, typename...Args>
Appout::FunctionBinding<Ret, Args...>::FunctionBinding(OrigType orig) : m_hookInfo(reinterpret_cast<uintptr_t>(orig))
{

}

#include "Assembler/x86Assembler.hpp"

void fromCdecl(Appout::x86Assembler& ass, size_t paramSize)
{
	ass.push_r32(Appout::x86Assembler::Register::EBP);
	ass.mov_EBP_ESP();

	for (auto i = 0; i < paramSize; i++) // repush all args
	{
		ass.push_EBP_PTR((i + 1) * -4);
	}

	// call first in line?

	ass.ret();
}


template <typename Ret, typename...Args>
void Appout::FunctionBinding<Ret, Args...>::createWrapper()
{
	auto log = Appout::Log::Instance();


	log->WriteInfo(Appout::CurrentSourceLocation(), std::format("Param Pack Size: {}", (sizeof(Args) + ...)));
}