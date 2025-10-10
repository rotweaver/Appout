#pragma once

#include <cstdint>

#include "AssemblerBase.hpp"


namespace Appout
{
	class x86Assembler : public AssemblerBase
	{
	private:

	public:

		void nop();

		/// <summary>
		/// Call near, relative, displacement relative to next instruction
		/// </summary>
		void call_rel(uint32_t value);

		void jmp_rel(uint32_t value);

		void push_imm32(uint32_t value);

	};
}
