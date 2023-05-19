#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <vector>

class Point;

class BitBoard
{
private:
	using Board = std::uint64_t;
	using ShiftFunc = std::function<Board(Board, unsigned int)>;
	static const Board kHorizontalEdge;
	static const Board kVerticalEdge;
	static const Board kDiagonalEdge;
private:
	// [0] ... me
	// [1] ... opponent
	std::uint64_t board_[2];
private:
	/// <summary>
	/// ���V�t�g���Z���s��
	/// </summary>
	/// <param name="a">�V�t�g�����l</param>
	/// <param name="b">�V�t�g����r�b�g��</param>
	/// <returns>a��b�������V�t�g�����l</returns>
	static Board shl(Board a, std::uint32_t b);

	/// <summary>
	/// �E�V�t�g���Z���s��
	/// </summary>
	/// <param name="a">�V�t�g�����l</param>
	/// <param name="b">�V�t�g����r�b�g��</param>
	/// <returns>a��b�����E�V�t�g�����l</returns>
	static Board shr(Board a, std::uint32_t b);

	/// <summary>
	/// me�̐΂���A������opponent�̐΂�Ֆʌ`���ŋ��߂�.
	/// �J�n�ʒu����������ꍇ�ł����������삷��D
	/// �Ԃ����f�[�^�ɊJ�n�n�_�ƘA������7�ڂ̃}�X���܂܂�Ȃ����Ƃɒ��ӁD
	/// </summary>
	/// <param name="me">�����̔Ֆ�</param>
	/// <param name="mask">(�Ֆʂ̒[��\���}�X�N) and (�G�̔Ֆ�)</param>
	/// <param name="shift">shif(a,b) = a��b�r�b�g�V�t�g����֐�</param>
	/// <param name="n">�V�t�g����r�b�g��</param>
	/// <returns>me�̐΂���A������opponent�̐΂�1�Ƃ���Ֆ�</returns>
	static Board Line(Board me, Board mask, ShiftFunc shift, int n);

	/// <summary>
	/// me���̍��@���Ֆʌ`���ŋ��߂�
	/// </summary>
	/// <param name="me">�����̔Ֆ�</param>
	/// <param name="opponent">�G�̔Ֆ�</param>
	/// <returns>me���̍��@���1�Ƃ���Ֆ�</returns>
	static Board Legal(Board me, Board opponent);

	/// <summary>
	/// ���]����΂����߂�
	/// </summary>
	/// <param name="me">�����̔Ֆ�</param>
	/// <param name="opponent">�G�̔Ֆ�</param>
	/// <param name="point">me�����΂�u���ꏊ</param>
	/// <returns>���]����΂�1�Ƃ���Ֆ�</returns>
	static Board ReverseStones(Board me, Board opponent, Board position);

	/// <summary>
	/// action�Őݒu�����΂ɂ�锽�]��board_�ɔ��f������D
	/// �΂̐ݒu���s��
	/// </summary>
	/// <param name="action">�s���̓��e</param>
	void Reverse(Point action);
public:
	BitBoard();
	BitBoard(const BitBoard& bit_board);

	/// <summary>
	/// �Ֆʂ̏������D
	/// 4�̐΂�u��
	/// </summary>
	void Init();

	/// <summary>
	/// �s����Ֆʂɔ��f������D
	/// ���̍s�������@��ł��邩�̔�����s��
	/// </summary>
	/// <param name="action">�s���̓��e</param>
	/// <returns>action�����@��̏ꍇ�̂�true</returns>
	bool Act(Point action);

	/// <summary>
	/// �u���ꂽ�΂̐��𐔂���
	/// </summary>
	/// <param name="is_opponent">�����鑤�̃v���C���[���G���Ȃ�true</param>
	/// <returns>�u���ꂽ�΂̐�</returns>
	int CountStones(bool is_opponent) const;

	/// <summary>
	/// �����̏I������D�Е����p�X���Ă������͑���
	/// </summary>
	/// <returns>�������I�����Ă�����true�C����ȊO��false</returns>
	bool IsFinish() const;

	/// <summary>
	/// ���̔Ֆʂɑ΂��č��@��̗L���𒲂ׂ�
	/// </summary>
	/// <param name="player_side">�m�F���s�����̃v���C���[</param>
	/// <returns>���@�肪��ł�����Ȃ�true</returns>
	bool IsExistLegal() const;

	/// <summary>
	/// Legal�̃��b�p�[�֐�
	/// </summary>
	/// <param name="player_side">����</param>
	/// <returns>���@���1�Ƃ���Ֆ�</returns>
	Board LegalPublic() const;

	/// <summary>
	/// �������v���C���[�̍��@���񋓂���
	/// </summary>
	/// <returns>�������v���C���[�̍��@��</returns>
	std::vector<Point> LegalActions() const;

	/// <summary>
	/// �Ֆʂ̎������ƓG���̃R�}�����ւ���
	/// </summary>
	void Swap();

	/// <summary>
	/// �����̌��ʂ𔻒肷��
	/// �O������F�������I�����Ă��邱��
	/// </summary>
	/// <returns>�����F1, ���������F0.5, �����F0</returns>
	double Result() const;

	bool operator==(const BitBoard& bitboard) const;
	bool operator!=(const BitBoard& bitboard) const;

	friend std::ostream& operator<<(std::ostream& os, const BitBoard& bit_board);
	friend class MatchScene;
};

