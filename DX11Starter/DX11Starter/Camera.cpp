#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

const XMMATRIX Camera::Update()
{
	XMVECTOR defaultForward = XMLoadFloat3(&camDir);
	XMVECTOR defaultPos = XMLoadFloat3(&camPos);
	XMVECTOR defaultUp = XMLoadFloat3(&camUp);
	XMVECTOR camView;
	
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(camRotX, camRotY, 0.0f);
	camView = XMVector3Transform(defaultForward, camRotationMatrix);
	camView = XMVector3Normalize(camView);
	XMMATRIX viewMat = XMMatrixLookToLH(defaultPos, camView, defaultUp);

	return viewMat;
}

void Camera::MoveForward(float deltaTime)
{
	camPos.z += speed * deltaTime;
}

void Camera::MoveBackward(float deltaTime)
{
	camPos.z -= speed * deltaTime;
}

void Camera::MoveLeft(float deltaTime)
{
	camPos.x -= speed * deltaTime;
}

void Camera::MoveRight(float deltaTime)
{
	camPos.x += speed * deltaTime;
}

void Camera::MoveUp(float deltaTime)
{
	camPos.y += speed * deltaTime;
}

void Camera::MoveDown(float deltaTime)
{
	camPos.y -= speed * deltaTime;
}

void Camera::Rotate(float x,float y)
{
	    camRotX += x;
		camRotY += y;
}
const XMMATRIX Camera::Projection()
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	return P;
}
