#pragma once

#include <Windows.h>
#include <wrl.h>
#include <dinput.h>
#include <DirectXMath.h>

#define DIRECTINPUT_VERSION     0x0800//DirectInput�̃o�[�W�����w��

//���̓N���X
class Input
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�
	void Initialize(HINSTANCE hInstance, HWND hwnd);//����������
	void Update();//�X�V����
	bool IsKey(BYTE KeyNumber);//�L�[����
	bool IsKeyTrigger(BYTE KeyNumber);//�L�[����i�������s�j

private://�����o�ϐ�
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE Key[256] = {};
	BYTE OldKey[256] = {};

};