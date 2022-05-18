#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

#include "Model.h"

//3D�I�u�W�F�N�g
class Object3d
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
	//�萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		XMMATRIX mat;//3D�ϊ��s��
	};

public://�ÓI�����o�֐�
	static bool StaticInitialize(ID3D12Device* dev, int WIN_WIDTH, int WIN_HEIGHT);//�ÓI������
	static void CreateGraphicsPipeline();//�O���t�B�b�N�p�C�v���C���̐���
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);//�`��O����
	static void PostDraw();//�`��㏈��
	static Object3d* Create();//3D�I�u�W�F�N�g����
	
	//���_���W�̎擾
	static const XMFLOAT3& GetEye() { return eye; }
	
	//���_���W�̐ݒ�
	static void SetEye(XMFLOAT3 eye);
	
	//�����_���W�̎擾
	static const XMFLOAT3& GetTarget() { return target; }
	
	//�����_���W�̐ݒ�
	static void SetTarget(XMFLOAT3 target);

	//�J��������������
	static void InitializeCamera(int WIN_WIDTH, int WIN_HEIGHT);
	
	//�r���[�s����X�V
	static void UpdateViewMatrix();

private://�ÓI�����o�ϐ�
	static ID3D12Device* dev;//�f�o�C�X
	static ID3D12GraphicsCommandList* cmdList;//�R�}���h���X�g
	static ComPtr<ID3D12RootSignature> rootsignature;//���[�g�V�O�l�`��
	static ComPtr<ID3D12PipelineState> pipelinestate;//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static XMMATRIX matView;//�r���[�s��
	static XMMATRIX matProjection;//�ˉe�s��
	static XMFLOAT3 eye;//���_���W
	static XMFLOAT3 target;//�����_���W
	static XMFLOAT3 up;//������x�N�g��
	static XMMATRIX matBillboard;//�r���{�[�h�s��
	static XMMATRIX matBillboardY;//Y�����r���{�[�h�s��
	
public://�����o�֐�
	void Initialize();//����������
	void Update();//�X�V����
	void Draw();//�`�揈��

	//���W�̎擾
	const XMFLOAT3& GetPosition() { return position; }
	
	//���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	
	//��]�̎擾
	const XMFLOAT3& GetRotation() { return rotation; }
	
	//��]�̐ݒ�
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	
	//�X�P�[���̎擾
	const XMFLOAT3& GetScale() { return scale; }
	
	//�X�P�[���̐ݒ�
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	
	//���f���̃Z�b�g
	void SetModel(Model* model) { this->model = model; };

	//�r���{�[�h�̐ݒ�
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

private://�����o�ϐ�
	ComPtr<ID3D12Resource> constBuffB0;//�萔�o�b�t�@

	//�F
	XMFLOAT4 color = { 1,1,1,1 };

	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };

	//X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };

	//���[�J�����W
	XMFLOAT3 position = { 0,0,0 };

	//���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;

	//�e�I�u�W�F�N�g
	Object3d* parent = nullptr;
	
	//���f��
	Model* model = nullptr;
	
	//�r���{�[�h
	bool isBillboard = false;

};