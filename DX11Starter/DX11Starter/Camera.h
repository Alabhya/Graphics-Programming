#pragma once
#include <d3d11.h>
#include "Vertex.h"



// For the DirectX Math library
using namespace DirectX;

class Camera
{
public:
	XMFLOAT3 camPos = XMFLOAT3(0.0f, 0.0f, -5.0f);
	XMFLOAT3 camDir = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 camUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	float camRotX = 0.0f;
	float camRotY = 0.0f;
	float speed = 10.0f;
	Camera();
	~Camera();
	const XMMATRIX Update();
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
};
