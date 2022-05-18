#pragma once

#include "Camera.h"
#include "Input.h"

//�f�o�b�O�p�J����
class DebugCamera : public Camera
{
protected://�G�C���A�X
	//DirectX::���ȗ�
	using XMMATRIX = DirectX::XMMATRIX;
public://�����o�֐�
	//�R���X�g���N�^
	DebugCamera(int WIN_WIDTH, int WIN_HEIGHT, Input* input);

	//�X�V����
	void Update() override;

	void SetDistance(float distance) { this->distance = distance; viewDirty = true; }

private:
	//���̓N���X�̃|�C���^
	Input* input;
	//�J���������_�܂ł̋���
	float distance = 20;
	//�X�P�[�����O
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	//��]�s��
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
};