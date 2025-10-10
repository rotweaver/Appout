#pragma once

#include <array>

#include "OpCode.hpp"

namespace Appout
{
	class TrampolineFactory
	{
	private:
		uintptr_t m_trampolineHeap = 0;
		uintptr_t m_trampolinePointer = 0;
		size_t m_size = 0;

		TrampolineFactory();

	public:
		static TrampolineFactory* Get();
		size_t GetSize() const;

		uintptr_t CreateTrampoline(const std::array<uint8_t, 16>& prologue, uint32_t address);
	};



}