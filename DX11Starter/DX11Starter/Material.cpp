#include "Material.h"



ID3D11ShaderResourceView *& Material::GetTexture()
{
	return texture;
}

ID3D11SamplerState *& Material::GetSampler()
{
	return sampler;
}

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

Material::Material(SimpleVertexShader*& vertexShader, SimplePixelShader*& pixelShader, ID3D11ShaderResourceView*& texture, ID3D11SamplerState*& sampler)
 {
	 this->vertexShader = vertexShader;
	 this->pixelShader = pixelShader;
	 this->texture = texture;
	 this->sampler = sampler;
}

Material::~Material()
{
}


