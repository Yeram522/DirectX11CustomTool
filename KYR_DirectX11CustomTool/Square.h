#pragma once
#include "shape.h"

class Square : public Shape
{
private:
	Dimension dim;
private:
	VERTEX Vertices[7];

public:
	Square(Position pos, Dimension dim, ID3D11DeviceContext* devcon, ID3D11Device* dev, D3DXCOLOR c1, D3DXCOLOR c2, D3DXCOLOR c3, bool isFilled = true)
		: Shape(pos, devcon, dev, c1, c2, c3, isFilled), dim(dim)
	{
		VERTEX OurVertices[] =
		{
			{pos.x - (float)dim.x / 2,pos.y + (float)dim.y / 2, 0.0f, Shape::getColors()[0]},
			{pos.x + (float)dim.x / 2, pos.y + (float)dim.y / 2, 0.0f, Shape::getColors()[1]},
			{pos.x - (float)dim.x / 2, pos.y - (float)dim.y / 2, 0.0f, Shape::getColors()[0]},
			{pos.x + (float)dim.x / 2, pos.y + (float)dim.y / 2, 0.0f, Shape::getColors()[1]},
			{pos.x + (float)dim.x / 2, pos.y - (float)dim.y / 2, 0.0f, Shape::getColors()[2]},
			{pos.x - (float)dim.x / 2, pos.y - (float)dim.y / 2, 0.0f,  Shape::getColors()[0]},
			{pos.x - (float)dim.x / 2,pos.y + (float)dim.y / 2, 0.0f,  Shape::getColors()[0]}
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
		memcpy(ms.pData, Vertices, sizeof(Vertices));                 // copy the data
		devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer
	}

	void render() override
	{
		Shape::render();
		// draw the vertex buffer to the back buffer
		devcon->Draw(7, 0);
	}
};