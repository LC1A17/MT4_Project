#include "Camera.h"

using namespace DirectX;

XMFLOAT3 Camera::eye = { 0, 10, -50 };//���_���W
XMFLOAT3 Camera::target = { 0, 0, 0 };//�����_���W
XMFLOAT3 Camera::up = { 0, 1, 0 };//������x�N�g��

//�X�V����
void Camera::Update()
{
	//���_���W�̐ݒ�
	object3d->SetEye(eye);

	//�����_���W�̐ݒ�
	object3d->SetTarget(target);
}

//�x�N�g���ɂ��ړ�
void Camera::MoveVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

//�x�N�g���ɂ��ړ�
void Camera::MoveEyeVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}