#include <Steel/Appout/Assembler/AssemblerBase.hpp>

using namespace Appout;

void AssemblerBase::checkFitsInBlock()
{
	if (m_memoryPool.GetFreeSpace() >= m_currentWriteSize)
		return;

	// We need more space!
	
	if (m_memoryPool.GetTotalFreeSpace() >= m_currentWriteSize) // Is there even enough free space?
	{
		for (auto it = m_memoryPool.begin(); it != m_memoryPool.end(); it++)
		{
			if (it->GetFreeSpace() < m_currentWriteSize) // Does the current block have enough free space?
				continue;

			// Yes so copy

			m_memoryPool.CurrentBlock().Transfer(*it, m_currentWriteSize);
			return;
		}
	}

	auto lastBlock = m_memoryPool.CurrentBlock();

	m_memoryPool.AllocateBlock();
	lastBlock.Transfer(m_memoryPool.CurrentBlock(), m_currentWriteSize);
}


AssemblerBase::AssemblerBase(MemoryPoolBase& memoryPool) : m_memoryPool(memoryPool)
{

}

void AssemblerBase::Write(std::uint8_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::int8_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::uint16_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::int8_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::uint32_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::int32_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::uint64_t value) { writePrimitive(value); }
void AssemblerBase::Write(std::int64_t value) { writePrimitive(value); }
void AssemblerBase::Write(float value) { writePrimitive(value); }