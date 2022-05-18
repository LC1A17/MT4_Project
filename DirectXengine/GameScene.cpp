#include "GameScene.h"
#include "Model.h"
#include "Collision.h"
#include "FbxLoader.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace Microsoft;
using namespace std;
using namespace DirectX;

//コンストラクタ
GameScene::GameScene()
{

}

//デストラクタ
GameScene::~GameScene()
{
	delete(back);
	delete(Obj);
	delete(Obj2);
}

//初期化処理
void GameScene::Initialize(DxInit* dxInit, Input* input, Sound* sound)
{
	//nullptrチェック
	assert(dxInit);
	assert(input);
	assert(sound);

	this->dxInit = dxInit;
	this->input = input;
	this->sound = sound;

	//デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}

	//デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	//ここから追加
	srand(time(NULL));//乱数初期化

	//スプライト読み込み
	if (!Sprite::LoadTexture(1, L"Resources/image/back.png"))
	{
		assert(0);
	}

	//背景スプライト生成
	back = Sprite::Create(1, { 0.0f,0.0f });
	back->SetSize({ 1280, 720 });
	back->SetPosition({ 0.0f, 0.0f });

	//モデル読み込み、生成
	//モデル1
	model = model->CreateFromOBJ("player");
	Obj = Object3d::Create();
	Obj->SetModel(model);
	Obj->SetPosition({ posX, posY, 0 });
	Obj->SetScale({ 2, 2, 2 });

	//モデル2
	model = model->CreateFromOBJ("enemy");
	Obj2 = Object3d::Create();
	Obj2->SetModel(model);
	Obj2->SetPosition({ posX2, posY2, 0 });
	Obj2->SetScale({ 2, 2, 2 });

	//BGM.SE読み込み
	//soundData1 = sound->SoundLoadWave("Resources/sound/BGM.wav");
	//se0 = sound->SoundLoadWave("Resources/sound/SE0.wav");
	//se1 = sound->SoundLoadWave("Resources/sound/SE1.wav");
	//se2 = sound->SoundLoadWave("Resources/sound/SE2.wav");
	//se3 = sound->SoundLoadWave("Resources/sound/SE3.wav");
	//se4 = sound->SoundLoadWave("Resources/sound/SE4.wav");
	//sound->SoundPlayWave(soundData1);//サウンド再生

	//モデルを指定してファイル読み込み
	FbxLoader::GetInstance()->LoadModelFromFile("cube");

	camera->Update();//カメラ更新処理
}

//更新処理
void GameScene::Update()
{
	//ここに追加

	//1で進行開始
	if (input->IsKeyTrigger(DIK_1))
	{
		isStart = true;
	}

	//Rでリセット
	if (input->IsKeyTrigger(DIK_R))
	{
		isStart = false;
		posX = -40;
		posX2 = 40;
		v = 1;
		v2 = 1;
		isHit = false;
		Obj->SetPosition({ posX, posY, 0 });
		Obj2->SetPosition({ posX2, posY2, 0 });
	}

	//移動、反発処理
	if (isStart)
	{
		posX += v;
		posX2 -= v;
		Obj->SetPosition({posX, posY, 0 });
		Obj2->SetPosition({ posX2, posY2, 0 });
	}

	if (!isHit && posX == -2)
	{
		v = ((m * v) + (m2 * -v)) / (m + m2);
		isHit = true;
	}

	camera->SetEye(eye);//カメラ座標更新

	camera->Update();//カメラ更新処理
	
	//オブジェクト更新処理
	Obj->Update();
	Obj2->Update();
}

//描画処理
void GameScene::Draw()
{
	//コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxInit->GetCmdList();

	Sprite::PreDraw(cmdList);//スプライト描画前処理

	//ここに追加
	back->Draw();//背景

	Sprite::PostDraw();//スプライト描画後処理
	dxInit->ClearDepthBuffer();//深度バッファクリア

	Object3d::PreDraw(cmdList);//3Dオブジェクト描画前処理
	
	//ここに追加
	Obj->Draw();
	Obj2->Draw();

	Object3d::PostDraw();//3Dオブジェクト描画後処理

	Sprite::PreDraw(cmdList);//スプライト描画前処理

	//ここに追加

	debugText.DrawAll(cmdList);//デバッグテキストの描画
	Sprite::PostDraw();//スプライト描画後処理
}