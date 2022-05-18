#include "Camera.h"

using namespace DirectX;

XMFLOAT3 Camera::eye = { 0, 10, -50 };//視点座標
XMFLOAT3 Camera::target = { 0, 0, 0 };//注視点座標
XMFLOAT3 Camera::up = { 0, 1, 0 };//上方向ベクトル

//更新処理
void Camera::Update()
{
	//視点座標の設定
	object3d->SetEye(eye);

	//注視点座標の設定
	object3d->SetTarget(target);
}

//ベクトルによる移動
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

//ベクトルによる移動
void Camera::MoveEyeVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}