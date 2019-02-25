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
	ID3D11ShaderResourceView* texture;
	ID3D11SamplerState* sampler;
	ID3D11ShaderResourceView* & GetTexture();
	ID3D11SamplerState* & GetSampler();

	
	SimpleVertexShader* & GetVertexShader();
	SimplePixelShader*  & GetPixelShader();
	Material(SimpleVertexShader*& vertexShader, SimplePixelShader*& pixelShader, ID3D11ShaderResourceView*& texture, ID3D11SamplerState*& sampler);
	~Material();
};

