#include "Material.h"



SimpleVertexShader *& Material::GetVertexShader()
{
	// TODO: insert return statement here
	return vertexShader;
}

SimplePixelShader *& Material::GetPixelShader()
{
	// TODO: insert return statement here
	return pixelShader;
}

void Material::LoadShaders(ID3D11Device* &device, ID3D11DeviceContext * &context)
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}

Material::Material()
{
	vertexShader = 0;
	pixelShader = 0;
}

Material::~Material()
{
	delete vertexShader;
	delete pixelShader;
}
