#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	// �A�N�^�[�̏�ԊǗ��p
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	// �R���X�g���N�^�ƃf�X�g���N�^
	Actor(class Game* game);
	virtual ~Actor();

	// �Q�[������Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	// �A�N�^�[�����S�R���|�[�l���g���X�V(�I�[�o�[���C�h�s��)
	void UpdateComponents(float deltaTime);
	// �A�N�^�[�Ǝ��̍X�V����(�I�[�o�[���C�h�\)
	virtual void UpdateActor(float deltaTime);

	// �Q�b�^�[ / �Z�b�^�[
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// �R���|�[�l���g�̒ǉ� / ����
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// �A�N�^�[�̏��
	State mState;

	// ���W
	Vector2 mPosition;//���S���W
	float mScale;//�傫��(1.0f��100%)
	float mRotation;// ��]�̊p�x (���W�A��)

	std::vector<class Component*> mComponents;

	class Game* mGame;
};