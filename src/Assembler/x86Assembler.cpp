#include <Appout/Assembler/x86Assembler.hpp>

using namespace Appout;



void x86Assembler::nop()
{
	m_memoryPool->CurrentBlock().Write((uint8_t)OpCode::NOP);
}


void x86Assembler::call_rel(uint32_t value)
{
	MemoryBlock& block = m_memoryPool->CurrentBlock();

	block.Write((uint8_t)OpCode::CALL_REL);
	block.Write(value);
}

void x86Assembler::call_abs(uint32_t value)
{
	MemoryBlock& block = m_memoryPool->CurrentBlock();

	block.Write((uint8_t)OpCode::CALL_REL);
	block.Write((value - block.GetCurrentAddress()) - 5);
}

void x86Assembler::jmp_rel(uint32_t value)
{
	MemoryBlock& block = m_memoryPool->CurrentBlock();

	block.Write((uint8_t)OpCode::JMP_REL);
	block.Write(value);
}
void x86Assembler::jmp_abs(uint32_t value)
{
	MemoryBlock& block = m_memoryPool->CurrentBlock();

	block.Write((uint8_t)OpCode::JMP_REL);
	block.Write((value - block.GetCurrentAddress()) - 5);
}

void x86Assembler::push_imm32(uint32_t value)
{
	MemoryBlock& block = m_memoryPool->CurrentBlock();

	block.Write((uint8_t)OpCode::PUSH_IMM32);
	block.Write(value);
}

void x86Assembler::push_r32(Register reg)
{

	m_memoryPool->CurrentBlock().Write((uint8_t)(0x50 + (uint8_t)reg));
}
void x86Assembler::pop_r32(Register reg)
{
	m_memoryPool->CurrentBlock().Write((uint8_t)(0x58 + (uint8_t)reg));
}
void x86Assembler::mov_r32_imm32(Register reg, uint32_t value)
{
	MemoryBlock& block = m_memoryPool->CurrentBlock();

	block.Write(static_cast<uint8_t>(static_cast<uint8_t>(OpCode::MOV_R32_IMM32) + static_cast<uint8_t>(reg)));
	block.Write(value);
}
void x86Assembler::mov_EBP_ESP()
{
	m_memoryPool->CurrentBlock().Write((uint16_t)0xEC8B);
}

void x86Assembler::push_EBP_PTR(int8_t offset)
{
	m_memoryPool->CurrentBlock().Write((uint16_t)0x75FF);
	m_memoryPool->CurrentBlock().Write(offset);
}

void x86Assembler::add_r32_imm8(Register reg, int8_t value)
{
	m_memoryPool->CurrentBlock().Write((uint8_t)OpCode::ADD_R32_IMM8);
	m_memoryPool->CurrentBlock().Write((uint8_t)(0xC0 + static_cast<uint8_t>(reg)));
	m_memoryPool->CurrentBlock().Write(value);
}
void x86Assembler::ret(uint16_t amount)
{
	m_memoryPool->CurrentBlock().Write((uint8_t)OpCode::RET_IMM16);
	m_memoryPool->CurrentBlock().Write((uint8_t)amount);
}
void x86Assembler::ret()
{
	m_memoryPool->CurrentBlock().Write((uint8_t)OpCode::RET);
}
void x86Assembler::loop(int8_t startOffset)
{
	m_memoryPool->CurrentBlock().Write((uint8_t)OpCode::LOOP);
	m_memoryPool->CurrentBlock().Write(startOffset);
}