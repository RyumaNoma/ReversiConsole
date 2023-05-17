#pragma once
#include "AllocatorDefine.hpp"

// Allocator実装

template<class BlockType>
Allocator<BlockType>::Allocator(std::size_t num_blocks)
	: num_blocks_(num_blocks)
	, nodes_(new Node[num_blocks])
	, top_(&nodes_[0])
	, allocated_blocks_(0)
{
	Init();
}

template<class BlockType>
Allocator<BlockType>::~Allocator()
{
	delete[] nodes_;
}

template<class BlockType>
void Allocator<BlockType>::Init()
{
	for (int i = 0; i < num_blocks_ - 1; ++i)
	{
		nodes_[i].next = &nodes_[i + 1];
	}
	nodes_[num_blocks_ - 1].next = nullptr;

	top_ = &nodes_[0];
	allocated_blocks_ = 0;
}

template<class BlockType>
BlockType* Allocator<BlockType>::Allocate()
{
	// 未使用のブロックが存在しない場合
	if (top_ == nullptr)
	{
		return nullptr;
	}

	BlockType* r = &top_->block;
	top_ = top_->next;
	allocated_blocks_ += 1;

	return r;
}

template<class BlockType>
bool Allocator<BlockType>::Deallocate(BlockType* block)
{
	if (block == nullptr) return false;

	reinterpret_cast<Node*>(block)->next = top_;
	top_ = reinterpret_cast<Node*>(block);
	allocated_blocks_ -= 1;
	return true;
}

template<class BlockType>
std::size_t Allocator<BlockType>::CountBlocks() const
{
	return allocated_blocks_;
}

template<class BlockType>
std::ostream& operator<<(std::ostream& os, const Allocator<BlockType>& allocator)
{
	os << "Number of blocks: " << allocator.num_blocks_
		<< "Block Size: " << sizeof(BlockType) << "[byte]"
		<< "Allocated blocks: " << allocator.CountBlocks();
	return os;
}