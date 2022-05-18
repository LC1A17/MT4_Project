#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <vector>

#include "Material.h"

//�`��f�[�^
class Mesh
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
	//���_�f�[�^�\���́i�e�N�X�`������j
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos;//XYZ���W
		XMFLOAT3 normal;//�@���x�N�g��
		XMFLOAT2 uv;//UV���W
	};

public://�ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device);//�ÓI������

private://�ÓI�����o�ϐ�
	static ID3D12Device* dev;//�f�o�C�X

public://�����o�֐�
	//���O���擾
	const std::string& GetName() { return name; }

	//���O���Z�b�g
	void SetName(const std::string& name);

	//���_�f�[�^�̒ǉ�
	void AddVertex(const VertexPosNormalUv& vertex);

	//���_�C���f�b�N�X�̒ǉ�
	void AddIndex(unsigned short index);

	//���_�f�[�^�̐����擾
	inline size_t GetVertexCount() { return vertices.size(); }

	//�}�e���A���̎擾
	Material* GetMaterial() { return material; }

	//�}�e���A���̊��蓖��
	void SetMaterial(Material* material);

	//�o�b�t�@�̐���
	void CreateBuffers();

	//���_�o�b�t�@�擾
	const D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return vbView; }

	//�C���f�b�N�X�o�b�t�@�擾
	const D3D12_INDEX_BUFFER_VIEW& GetIBView() { return ibView; }

	//�`�揈��
	void Draw(ID3D12GraphicsCommandList* cmdList);

private://�����o�ϐ�
	//���O
	std::string name;
	
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	
	//���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	
	//�}�e���A��
	Material* material = nullptr;

};