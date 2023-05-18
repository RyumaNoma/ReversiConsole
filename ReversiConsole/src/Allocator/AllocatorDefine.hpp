#pragma once
#include <cstddef>
#include <cstdint>
#include <iostream>
/// <summary>
/// �q�[�v�̈�Ɏ��̂����v�[���A���P�[�^�D
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
	/// �R���X�g���N�^�D�q�[�v�̈�̃��������m�ۂ���
	/// </summary>
	/// <param name="num_blocks">�m�ۂ���u���b�N�̐�</param>
	Allocator(std::size_t num_blocks);

	~Allocator();

	/// <summary>
	/// O(�u���b�N��)
	/// ����������D
	/// �m�ۂ���Ă���u���b�N�����ׂĉ������
	/// </summary>
	void Init();

	/// <summary>
	/// O(1)�Ŏ��̂���̈���m�ۂ���D
	/// �m�ۂł��Ȃ�������nullptr��Ԃ�
	/// </summary>
	/// <returns>�m�ۂ����̈�̐擪�A�h���X</returns>
	BlockType* Allocate();

	/// <summary>
	/// O(1)�Ŋm�ۂ���Ă���̈���������D
	/// nullptr���n���ꂽ�ꍇ�Cfalse��Ԃ��D
	/// �s���ȃA�h���X���n���ꂽ�ꍇ�͖���`�D
	/// </summary>
	/// <param name="block_addr">�������u���b�N�̐擪�A�h���X</param>
	/// <returns>����ɐ���������true</returns>
	/// TODO: int Deallocate(BlockType& block)������
	bool Deallocate(BlockType* block_addr);

	/// <summary>
	/// O(1)�Ŋm�ۂ���Ă���u���b�N�̐������߂�D
	/// </summary>
	/// <returns>�u���b�N�̐�</returns>
	std::size_t CountBlocks() const;

	friend std::ostream& operator<<(std::ostream& os, const Allocator& allocator);
};