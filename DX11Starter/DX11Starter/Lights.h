#pragma once

#include <DirectXMath.h>

// --------------------------------------------------------
// A custom Light definition
// --------------------------------------------------------
struct DirectionalLight
{
	DirectX::XMFLOAT4 AmbientColor;	    
	DirectX::XMFLOAT4 Diffusecolor;
	DirectX::XMFLOAT3 Direction;	   
};


struct PointLight

{

	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 position;

};