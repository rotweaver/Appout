#pragma once

#include <cstdint>
#include <vector>

#include "MemoryBlock.hpp"

namespace Appout
{
	class MemoryPoolBase
	{
	protected:
		std::vector<MemoryBlock> m_memoryBlocks = { };
		size_t m_defaultAllocationSize = 4096;
		size_t m_currentBlock = 0;

	public:

		struct Iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = MemoryBlock;
			using pointer = MemoryBlock*;
			using reference = MemoryBlock&;

			Iterator(pointer pointer);

			reference operator*();
			pointer operator->();

			Iterator& operator++();
			Iterator operator++(int);


			friend bool operator==(const Iterator& lhs, const Iterator& rhs) { lhs.m_pointer == rhs.m_pointer; }
			friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { lhs.m_pointer != rhs.m_pointer; }
		private:
			pointer m_pointer = nullptr;
		};

		Iterator begin();
		Iterator end();

		virtual void AllocateBlock() = 0;


		MemoryBlock& CurrentBlock();

		/// <summary>
		/// How many blocks have been allocated?
		/// </summary>
		/// <returns></returns>
		size_t GetBlockCount() const;

		size_t GetDefaultAllocationSize() const;

		/// <summary>
		/// How much free space does a block have?
		/// </summary>
		/// <param name="blockID"></param>
		/// <returns></returns>
		size_t GetFreeBlockSpace(size_t blockID) const;

		/// <summary>
		/// Get free space of current block
		/// </summary>
		/// <returns></returns>
		size_t GetFreeSpace() const;

		/// <summary>
		/// Get total free space
		/// </summary>
		/// <returns></returns>
		size_t GetTotalFreeSpace() const;
	};
}