#pragma once
#include <chrono>

/// <summary>
/// ���ԊǗ��p�N���X�D
/// std::chrono�̃��b�p�[
/// </summary>
class Timer
{
private:
	std::chrono::system_clock::time_point start_;
public:
	Timer();

	/// <summary>
	/// �J�n���Ԃ̃��Z�b�g�D
	/// </summary>
	void Reset();

	/// <summary>
	/// �~���b�P�ʂŌo�ߎ��Ԃ����߂�
	/// </summary>
	/// <returns>�O��Reset()���Ăяo���Ă���̌o�ߎ���</returns>
	std::chrono::milliseconds::rep ElapsedMilliseconds() const;

	/// <summary>
	/// �}�C�N���b�P�ʂŌo�ߎ��Ԃ����߂�
	/// </summary>
	/// <returns>�O��Reset()���Ăяo���Ă���̌o�ߎ���</returns>
	std::chrono::microseconds::rep ElapsedMicroseconds() const;
};