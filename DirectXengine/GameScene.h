#pragma once

#include "DxInit.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Sound.h"
#include "Camera.h"
#include "CollisionPrimitive.h"

//�Q�[���V�[��
class GameScene
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�\����
	//���[�v����p
	enum Scene
	{
		Title, Game, Clear, GameOver
	};

private://�ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public://�����o�֐�
	//�R���X�g���N�^
	GameScene();

	//�f�X�g���N�^
	~GameScene();

	//����������
	void Initialize(DxInit* dxInit, Input* input, Sound* sound);

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

private://�����o�ϐ�
	DxInit* dxInit = nullptr;
	Input* input = nullptr;
	Sound* sound = nullptr;
	Model* model = nullptr;
	Camera* camera = nullptr;
	DebugText debugText;

	Sound::SoundData soundData1;//BGM
	Sound::SoundData se0;//SE
	Sound::SoundData se1;//SE
	Sound::SoundData se2;//SE
	Sound::SoundData se3;//SE
	Sound::SoundData se4;//SE

	Sprite* back = nullptr;//�w�i

	Object3d* Obj = nullptr;//�I�u�W�F�N�g1
	Object3d* Obj2 = nullptr;//�I�u�W�F�N�g2

	XMFLOAT3 eye = { 0, 10, -50 };//�J�������W
	XMFLOAT3 pPos = { 0, 0, 0 };//�v���C���[���W

	float m = 1;//�y���M���̎���
	float m2 = 2;//�V���N�}�̎���
	float v = 1;//�y���M���̑��x
	float v2 = 1;//�V���N�}�̑��x
	float posX = -40.0f;//�y���M����Y���W
	float posY = 0.0f;//�y���M����Y���W
	float posX2 = 40.0f;//�V���N�}��Y���W
	float posY2 = 0.0f;//�V���N�}��Y���W
	bool isHit = false;//�Փ˔���
	bool isStart = false;//�i�s�t���O
};