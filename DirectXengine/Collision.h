#pragma once

#include "CollisionPrimitive.h"

using namespace DirectX;

//�����蔻��w���p�[�N���X
class Collision
{
public:
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, XMVECTOR* inter = nullptr);//���ƕ��ʂ̓����蔻��
	static void ClosestPtPoint2Triangle(const XMVECTOR& point, const Triangle& triangle, XMVECTOR* closest);//�_�ƎO�p�`�̍ŋߐړ_�����߂�
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);//���Ɩ@���t���O�p�`�̓�����`�F�b�N
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, XMVECTOR* inter = nullptr);//���C�ƕ��ʂ̓����蔻��
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, XMVECTOR* inter = nullptr);//���C�Ɩ@���t���O�p�`�̓����蔻��
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, XMVECTOR* inter = nullptr);//���C�Ƌ��̓����蔻��
};