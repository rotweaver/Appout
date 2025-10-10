#include <Steel/Appout/Trampoline.hpp>
#include <Steel/Appout/Process.hpp>
#include <Steel/Appout/OpCode.hpp>

#include <Windows.h>
#include <mhde32.hpp>
#include <iostream>

using namespace Appout;




TrampolineFactory::TrampolineFactory()
{
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);

	m_size = system_info.dwPageSize;

	m_trampolineHeap = reinterpret_cast<uintptr_t>(VirtualAlloc(NULL, m_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

	DWORD dummy;
	VirtualProtect(reinterpret_cast<void*>(m_trampolineHeap), m_size, PAGE_EXECUTE_READWRITE, &dummy);

	std::memset(reinterpret_cast<void*>(m_trampolineHeap), 0xCC, m_size);

	m_trampolinePointer = m_trampolineHeap;
}

TrampolineFactory* TrampolineFactory::Get()
{
	static auto s_trampolineFactory = new TrampolineFactory();
	return s_trampolineFactory;
}

size_t TrampolineFactory::GetSize() const
{
	return m_size;
}


uintptr_t TrampolineFactory::CreateTrampoline(const std::array<uint8_t, 16>& prologue, uint32_t address)
{
    int instructionsToCopy = 0;


    uintptr_t trampolineAddr = m_trampolinePointer;

    while (true)
    {
        mhde32s hs;
        auto copySize = mhde32_disasm(&(*prologue.begin()) + instructionsToCopy, &hs);

        auto originalAddress = address + instructionsToCopy;

        uintptr_t absoluteImm = 0;

        if (hs.opcode == 0xE8) // CALL_REL
        {
            absoluteImm = (originalAddress + (sizeof(x86::CALL_REL))) + hs.imm.imm32;

            x86::CALL_REL call = { };

            call.Offset = x86::CALL_REL::CalculateOffset(trampolineAddr, absoluteImm) - instructionsToCopy; //absoluteImm - trampolineAddr + sizeof(x86::CALL_REL);
            Process::WriteMemory(m_trampolinePointer, &call, sizeof(x86::CALL_REL));
        }
        else
            Process::WriteMemory(m_trampolinePointer, &(*prologue.begin()) + instructionsToCopy, hs.len);
        
        instructionsToCopy += hs.len;
        m_trampolinePointer += hs.len;

        if (instructionsToCopy >= (sizeof(x86::JMP_REL) + sizeof(x86::PUSH_imm32)))
            break;
    }

    x86::JMP_REL jmp = { };

    auto jmpAddrr = ((address + instructionsToCopy) - (m_trampolinePointer));
    jmp.Offset = ((address + instructionsToCopy) - (m_trampolinePointer)) - sizeof(x86::JMP_REL);

    Process::WriteMemory(m_trampolinePointer, &jmp, sizeof(x86::JMP_REL));


    m_trampolinePointer = ((m_trampolinePointer + 7) & -8); // Round to up to nearest 8

    return trampolineAddr;
}