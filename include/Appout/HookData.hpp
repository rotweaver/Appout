#pragma once

#include "CConv.hpp"

#include "Trampoline.hpp"
#include "OpCode.hpp"

#include <cstdint>
#include <array>

#include <Appout/Process.hpp>
#include <Appout/HookManager.hpp>

#include <cstring>

#include <iostream>

#include <Windows.h>

#include <mhde32.hpp>

#include <format>

namespace Appout
{
	// OLD DONT USE!!!
	uint32_t getEAX();
	uint32_t getECX();

	constexpr uint32_t PrologueLength = 16;


	template<typename Address>
	class HookData
	{
	private:

		std::uintptr_t m_address = 0;
		std::array<uint8_t, PrologueLength> m_prologue = { };



		ICConv* m_cconv = nullptr;

	public:
		std::uintptr_t m_trampoline = 0;

		HookData(uint32_t address);
		~HookData();

		uintptr_t GetAddress() const;
		uintptr_t GetTrampoline() const
		{
			return m_trampoline;
		}
		ICConv* GetCConv() const;

		const std::array<uint8_t, PrologueLength>& GetPrologue() const;

		friend class HookManager;
	};


	template<typename Address>
	__declspec(naked) void __fastcall Logic()
	{
		uint32_t data;
		__asm
		{
			push  ebp; Save the stack - frame base pointer(of the calling function).
			mov   ebp, esp; Set the stack - frame base pointer to be the current location on the stack.
			sub   esp, 4; Grow the stack by N bytes to reserve space for local variables

			push ecx
		}
		data = reinterpret_cast<HookData<Address>*>(getEAX())->m_trampoline;
		// std::cout << "aaa" << std::endl;




		__asm
		{
			pop ecx
			pop eax

			mov   esp, ebp; Put the stack pointer back where it was when this function  was called.
			pop   ebp; Restore the calling function's stack frame.

			push eax
			ret
		}

		reinterpret_cast<void(__fastcall*)()>(data)();

		__asm
		{
			ret
		}
		//__asm
		//{
		//	; push ebp; save old stack frame.
		//	;  mov ebp, esp; initialize new stack frame.
		//	add ebp, 4
		//}
	}

	template<typename Address>
	HookData<Address>::HookData(uint32_t address)
	{

		//m_cconv = cconv;


		m_address = address;
		std::memcpy(&(*m_prologue.begin()), reinterpret_cast<void*>(m_address), PrologueLength);


		uint8_t nops[PrologueLength] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		Process::WriteMemory(m_address, nops, PrologueLength);


		Appout::x86::PUSH_imm32 psh;

		
		psh.OpCode = 0xb8;

		std::cout << std::format("THIS: {:#4X}", reinterpret_cast<uintptr_t>(this)) << std::endl;

		psh.Value = reinterpret_cast<uintptr_t>(this); // dangerous


		SIZE_T written = 0;

		auto result = WriteProcessMemory(
			GetCurrentProcess(),
			reinterpret_cast<LPVOID>(m_address),
			&psh,
			sizeof(Appout::x86::PUSH_imm32),
			&written
		);



		Appout::x86::JMP_REL jmp = { };

		int fuckYou = m_address;

		auto str = std::format("CREATED A HOOK AT: {:#4X}", m_address);

		std::cout << str << std::endl;

		jmp.Offset = Appout::x86::JMP_REL::CalculateOffset(m_address + sizeof(Appout::x86::PUSH_imm32), reinterpret_cast<std::uintptr_t>(Logic<Address>));
		written = 0;

		result = WriteProcessMemory(
			GetCurrentProcess(),
			reinterpret_cast<LPVOID>(m_address + sizeof(Appout::x86::PUSH_imm32)),
			&jmp,
			sizeof(Appout::x86::JMP_REL),
			&written
		);

		m_trampoline = TrampolineFactory::Get()->CreateTrampoline(m_prologue, m_address);
	}

	template<typename Address>
	HookData<Address>::~HookData()
	{
		// std::memcpy(reinterpret_cast<void*>(m_address), m_functionPrologue, 8); // Restore original
	}

	template<typename Address>
	uintptr_t HookData<Address>::GetAddress() const
	{
		return m_address;
	}

	template<typename Address>
	const std::array<uint8_t, PrologueLength>& HookData<Address>::GetPrologue() const
	{
		return m_prologue;
	}

	template<typename Address>
	ICConv* HookData<Address>::GetCConv() const
	{
		return m_cconv;
	}

}