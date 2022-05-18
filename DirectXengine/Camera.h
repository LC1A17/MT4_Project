#pragma once

#include <DirectXMath.h>
#include "Object3d.h"

//�J����
class Camera
{
protected://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�����o�֐�
	//�X�V����
	void Update();

	//���_���W�̎擾
	static const XMFLOAT3& GetEye() { return eye; }

	//���_���W�̐ݒ�
	static void SetEye(XMFLOAT3 eye) { Camera::eye = eye; }

	//�����_���W�̎擾
	static const XMFLOAT3& GetTarget() { return target; }

	//�����_���W�̐ݒ�
	static void SetTarget(XMFLOAT3 target) { Camera::target = target; }

	//�x�N�g���ɂ��ړ�
	static void MoveVector(XMFLOAT3 move);
	static void MoveEyeVector(XMFLOAT3 move);

public://�����o�ϐ�	
	//���_���W
	static XMFLOAT3 eye;
	
	//�����_���W
	static XMFLOAT3 target;
	
	// ������x�N�g��
	static XMFLOAT3 up;

private://�����o�ϐ�
	Object3d* object3d = nullptr;

};