#pragma once

#include <cstdint>

#include "Predef.hpp"
#include "MemoryPool/Win32MemoryPool.hpp"

namespace Appout
{
	struct CallingConvention
	{
	public:
		enum
		{
			/// <summary>
			/// Standard C calling convention (Caller cleans stack)
			/// </summary>
			CDecl,
			/// <summary>
			/// Calling convention where "this" is moved into ECX, and other parameters are pushed to the stack (Callee cleans stack)
			/// </summary>
			ThisCall,
			/// <summary>
			/// Calling convention where param1 is moved into ECX, param2 is moved into EDX, and other parameters are pushed to the stack
			/// </summary>
			FastCall,
			/// <summary>
			/// Standard Windows calling convention (Callee cleans stack)
			/// </summary>
			STDCall,
		};
		
		using type = decltype(CDecl);

		type Value;
		CallingConvention(const type& value);
		CallingConvention(const CallingConvention& source);

		operator int();
		CallingConvention& operator=(type t);
		bool operator==(int other) const;
		bool operator==(const CallingConvention& other) const;
		const char* ToString() const;

		static void CreateWrapper(CallingConvention cconv, const std::vector<PrimitiveType>& params, MemoryPoolBase& memoryPool);

		static void AssembleWrapper(CallingConvention cconv, MemoryPoolBase& memoryPool);
		static void AssembleUnwrapper(type cconv, uint32_t paramCount);

	private:
		static void assembleThisCallWrapper(uint32_t paramCount);
		static void assembleThisCallUnwrapper(int32_t paramCount);

	};



}