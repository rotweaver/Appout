#pragma once

#include <cstdint>

#include "AssemblerBase.hpp"


namespace Appout
{
	class x86Assembler : public AssemblerBase
	{
	private:
	public:
		enum class OpCode
		{
			PUSH_R32 = 0x50,
			POP_R32 = 0x58,

			PUSH_IMM32 = 0x68,
			ADD_R32_IMM8,
			NOP = 0x90,
			MOV_R32_IMM32 = 0xB8,

			RET_IMM16 = 0xC2,
			RET = 0xC3,

			LOOP	= 0xE2,
			CALL_REL = 0xE8,
			JMP_REL = 0xE9,
		};
		enum class Register
		{
			EAX,
			ECX,
			EDX,
			EBX,
			ESP,
			EBP,
			ESI,
			EDI
		};
	
		void nop();

		/// <summary>
		/// Call near, relative, displacement relative to next instruction
		/// </summary>
		void call_rel(uint32_t value);
		void call_abs(uint32_t value);

		void jmp_rel(uint32_t value);
		void jmp_abs(uint32_t value);

		void push_imm32(uint32_t value);


		void push_r32(Register reg);
		void pop_r32(Register reg);
		void mov_r32_imm32(Register reg, uint32_t value);

		void push_EBP_PTR(int8_t offset);

		void mov_EBP_ESP();

		void add_r32_imm8(Register reg, int8_t value);

		void ret(uint16_t amount);
		void ret();

		void loop(int8_t startOffset);

	};
}
