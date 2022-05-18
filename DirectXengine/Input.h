#pragma once

#include <Windows.h>
#include <wrl.h>
#include <dinput.h>
#include <DirectXMath.h>

#define DIRECTINPUT_VERSION     0x0800//DirectInputのバージョン指定

//入力クラス
class Input
{
private://エイリアス
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://メンバ関数
	void Initialize(HINSTANCE hInstance, HWND hwnd);//初期化処理
	void Update();//更新処理
	bool IsKey(BYTE KeyNumber);//キー判定
	bool IsKeyTrigger(BYTE KeyNumber);//キー判定（長押し不可）

private://メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE Key[256] = {};
	BYTE OldKey[256] = {};

};