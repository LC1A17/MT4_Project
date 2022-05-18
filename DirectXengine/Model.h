#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
#include <d3dx12.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Mesh.h"

//�m�[�h
struct Node
{
	//���O
	std::string name;
	//���[�J���X�P�[��
	DirectX::XMVECTOR scaling = { 1, 1, 1, 0 };
	//���[�J����]�p
	DirectX::XMVECTOR rotation = { 0, 0, 0, 0 };
	//���[�J���ړ�
	DirectX::XMVECTOR translation = { 0, 0, 0, 1 };
	//���[�J���ό`�s��
	DirectX::XMMATRIX transform;
	//�O���[�o���ό`�s��
	DirectX::XMMATRIX globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
};

//���f��
class Model
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;

	//std::���ȗ�
	using string = std::string;
	template <class T> using vector = std::vector<T>;

public://�T�u�N���X
	//���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos;//XYZ���W
		DirectX::XMFLOAT3 normal;//�@���x�N�g��
		DirectX::XMFLOAT2 uv;//UV���W
	};

public://�t�����h�N���X
	friend class FbxLoader;

private:
	static const std::string baseDirectory;

private://�ÓI�����o�ϐ�
	static ID3D12Device* dev;//�f�o�C�X
	static UINT descriptorHandleIncrementSize;//�f�X�N���v�^�T�C�Y

public://�ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* dev);//�ÓI������
	static Model* CreateFromOBJ(const std::string& modelname);//OBJ�t�@�C�����烁�b�V������

public://�����o�֐�
	~Model();//�f�X�g���N�^
	void Initialize(const std::string& modelname);//����������
	void Draw(ID3D12GraphicsCommandList* cmdList);//�`�揈��

	//�o�b�t�@����
	void CreateBuffers(ID3D12Device* dev);

	//���f���̕ό`�s��擾
	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }

private://�����o�ϐ�
	std::string name;//���O
	std::vector<Node> nodes;//�m�[�h�z��
	Node* meshNode = nullptr;//���b�V�������m�[�h
	std::vector<VertexPosNormalUv> vertices;//���_�f�[�^�z��
	std::vector<unsigned short> indices;//���_�C���f�b�N�X�z��
	DirectX::XMFLOAT3 ambient = { 1, 1, 1 };//�A���r�G���g�W��
	DirectX::XMFLOAT3 diffuse = { 1, 1, 1 };//�f�B�t���[�Y�W��
	DirectX::TexMetadata metadata = {};//�e�N�X�`�����^�f�[�^
	DirectX::ScratchImage scratchImg = {};//�X�N���b�`�C���[�W

	std::vector<Mesh*> meshes;//���b�V���R���e�i
	std::unordered_map<std::string, Material*> materials;//�}�e���A���R���e�i
	Material* defaultMaterial = nullptr;//�f�t�H���g�}�e���A��
	ComPtr<ID3D12DescriptorHeap> descHeap;//�f�X�N���v�^�q�[�v

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

private://�����o�֐�
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);//�}�e���A���ǂݍ���
	void AddMaterial(Material* material);//�}�e���A���o�^
	void CreateDescriptorHeap();//�f�X�N���v�^�q�[�v�̐���
	void LoadTextures();//�e�N�X�`���ǂݍ���

};