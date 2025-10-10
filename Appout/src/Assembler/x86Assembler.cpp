#include <Appout/Assembler/x86Assembler.hpp>

using namespace Appout;

void x86Assembler::nop()
{
	m_memoryPool.CurrentBlock().Write((uint8_t)0x90);
}

/// <summary>
/// Call near, relative, displacement relative to next instruction
/// </summary>
void call_rel(uint32_t value)
{

}

void jmp_rel(uint32_t value)
{

}

void push_imm32(uint32_t value)
{

}