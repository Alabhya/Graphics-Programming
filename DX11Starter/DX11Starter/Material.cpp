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

Material::Material(SimpleVertexShader*& vertexShader, SimplePixelShader*& pixelShader)
 {
	 vertexShader = 0;
	 pixelShader = 0;
}

 Material::~Material()
{
	delete vertexShader;
	delete pixelShader;
}
