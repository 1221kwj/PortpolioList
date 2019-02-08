#include "stdafx.h"
#include "ModelKeyframe.h"

ModelKeyframe::ModelKeyframe() {}
ModelKeyframe::~ModelKeyframe() {}

XMFLOAT4X4 ModelKeyframe::GetInterpolatedMatrix( float time, bool bRepeat )
{
	UINT	index1 = 0;
	UINT	index2 = 0;
	float	interpolatedTime = 0.0f;

	CalcKeyframeIndex( time, bRepeat, index1, index2, interpolatedTime );

	return GetInterpolatedMatrix( index1, index2, interpolatedTime );
}

UINT ModelKeyframe::GetKeyframeIndex( float time )
{
	UINT start = 0;
	UINT end = frameCount - 1;

	if ( time >= transforms[ end ].Time ) return end;

	do
	{
		UINT middle = ( start + end ) / 2;

		if ( end - start <= 1 )
		{
			break;
		}
		else if ( transforms[ middle ].Time < time )
		{
			start = middle;
		}
		else if ( transforms[ middle ].Time > time )
		{
			end = middle;
		}
		else
		{
			start = middle;
			break;
		}
	} while ( ( end - start ) > 1 );

	return start;
}

void ModelKeyframe::CalcKeyframeIndex( float time, bool bRepeat, OUT UINT & index1, OUT UINT & index2, OUT float & interpolatedTime )
{
	index1 = index2 = 0;
	interpolatedTime = 0.0f;

	index1 = GetKeyframeIndex( time );

	if ( bRepeat == false )	index2 = ( index1 >= frameCount - 1 ) ? index1 : index1 + 1;
	else					index2 = ( index1 >= frameCount - 1 ) ? 0 : index1 + 1;

	if ( index1 >= frameCount - 1 )
	{
		index1 = index2 = frameCount - 1;

		interpolatedTime = 1.0f;
	}
	else
	{
		float time1 = time - transforms[ index1 ].Time;
		float time2 = transforms[ index2 ].Time - transforms[ index1 ].Time;

		interpolatedTime = time1 / time2;
	}
}

XMFLOAT4X4 ModelKeyframe::GetInterpolatedMatrix( UINT index1, UINT index2, float t )
{
	XMVECTOR s1				= XMLoadFloat3( &transforms[ index1 ].S );
	XMVECTOR s2				= XMLoadFloat3( &transforms[ index2 ].S );
	XMVECTOR scale			= XMVectorLerp( s1, s2, t );
	XMMATRIX S				= XMMatrixScalingFromVector( scale );

	XMVECTOR r1				= XMLoadFloat4( &transforms[ index1 ].R );
	XMVECTOR r2				= XMLoadFloat4( &transforms[ index2 ].R );
	XMVECTOR q				= XMQuaternionSlerp( r1, r2, t );
	XMMATRIX R				= XMMatrixRotationQuaternion( q );

	XMVECTOR t1				= XMLoadFloat3( &transforms[ index1 ].T );
	XMVECTOR t2				= XMLoadFloat3( &transforms[ index2 ].T );
	XMVECTOR translation	= XMVectorLerp( t1, t2, t );
	XMMATRIX T				= XMMatrixTranslationFromVector( translation );

	XMFLOAT4X4 mat = Math::IdentityMatrix();
	XMStoreFloat4x4( &mat, S * R * T );

	return mat;
}
