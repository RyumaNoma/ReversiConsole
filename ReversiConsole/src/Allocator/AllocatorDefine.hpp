#pragma once
#include <cstddef>
#include <cstdint>
#include <iostream>
/// <summary>
/// ヒープ領域に実体を持つプールアロケータ．
/// </summary>
template<class BlockType>
class Allocator
{
private:
	union node_t
	{
		BlockType block;
		union node_t* next;
		node_t() {}
		~node_t() {}
	};
	using Node = union node_t;

	const std::size_t num_blocks_;
	Node* nodes_;
	Node* top_;
	std::size_t allocated_blocks_;
public:
	Allocator() = delete;

	/// <summary>
	/// コンストラクタ．ヒープ領域のメモリを確保する
	/// </summary>
	/// <param name="num_blocks">確保するブロックの数</param>
	Allocator(std::size_t num_blocks);

	~Allocator();

	/// <summary>
	/// O(ブロック数)
	/// 初期化する．
	/// 確保されているブロックをすべて解放する
	/// </summary>
	void Init();

	/// <summary>
	/// O(1)で実体から領域を確保する．
	/// 確保できなかったらnullptrを返す
	/// </summary>
	/// <returns>確保した領域の先頭アドレス</returns>
	BlockType* Allocate();

	/// <summary>
	/// O(1)で確保されている領域を解放する．
	/// nullptrが渡された場合，falseを返す．
	/// 不正なアドレスが渡された場合は未定義．
	/// </summary>
	/// <param name="block_addr">解放するブロックの先頭アドレス</param>
	/// <returns>解放に成功したらtrue</returns>
	/// TODO: int Deallocate(BlockType& block)高速化
	bool Deallocate(BlockType* block_addr);

	/// <summary>
	/// O(1)で確保されているブロックの数を求める．
	/// </summary>
	/// <returns>ブロックの数</returns>
	std::size_t CountBlocks() const;

	friend std::ostream& operator<<(std::ostream& os, const Allocator& allocator);
};