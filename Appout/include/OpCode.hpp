#pragma once

#include <cstdint>

namespace Appout
{
	namespace x86
	{
#pragma pack(push, 1)

		/// <summary>
		/// Call near, relative, displacement relative to next instruction
		/// </summary>
		struct CALL_REL
		{
			std::uint8_t OpCode = 0xE8;
			std::uint32_t Offset = 0;
			constexpr uint32_t static CalculateOffset(uintptr_t target, uintptr_t replacement) { return replacement - target - sizeof(CALL_REL); }
		};

		struct JMP_REL
		{
			std::uint8_t OpCode = 0xE9;
			std::uintptr_t Offset = 0x00;
			constexpr uint32_t static CalculateOffset(uintptr_t target, uintptr_t replacement) { return replacement - target - sizeof(JMP_REL); }
		};

		struct JMP_REL_SHORT
		{
			std::uint8_t OpCode = 0xEB;
			std::int8_t Offset = 0x00;
			constexpr uint32_t static CalculateOffset(uintptr_t target, uintptr_t replacement) { return replacement - target - sizeof(JMP_REL_SHORT); }
		};

		struct PUSH_imm32
		{
			std::uint8_t OpCode = 0x68;
			std::uint32_t Value = 0x00;
		};


		struct PUSH_ECX
		{
			std::uint8_t OpCode = 0x51;
		};
#pragma pack(pop)
	}
}