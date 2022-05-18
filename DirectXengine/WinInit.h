#pragma once

#include <Windows.h>

//Windows
class WinInit
{
public://�ÓI�����o�ϐ�
	static const wchar_t TitleName[];//�Q�[���^�C�g��
	static const int WIN_WIDTH;//�E�B���h�E�̉���
	static const int WIN_HEIGHT;//�E�B���h�E�̏c��
	
public://�ÓI�����o�֐�
	HWND GetHwnd();//�E�B���h�E�n���h���̎擾
	
public://�����o�֐�
	HINSTANCE GetInstance();//�E�B���h�E�N���X�̎擾
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);//�E�B���h�E�v���V�[�W��
	void CreateWIN();//�E�B���h�E�̐���
	void DeleteWIN();//�E�B���h�E�j��
	bool MessageLoop();//���b�Z�[�W���[�v

private://�����o�ϐ�
	WNDCLASSEX win{};//�E�B���h�E�N���X
	HWND hwnd = nullptr;//�E�B���h�E�n���h��

};