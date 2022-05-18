#pragma once

#include <Windows.h>

//Windows
class WinInit
{
public://静的メンバ変数
	static const wchar_t TitleName[];//ゲームタイトル
	static const int WIN_WIDTH;//ウィンドウの横幅
	static const int WIN_HEIGHT;//ウィンドウの縦幅
	
public://静的メンバ関数
	HWND GetHwnd();//ウィンドウハンドルの取得
	
public://メンバ関数
	HINSTANCE GetInstance();//ウィンドウクラスの取得
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);//ウィンドウプロシージャ
	void CreateWIN();//ウィンドウの生成
	void DeleteWIN();//ウィンドウ破棄
	bool MessageLoop();//メッセージループ

private://メンバ変数
	WNDCLASSEX win{};//ウィンドウクラス
	HWND hwnd = nullptr;//ウィンドウハンドル

};