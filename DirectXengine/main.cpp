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

	//���͊֘A
	Input* input = nullptr;
	input = new Input();
	input->Initialize(win->GetInstance(), win->GetHwnd());

	//�T�E���h
	Sound* sound = nullptr;
	sound = new Sound();
	sound->Initialize();
	
	//�X�v���C�g
	Sprite::StaticInitialize(dxInit->GetDev(), WinInit::WIN_WIDTH, WinInit::WIN_HEIGHT);

	//3D�I�u�W�F�N�g
	Object3d::StaticInitialize(dxInit->GetDev(), WinInit::WIN_WIDTH, WinInit::WIN_HEIGHT);

	//FBX
	FbxLoader::GetInstance()->Initialize(dxInit->GetDev());

	//GameScene
	gameScene = new GameScene();
	gameScene->Initialize(dxInit, input, sound);

	//�Q�[�����[�v
	while (true)
	{
		//���b�Z�[�W���[�v
		if (win->MessageLoop())
		{
			break;
		}

		//�X�V������������
		input->Update();//Input�X�V
		gameScene->Update();//GameScene�X�V
		//�X�V���������܂�

		//�`�揈����������
		dxInit->BeforeDraw();//�`��J�n
		gameScene->Draw();//GameScene�`��
		dxInit->AfterDraw();//�`��I��
		//�`�揈�������܂�

		//ESC�ŋ����I��
		if (input->IsKey(DIK_ESCAPE))
		{
			break;
		}
	}

	//�e����
	delete(gameScene);
	delete(sound);
	delete(input);
	delete(dxInit);
	FbxLoader::GetInstance()->Finalize();

	//�E�B���h�E�̔j��
	win->DeleteWIN();
	delete(win);

	return 0;
}