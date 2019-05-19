#pragma once
#include "stdafx.h"

class GizmosBuffer : public ShaderBuffer
{
public:
	GizmosBuffer() : ShaderBuffer( &Data, sizeof( Struct ) )
	{
		Data.bCollision = false;
	}

	void SetCollision( const bool& bCollision ) { Data.bCollision = ( UINT )bCollision; }

	struct Struct
	{
		UINT		bCollision;
		D3DXVECTOR3 padding;
	} Data;
};