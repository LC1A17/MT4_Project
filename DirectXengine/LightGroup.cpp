#include "LightGroup.h"
#include <assert.h>

using namespace DirectX;

///�ÓI�����o�ϐ��̎���
ID3D12Device* LightGroup::dev = nullptr;

//����������
void LightGroup::StaticInitialize(ID3D12Device* dev)
{
	//�ď������`�F�b�N
	assert(!LightGroup::dev);

	//nullptr�`�F�b�N
	assert(dev);

	LightGroup::dev = dev;
}

//�C���X�^���X����
LightGroup* LightGroup::Create()
{
	//3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	LightGroup* instance = new LightGroup();
	//����������
	instance->Initialize();

	return instance;
}

//����������
void LightGroup::Initialize()
{
	//nullptr�`�F�b�N
	assert(dev);

	DefaultLightSetting();

	HRESULT result = S_FALSE;
	
	//�萔�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));

	if (FAILED(result))
	{
		assert(0);
	}

	//�萔�o�b�t�@�փf�[�^�]��
	TransferConstBuffer();
}

//�X�V����
void LightGroup::Update()
{
	//�l�̍X�V���������������萔�o�b�t�@�ɓ]������
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

//�`�揈��
void LightGroup::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

//�萔�o�b�t�@�]��
void LightGroup::TransferConstBuffer()
{
	HRESULT result = S_FALSE;

	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		//����
		constMap->ambientColor = ambientColor;
		//���s����
		for (int i = 0; i < DirLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (dirLights[i].IsActive())
			{
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap->dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			//���C�g�������Ȃ烉�C�g�F��0��
			else
			{
				constMap->dirLights[i].active = 0;
			}
		}
		//�_����
		for (int i = 0; i < PointLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (pointLights[i].IsActive())
			{
				constMap->pointLights[i].active = 1;
				constMap->pointLights[i].lightpos = pointLights[i].GetLightPos();
				constMap->pointLights[i].lightcolor = pointLights[i].GetLightColor();
				constMap->pointLights[i].lightatten = pointLights[i].GetLightAtten();
			}
			//���C�g�������Ȃ烉�C�g�F��0��
			else
			{
				constMap->pointLights[i].active = 0;
			}
		}
		//�X�|�b�g���C�g
		for (int i = 0; i < SpotLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (spotLights[i].IsActive())
			{
				constMap->spotLights[i].active = 1;
				constMap->spotLights[i].lightv = -spotLights[i].GetLightDir();
				constMap->spotLights[i].lightpos = spotLights[i].GetLightPos();
				constMap->spotLights[i].lightcolor = spotLights[i].GetLightColor();
				constMap->spotLights[i].lightatten = spotLights[i].GetLightAtten();
				constMap->spotLights[i].lightfactoranglecos = spotLights[i].GetLightFactorAngleCos();
			}
			//���C�g�������Ȃ烉�C�g�F��0��
			else
			{
				constMap->spotLights[i].active = 0;
			}
		}
		//�ۉe
		for (int i = 0; i < CircleShadowNum; i++)
		{
			//�L���Ȃ�ݒ��]��
			if (circleShadows[i].IsActive())
			{
				constMap->circleShadows[i].active = 1;
				constMap->circleShadows[i].dir = -circleShadows[i].GetDir();
				constMap->circleShadows[i].casterPos = circleShadows[i].GetCasterPos();
				constMap->circleShadows[i].distanceCasterLight = circleShadows[i].GetDistanceCasterLight();
				constMap->circleShadows[i].atten = circleShadows[i].GetAtten();
				constMap->circleShadows[i].factorAngleCos = circleShadows[i].GetFactorAngleCos();
			}
			//�����Ȃ�F��0��
			else
			{
				constMap->circleShadows[i].active = 0;
			}
		}
		constBuff->Unmap(0, nullptr);
	}
}

//�W���̃��C�g�ݒ�
void LightGroup::DefaultLightSetting()
{
	dirLights[0].SetActive(true);
	dirLights[0].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights[0].SetLightDir({ 0.0f, -1.0f, 0.0f, 0 });

	dirLights[1].SetActive(true);
	dirLights[1].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights[1].SetLightDir({ +0.5f, +0.1f, +0.2f, 0 });

	dirLights[2].SetActive(true);
	dirLights[2].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights[2].SetLightDir({ -0.5f, +0.1f, -0.2f, 0 });
}

//�����̃��C�g�F�Z�b�g
void LightGroup::SetAmbientColor(const XMFLOAT3& color)
{
	ambientColor = color;
	dirty = true;
}

//���s�����̗L���t���O�Z�b�g
void LightGroup::SetDirLightActive(int index, bool active)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetActive(active);
}

//���s�����̃��C�g�����Z�b�g
void LightGroup::SetDirLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetLightDir(lightdir);
	dirty = true;
}

//���s�����̃��C�g�F�Z�b�g
void LightGroup::SetDirLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetLightColor(lightcolor);
	dirty = true;
}

//�_�����̗L���t���O���Z�b�g
void LightGroup::SetPointLightActive(int index, bool active)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetActive(active);
}

//�_�����̃��C�g���W���Z�b�g
void LightGroup::SetPointLightPos(int index, const XMFLOAT3& lightpos)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightPos(lightpos);
	dirty = true;
}

//�_�����̃��C�g�F���Z�b�g
void LightGroup::SetPointLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightColor(lightcolor);
	dirty = true;
}

//�_�����̃��C�g���������W�����Z�b�g
void LightGroup::SetPointLightAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightAtten(lightAtten);
	dirty = true;
}

//�X�|�b�g���C�g�̗L���t���O���Z�b�g
void LightGroup::SetSpotLightActive(int index, bool active)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetActive(active);
}

//�X�|�b�g���C�g�̃��C�g�������Z�b�g
void LightGroup::SetSpotLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightDir(lightdir);
	dirty = true;
}

//�X�|�b�g���C�g�̃��C�g���W���Z�b�g
void LightGroup::SetSpotLightPos(int index, const XMFLOAT3& lightpos)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightPos(lightpos);
	dirty = true;
}

//�X�|�b�g���C�g�̃��C�g�F���Z�b�g
void LightGroup::SetSpotLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightColor(lightcolor);
	dirty = true;
}

//�X�|�b�g���C�g�̃��C�g���������W�����Z�b�g
void LightGroup::SetSpotLightAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightAtten(lightAtten);
	dirty = true;
}

//�X�|�b�g���C�g�̃��C�g�����p�x���Z�b�g
void LightGroup::SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightFactorAngle(lightFactorAngle);
	dirty = true;
}

//�ۉe�̗L���t���O���Z�b�g
void LightGroup::SetCircleShadowActive(int index, bool active)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetActive(active);
}

//�ۉe�̃L���X�^�[���W���Z�b�g
void LightGroup::SetCircleShadowCasterPos(int index, const XMFLOAT3& casterPos)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetCasterPos(casterPos);
	dirty = true;
}

//�ۉe�̕������Z�b�g
void LightGroup::SetCircleShadowDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetDir(lightdir);
	dirty = true;
}

//�ۉe�̃L���X�^�[�ƃ��C�g�̋������Z�b�g
void LightGroup::SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetDistanceCasterLight(distanceCasterLight);
	dirty = true;
}

//�ۉe�̋��������W�����Z�b�g
void LightGroup::SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetAtten(lightAtten);
	dirty = true;
}

//�ۉe�̌����p�x���Z�b�g
void LightGroup::SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetFactorAngle(lightFactorAngle);
	dirty = true;
}