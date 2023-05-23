#pragma once
#include "Scene.hpp"
#include "BitBoard.hpp"
class Player;
class SceneManager;

// TODO: �Ƃɂ���MatchScene�N���X������������
// TODO: �R�����g����
class MatchScene
	: public Scene
{
public:
	MatchScene(SceneManager* manager);
	~MatchScene() = default;
	void OnChanged(const std::map<std::string, int>& param) override;
	void Draw() const override;
	void Update() override;
	
	void BeforeMatch();
	void Think();
	void PlayAnimation();
	
	void Init();
	void SetPlayers(Player* first_player, Player* second_player);

	/// <summary>
	/// �l�ԑ�����݂����ʂ����߂�D
	/// �O������F�������I�����Ă��邱��
	/// </summary>
	/// <returns>(�����F1)(���������F0)(�����F-1)</returns>
	int HumanResult() const;

	/// <summary>
	/// �����_�ł̐l�ԑ��̐΂̐������߂�
	/// </summary>
	/// <returns>�l�ԑ��̐΂̐�</returns>
	int HumanStones() const;

	/// <summary>
	/// �����_�ł�AI���̐΂̐������߂�
	/// </summary>
	/// <returns>AI���̐΂̐�</returns>
	int AIStones() const;

	// �`��
	void DrawBeforeMatch() const;
	void DrawThink() const;
	void DrawPlayAnimation() const;
	void DrawBoard(int window_width, int window_height) const;
	
	enum class MatchState
	{
		BeforeMatch,
		Think,
		PlayAnimation
	};
private:
	BitBoard last_board_;
	BitBoard board_;
	Player* player_[2];
	int turn_;// 0-indexed
	int count_frame_;
	MatchState state_;
	int human_side_;
	bool is_pass_;
};