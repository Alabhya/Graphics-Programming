#pragma once
#include <d3d11.h>
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

class Mesh
{
public:
	Vertex *vertexArray;
	int vertexArrayCount;
	int *indexArray;
	int indexArrayCount;
	Mesh(Vertex *vertexArray, int const &vertexArrayCount, int *indexArray, int const &indexArrayCount, ID3D11Device* &device);
	~Mesh();
private:
	int indexCount;
public:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	ID3D11Device*  device;
	int GetIndexCount();
};

