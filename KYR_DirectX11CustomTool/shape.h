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

class Shape
{
private:
	Position pos;
	D3DXMATRIX matTrans, matScale, matRotate, matFinal;

protected:
	ID3D11Buffer* pVBuffer;
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;
	bool isFilled;
public:
	Shape(Position pos, ID3D11DeviceContext* devcon, ID3D11Device* dev, bool isFilled = true)
		: pos(pos),  devcon(devcon),dev(dev),isFilled(isFilled)
	{ }

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

	virtual void render() = 0 { }
};