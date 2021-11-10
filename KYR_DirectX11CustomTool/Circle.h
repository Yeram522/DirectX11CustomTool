#pragma once
#include "Shape.h"
#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */

class Circle : public Shape
{
private:
	VERTEX Vertices[90];// 30(얼마나 세밀하게 점 그릴지.)*3(삼각형꼭지점개수)= 90 
public:
	Circle(Position pos, float radius, ID3D11DeviceContext* devcon, ID3D11Device* dev, D3DXCOLOR c1, D3DXCOLOR c2, D3DXCOLOR c3, bool isFilled = true)
		: Shape(pos, devcon, dev, c1,c2,c3,isFilled)
	{
		float deltaTheta = 2 * M_PI / 30;
		for (int i = 0; i < 30; i++)
		{
			float theta = i * deltaTheta; // Theta is the angle for that triangle
			int index = 3 * i;
			Vertices[index + 0] = { pos.x+0.0f, pos.y+0.0f, 0.0f, Shape::getColors()[0] };
			Vertices[index + 1] = { pos.x+radius*(float)cos(theta),pos.y-radius*(float)sin(theta), 0.0f,  Shape::getColors()[1] };
			Vertices[index + 2] = { pos.x+radius*(float)cos(theta + deltaTheta), pos.y - radius*(float)sin(theta + deltaTheta), 0.0f,  Shape::getColors()[2] };
		
		}

		// create the vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 90;             // size is the VERTEX struct * 3
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
		devcon->Draw(90, 0);
	}

};