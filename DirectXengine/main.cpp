#include "WinInit.h"
#include "DxInit.h"
#include "Sound.h"
#include "GameScene.h"
//#include "fbxsdk.h"
#include "FbxLoader.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//FbxManager* fbxManager = FbxManager::Create();

	//WinInit
	WinInit* win = nullptr;
	win = new WinInit();
	win->CreateWIN();

	//DxInit
	DxInit* dxInit = nullptr;
	dxInit = new DxInit();
	dxInit->Initialize(win);

	GameScene* gameScene = nullptr;

	//入力関連
	Input* input = nullptr;
	input = new Input();
	input->Initialize(win->GetInstance(), win->GetHwnd());

	//サウンド
	Sound* sound = nullptr;
	sound = new Sound();
	sound->Initialize();
	
	//スプライト
	Sprite::StaticInitialize(dxInit->GetDev(), WinInit::WIN_WIDTH, WinInit::WIN_HEIGHT);

	//3Dオブジェクト
	Object3d::StaticInitialize(dxInit->GetDev(), WinInit::WIN_WIDTH, WinInit::WIN_HEIGHT);

	//FBX
	FbxLoader::GetInstance()->Initialize(dxInit->GetDev());

	//GameScene
	gameScene = new GameScene();
	gameScene->Initialize(dxInit, input, sound);

	//ゲームループ
	while (true)
	{
		//メッセージループ
		if (win->MessageLoop())
		{
			break;
		}

		//更新処理ここから
		input->Update();//Input更新
		gameScene->Update();//GameScene更新
		//更新処理ここまで

		//描画処理ここから
		dxInit->BeforeDraw();//描画開始
		gameScene->Draw();//GameScene描画
		dxInit->AfterDraw();//描画終了
		//描画処理ここまで

		//ESCで強制終了
		if (input->IsKey(DIK_ESCAPE))
		{
			break;
		}
	}

	//各種解放
	delete(gameScene);
	delete(sound);
	delete(input);
	delete(dxInit);
	FbxLoader::GetInstance()->Finalize();

	//ウィンドウの破棄
	win->DeleteWIN();
	delete(win);

	return 0;
}