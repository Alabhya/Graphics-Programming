#include "Game.h"
#include "Vertex.h"


// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		// The application's handle
		"DirectX Game",	   	// Text for the window's title bar
		1280,			// Width of the window's client area
		720,			// Height of the window's client area
		true)			// Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;
	

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Release any (and all!) DirectX objects
	// we've made in the Game class
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;
	delete Mesh1;
	delete Mesh2;
	delete Mesh3;
	delete GameEntity1;
	delete GameEntity2;
	delete GameEntity3;
	delete GameEntity4;
	delete GameEntity5;	
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	/*// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)*/
	 // Transpose for HLSL!

	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	
	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex vertices1[] =
	{
		{ XMFLOAT3(+2.5f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+3.5f, +0.0f, +0.0f), red },
		{ XMFLOAT3(+2.5f, -1.0f, +0.0f), red},
	    { XMFLOAT3(+1.5f, +0.0f, +0.0f), red},
	};

	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	int indices1[] = { 0, 1, 2, 2, 3, 0 };


	Vertex vertices2[] = 
	{
			{ XMFLOAT3(-1.0f, +0.0f, +0.0f), blue },
			{ XMFLOAT3(+0.0f, +1.7f, +0.0f), blue },
			{ XMFLOAT3(+1.0f, +0.0f, +0.0f), blue},
			{ XMFLOAT3(-1.0f, +1.1f, +0.0f), blue},
	        { XMFLOAT3(+1.0f, +1.1f, +0.0f), blue },
	        { XMFLOAT3(+0.0f, -0.6f, +0.0f), blue }
	};

	int indices2[] = { 0, 1, 2, 3, 4, 5 };

	Vertex vertices3[] =
	{
		{ XMFLOAT3(-2.5f, +1.0f, +0.0f), green },
		{ XMFLOAT3(-1.5f, +0.0f, +0.0f), green },
		{ XMFLOAT3(-2.5f, -1.0f, +0.0f), green},
		{ XMFLOAT3(-3.5f, +0.0f, +0.0f), green},
	};

	int indices3[] = { 0, 1, 2, 2, 3, 0 };

	Mesh1 = new Mesh (vertices1,4,indices1,6,device);
	Mesh2 = new Mesh (vertices2,6,indices2,6,device);
	Mesh3 = new Mesh (vertices3,4,indices3,6,device);
	

	GameEntity1 = new GameEntity(Mesh1);
	GameEntity2 = new GameEntity(Mesh1);
	GameEntity3 = new GameEntity(Mesh2);
	GameEntity4 = new GameEntity(Mesh3);
	GameEntity5 = new GameEntity(Mesh3);

}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
	if (GetAsyncKeyState('W') & 0x8000)
	{
		cam.MoveForward(deltaTime);
		cam.Update();
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		cam.MoveBackward(deltaTime);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		cam.MoveLeft(deltaTime);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		cam.MoveRight(deltaTime);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		cam.MoveUp(deltaTime);
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		cam.MoveDown(deltaTime);
	}
	GameEntity1->SetRotationZ(totalTime);
	GameEntity2->SetTranslation(0.0f, (sin(5.0f * totalTime) + 2) / 5.0f, 0.0f);
	GameEntity3->SetScale((sin(5.0f * totalTime) + 2)/5.0f, (sin(5.0f * totalTime) +2)/5.0f ,(sin(5.0f * totalTime)+2)/5.0f);
	GameEntity4->SetRotationZ(-totalTime);
	GameEntity5->SetTranslation(0.0f, (sin(5.0f * totalTime) + 2) / 5.0f, 0.0f);
	GameEntity1->SetScale(0.7f,0.7f,0.7f);
	GameEntity2->SetScale(0.7f,0.7f,0.7f);
	GameEntity4->SetScale(0.7f, 0.7f, 0.7f);
	GameEntity5->SetScale(0.7f, 0.7f, 0.7f);
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(cam.Update()));
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(cam.Projection()));
	//Draw Calls for Individual Objects
	vertexShader->SetMatrix4x4("world", GameEntity1->GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();
	pixelShader->SetShader();
	/*GameEntity1->PrepareMaterial(viewMatrix, projectionMatrix, worldMatrix, mat);*/

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ID3D11Buffer* vertexBufferGame;
	ID3D11Buffer* indexBufferGame;
	vertexBufferGame = Mesh1->GetVertexBuffer();
	indexBufferGame = Mesh1->GetIndexBuffer();
	int tempIndex = Mesh1->GetIndexCount();
	context->IASetVertexBuffers(0, 1, &vertexBufferGame, &stride, &offset);
	context->IASetIndexBuffer(indexBufferGame, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		tempIndex,     
		0,     
		0);    

	vertexShader->SetMatrix4x4("world", GameEntity2->GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();
	pixelShader->SetShader();

	vertexBufferGame = Mesh1->GetVertexBuffer();
	indexBufferGame = Mesh1->GetIndexBuffer();
	tempIndex = Mesh1->GetIndexCount();
	context->IASetVertexBuffers(0, 1, &vertexBufferGame, &stride, &offset);
	context->IASetIndexBuffer(indexBufferGame, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		tempIndex,
		0,
		0);

	vertexShader->SetMatrix4x4("world", GameEntity3->GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();
	pixelShader->SetShader();

	vertexBufferGame = Mesh2->GetVertexBuffer();
	indexBufferGame = Mesh2->GetIndexBuffer();
	tempIndex = Mesh2->GetIndexCount();
	context->IASetVertexBuffers(0, 1, &vertexBufferGame, &stride, &offset);
	context->IASetIndexBuffer(indexBufferGame, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		tempIndex,
		0,
		0);

	vertexShader->SetMatrix4x4("world", GameEntity3->GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();
	pixelShader->SetShader();

	vertexBufferGame = Mesh2->GetVertexBuffer();
	indexBufferGame = Mesh2->GetIndexBuffer();
	tempIndex = Mesh2->GetIndexCount();
	context->IASetVertexBuffers(0, 1, &vertexBufferGame, &stride, &offset);
	context->IASetIndexBuffer(indexBufferGame, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		tempIndex,
		0,
		0);

	vertexShader->SetMatrix4x4("world", GameEntity4->GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();
	pixelShader->SetShader();

	vertexBufferGame = Mesh3->GetVertexBuffer();
	indexBufferGame = Mesh3->GetIndexBuffer();
	tempIndex = Mesh3->GetIndexCount();
	context->IASetVertexBuffers(0, 1, &vertexBufferGame, &stride, &offset);
	context->IASetIndexBuffer(indexBufferGame, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		tempIndex,
		0,
		0);

	vertexShader->SetMatrix4x4("world", GameEntity5->GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();
	pixelShader->SetShader();

	vertexBufferGame = Mesh3->GetVertexBuffer();
	indexBufferGame = Mesh3->GetIndexBuffer();
	tempIndex = Mesh3->GetIndexCount();
	context->IASetVertexBuffers(0, 1, &vertexBufferGame, &stride, &offset);
	context->IASetIndexBuffer(indexBufferGame, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		tempIndex,
		0,
		0);
	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	if ((buttonState & 0x0001 && x > prevMousePos.x)) 
	{
		cam.Rotate((float)x*0.00001f, 0.0f);
		
	}
	if ((buttonState & 0x0001 && x < prevMousePos.x))
	{
		cam.Rotate((float)x*-0.00001f, 0.0f);
		
	}
	if ((buttonState & 0x0001 && y > prevMousePos.y))
	{
		cam.Rotate(0.0f, (float)y*0.00001f);
		
	}
	if ((buttonState & 0x0001 && y < prevMousePos.y))
	{
		cam.Rotate(0.0f, (float)y*-0.00001f);
	}
	

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion