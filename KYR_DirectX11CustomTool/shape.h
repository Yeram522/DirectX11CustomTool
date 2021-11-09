#pragma once
#include <iostream>
#include<algorithm>
#include <D3DX10math.h>
#include <d3dx11.h>
using namespace std;

enum class ANGLE {
	X,
	Y,
	Z
};

struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };//vertex posiiton
struct Position { int x, y, z; }; //shape position
typedef Position Dimension;

class Squere
{
public:
	VERTEX Vertices[7];
	ID3D11Buffer* pVBuffer;
	Position pos;
	Dimension dim;
	D3DXMATRIX matTrans, matScale, matRotate, matFinal;
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;

	bool isFilled;

	Squere(Position pos, Dimension dim, ID3D11DeviceContext* devcon, ID3D11Device* dev, bool isFilled = true)
		: pos(pos), dim(dim), devcon(devcon),dev(dev),isFilled(isFilled)
	{
		VERTEX OurVertices[] =
		{
			{pos.x - (float)dim.x / 2,pos.y + (float)dim.y / 2, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
			{pos.x + (float)dim.x / 2, pos.y + (float)dim.y / 2, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
			{pos.x - (float)dim.x / 2, pos.y - (float)dim.y / 2, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
			{pos.x + (float)dim.x / 2, pos.y + (float)dim.y / 2, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
			{pos.x + (float)dim.x / 2, pos.y - (float)dim.y / 2, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
			{pos.x - (float)dim.x / 2, pos.y - (float)dim.y / 2, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
			{pos.x - (float)dim.x / 2,pos.y + (float)dim.y / 2, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
		};

		copy(OurVertices, OurVertices + 7, Vertices);

		// create the vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 7;             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


		// copy the vertices into the buffer
		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
		memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
		devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer
	}

	ID3D11Buffer* const* getBuffer() { return &pVBuffer; }
	ID3D11Buffer* getBuffer(int n) { return pVBuffer; }
	D3DXMATRIX getMatTrans() { return matTrans; }
	D3DXMATRIX getMatScale() { return matScale; }
	D3DXMATRIX metGatRotate() { return matRotate; }

	void translate(FLOAT sx, FLOAT sy, FLOAT sz)
	{
		D3DXMatrixTranslation(&matTrans, sx, sy, sz);
	}

	void rotation(ANGLE type, FLOAT angle)
	{
		switch (type)
		{
		case ANGLE::X:
			D3DXMatrixRotationX(&matRotate, angle);
			break;
		case ANGLE::Y:
			D3DXMatrixRotationY(&matRotate, angle);
			break;
		case ANGLE::Z:
			D3DXMatrixRotationZ(&matRotate, angle);
			break;
		}
	}

	void scaling(FLOAT sx, FLOAT sy, FLOAT sz)
	{
		D3DXMatrixScaling(&matScale, sx, sy, sz);
	}

	D3DXMATRIX* update(D3DXMATRIX mat1,D3DXMATRIX matView, D3DXMATRIX matProjection)
	{
		matFinal = mat1 * matView * matProjection;

		return &matFinal;
	}

	D3DXMATRIX* update(D3DXMATRIX mat1, D3DXMATRIX mat2, D3DXMATRIX matView, D3DXMATRIX matProjection)
	{
		matFinal = (mat1 * mat2 ) * matView * matProjection;

		return &matFinal;
	}

	D3DXMATRIX* update(D3DXMATRIX mat1, D3DXMATRIX mat2, D3DXMATRIX mat3, D3DXMATRIX matView, D3DXMATRIX matProjection)
	{
		matFinal = (mat1 * mat2 * mat3) * matView * matProjection;

		return &matFinal;
	}

	void render()
	{
		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

		// select which primtive type we are using
		if (isFilled == true)devcon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		else
			devcon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

		// draw the vertex buffer to the back buffer
		devcon->Draw(7, 0);
	}
};