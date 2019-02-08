#include "GameEntity.h"




void GameEntity::SetTranslation(const float x, const float y, const float z)
{
	translate.x = x;
	translate.y = y;
	translate.z = z;
}

void GameEntity::SetScale(const float x, const float y, const float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void GameEntity::SetRotationX(const float x)
{
	rotateX = x;
}

void GameEntity::SetRotationY(const float y)
{
	rotateY = y;
}

void GameEntity::SetRotationZ(const float z)
{
	rotateZ = z;
}

const XMFLOAT4X4 GameEntity::GetWorldMatrix()
{
	XMStoreFloat4x4(&worldMat, XMMatrixIdentity());
	XMMATRIX sca = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX trans = XMMatrixTranslation(translate.x, translate.y, translate.z);
	XMMATRIX rotx = XMMatrixRotationX(rotateX);
	XMMATRIX roty = XMMatrixRotationY(rotateY);
	XMMATRIX rotz = XMMatrixRotationZ(rotateZ);
	XMMATRIX world = sca * rotx * roty * rotz *trans;
	XMStoreFloat4x4(&worldMat, XMMatrixTranspose(world));
	return worldMat;
}

void GameEntity::PrepareMaterial(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, XMFLOAT4X4 worldMatrix, Material *& mat)
{
	mat->GetVertexShader()->SetMatrix4x4("world", worldMatrix);
	mat->GetVertexShader()->SetMatrix4x4("view", viewMatrix);
	mat->GetVertexShader()->SetMatrix4x4("projection", projectionMatrix);
	mat->GetVertexShader()->CopyAllBufferData();
	mat->GetVertexShader()->SetShader();
	mat->GetVertexShader()->SetShader();
}

GameEntity::GameEntity(Mesh *bMesh)
{
	this->bMesh = bMesh;
}


GameEntity::~GameEntity()
{
}

