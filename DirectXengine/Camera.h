#pragma once

#include <DirectXMath.h>
#include "Object3d.h"

//カメラ
class Camera
{
protected://エイリアス
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://メンバ関数
	//更新処理
	void Update();

	//視点座標の取得
	static const XMFLOAT3& GetEye() { return eye; }

	//視点座標の設定
	static void SetEye(XMFLOAT3 eye) { Camera::eye = eye; }

	//注視点座標の取得
	static const XMFLOAT3& GetTarget() { return target; }

	//注視点座標の設定
	static void SetTarget(XMFLOAT3 target) { Camera::target = target; }

	//ベクトルによる移動
	static void MoveVector(XMFLOAT3 move);
	static void MoveEyeVector(XMFLOAT3 move);

public://メンバ変数	
	//視点座標
	static XMFLOAT3 eye;
	
	//注視点座標
	static XMFLOAT3 target;
	
	// 上方向ベクトル
	static XMFLOAT3 up;

private://メンバ変数
	Object3d* object3d = nullptr;

};