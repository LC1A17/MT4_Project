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

//�R���X�g���N�^
GameScene::GameScene()
{

}

//�f�X�g���N�^
GameScene::~GameScene()
{
	delete(back);
	delete(Obj);
	delete(Obj2);
}

//����������
void GameScene::Initialize(DxInit* dxInit, Input* input, Sound* sound)
{
	//nullptr�`�F�b�N
	assert(dxInit);
	assert(input);
	assert(sound);

	this->dxInit = dxInit;
	this->input = input;
	this->sound = sound;

	//�f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}

	//�f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	//��������ǉ�
	srand(time(NULL));//����������

	//�X�v���C�g�ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/image/back.png"))
	{
		assert(0);
	}

	//�w�i�X�v���C�g����
	back = Sprite::Create(1, { 0.0f,0.0f });
	back->SetSize({ 1280, 720 });
	back->SetPosition({ 0.0f, 0.0f });

	//���f���ǂݍ��݁A����
	//���f��1
	model = model->CreateFromOBJ("player");
	Obj = Object3d::Create();
	Obj->SetModel(model);
	Obj->SetPosition({ posX, posY, 0 });
	Obj->SetScale({ 2, 2, 2 });

	//���f��2
	model = model->CreateFromOBJ("enemy");
	Obj2 = Object3d::Create();
	Obj2->SetModel(model);
	Obj2->SetPosition({ posX2, posY2, 0 });
	Obj2->SetScale({ 2, 2, 2 });

	//BGM.SE�ǂݍ���
	//soundData1 = sound->SoundLoadWave("Resources/sound/BGM.wav");
	//se0 = sound->SoundLoadWave("Resources/sound/SE0.wav");
	//se1 = sound->SoundLoadWave("Resources/sound/SE1.wav");
	//se2 = sound->SoundLoadWave("Resources/sound/SE2.wav");
	//se3 = sound->SoundLoadWave("Resources/sound/SE3.wav");
	//se4 = sound->SoundLoadWave("Resources/sound/SE4.wav");
	//sound->SoundPlayWave(soundData1);//�T�E���h�Đ�

	//���f�����w�肵�ăt�@�C���ǂݍ���
	FbxLoader::GetInstance()->LoadModelFromFile("cube");

	camera->Update();//�J�����X�V����
}

//�X�V����
void GameScene::Update()
{
	//�����ɒǉ�

	//1�Ői�s�J�n
	if (input->IsKeyTrigger(DIK_1))
	{
		isStart = true;
	}

	//R�Ń��Z�b�g
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

	//�ړ��A��������
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

	camera->SetEye(eye);//�J�������W�X�V

	camera->Update();//�J�����X�V����
	
	//�I�u�W�F�N�g�X�V����
	Obj->Update();
	Obj2->Update();
}

//�`�揈��
void GameScene::Draw()
{
	//�R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxInit->GetCmdList();

	Sprite::PreDraw(cmdList);//�X�v���C�g�`��O����

	//�����ɒǉ�
	back->Draw();//�w�i

	Sprite::PostDraw();//�X�v���C�g�`��㏈��
	dxInit->ClearDepthBuffer();//�[�x�o�b�t�@�N���A

	Object3d::PreDraw(cmdList);//3D�I�u�W�F�N�g�`��O����
	
	//�����ɒǉ�
	Obj->Draw();
	Obj2->Draw();

	Object3d::PostDraw();//3D�I�u�W�F�N�g�`��㏈��

	Sprite::PreDraw(cmdList);//�X�v���C�g�`��O����

	//�����ɒǉ�

	debugText.DrawAll(cmdList);//�f�o�b�O�e�L�X�g�̕`��
	Sprite::PostDraw();//�X�v���C�g�`��㏈��
}