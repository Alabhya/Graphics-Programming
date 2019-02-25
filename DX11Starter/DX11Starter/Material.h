#pragma once
#include <d3d11.h>
#include "simpleshader.h"

// For the DirectX Math library
using namespace DirectX;

class Material
{
public:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	
	SimpleVertexShader* & GetVertexShader();
	SimplePixelShader*  & GetPixelShader();
	Material(SimpleVertexShader*& vertexShader, SimplePixelShader*& pixelShader);
	~Material();
};

