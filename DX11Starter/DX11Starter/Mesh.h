#pragma once
#include <d3d11.h>
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

class Mesh
{
private:
	int indexArrayCount;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
public:
	Mesh(Vertex *vertexArray, int  vertexArrayCount, int *indexArray, int  indexArrayCount, ID3D11Device* device);
	Mesh(const char* objFile, ID3D11Device* device);
	~Mesh();
	void CreateBuffer(Vertex * vertexArray, int vertexArrayCount, int * indexArray, int indexArrayCount, ID3D11Device * device);
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();	
	int GetIndexCount();
};

