#pragma once
#include <d3d11.h>
#include "Vertex.h"
#include "Mesh.h"

// For the DirectX Math library
using namespace DirectX;

class GameEntity
{
public:
	Mesh *bMesh;
	XMFLOAT4X4 worldMat;
	XMFLOAT3 translate = XMFLOAT3(0.0f,0.0f,0.0f);
	XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	float rotateX=0.0f;
	float rotateY=0.0f;
	float rotateZ=0.0f;
	   
	void SetTranslation(const float x,const  float y,const float z);
	void SetScale(const float x, const float y, const float z);
	void SetRotationX(const float x);
	void SetRotationY(const float y);
	void SetRotationZ(const float z);
	const XMFLOAT4X4 GetWorldMatrix();	
	GameEntity(Mesh *bMesh);
	~GameEntity();
};

