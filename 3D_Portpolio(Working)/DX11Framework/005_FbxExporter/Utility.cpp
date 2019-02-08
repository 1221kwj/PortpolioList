#include "stdafx.h"
#include "Utility.h"

XMFLOAT4X4 Fbx::Utility::Negative()
{
	XMMATRIX scaleX;
	scaleX = XMMatrixScaling( -1.0f, 1.0f, 1.0f );

	XMMATRIX rotation;
	rotation = XMMatrixRotationY( XMConvertToRadians( 180 ) );

	XMFLOAT4X4 mat;
	XMStoreFloat4x4( &mat, scaleX * rotation );

	return mat;
};

Vector2 Fbx::Utility::ToVector2( FbxVector2 & vec )
{
	return Vector2( ( float )vec.mData[ 0 ], ( float )vec.mData[ 1 ] );
}

Vector3 Fbx::Utility::ToVector3( FbxVector4 & vec )
{
	return Vector3( ( float )vec.mData[ 0 ], ( float )vec.mData[ 1 ], ( float )vec.mData[ 2 ] );
}

Vector3 Fbx::Utility::ToVector3( FbxDouble3 & vec )
{
	return Vector3( ( float )vec.mData[ 0 ], ( float )vec.mData[ 1 ], ( float )vec.mData[ 2 ] );
}

Vector4 Fbx::Utility::ToColor( FbxVector4 & vec )
{
	return Vector4( ( float )vec.mData[ 0 ], ( float )vec.mData[ 1 ], ( float )vec.mData[ 2 ], 1 );
}

Vector4 Fbx::Utility::ToColor( FbxPropertyT<FbxDouble3>& vec, FbxPropertyT<FbxDouble>& factor )
{
	FbxDouble3 color = vec;

	Vector4 result;
	result.x = ( float )color.mData[ 0 ];
	result.y = ( float )color.mData[ 1 ];
	result.z = ( float )color.mData[ 2 ];
	result.w = ( float )factor;

	return result;
}

XMFLOAT4X4 Fbx::Utility::ToMatrix( FbxAMatrix & matrix )
{
	FbxVector4 r1 = matrix.GetRow( 0 );
	FbxVector4 r2 = matrix.GetRow( 1 );
	FbxVector4 r3 = matrix.GetRow( 2 );
	FbxVector4 r4 = matrix.GetRow( 3 );

	XMFLOAT4X4 origin = XMFLOAT4X4
	(
		( float )r1.mData[ 0 ], ( float )r1.mData[ 1 ], ( float )r1.mData[ 2 ], ( float )r1.mData[ 3 ],
		( float )r2.mData[ 0 ], ( float )r2.mData[ 1 ], ( float )r2.mData[ 2 ], ( float )r2.mData[ 3 ],
		( float )r3.mData[ 0 ], ( float )r3.mData[ 1 ], ( float )r3.mData[ 2 ], ( float )r3.mData[ 3 ],
		( float )r4.mData[ 0 ], ( float )r4.mData[ 1 ], ( float )r4.mData[ 2 ], ( float )r4.mData[ 3 ]
	);

	XMMATRIX o = XMLoadFloat4x4( &origin );
	XMMATRIX n = XMLoadFloat4x4( &Negative() );
	XMMATRIX r = n * o * n;

	XMFLOAT4X4 mat = Math::IdentityMatrix();

	XMStoreFloat4x4( &mat, r );

	return mat;
}

string Fbx::Utility::GetTextureFile( FbxProperty & prop )
{
	if ( prop.IsValid() == true )
	{
		if ( prop.GetSrcObjectCount() > 0 )
		{
			FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>();

			if ( texture != NULL )
				return string( texture->GetFileName() );
		}
	}

	return "";
}

string Fbx::Utility::GetMaterialName( FbxMesh * mesh, int polygonIndex, int cpIndex )
{
	FbxNode* node = mesh->GetNode();
	if ( node == NULL ) return "";

	FbxLayerElementMaterial* material = mesh->GetLayer( 0 )->GetMaterials();
	if ( material == NULL ) return "";


	FbxLayerElement::EMappingMode mappingMode = material->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = material->GetReferenceMode();

	int mappingIndex = -1;
	switch ( mappingMode )
	{
		case FbxLayerElement::eAllSame:			mappingIndex = 0				; break;
		case FbxLayerElement::eByPolygon:		mappingIndex = polygonIndex		; break;
		case FbxLayerElement::eByControlPoint:	mappingIndex = cpIndex			; break;
		case FbxLayerElement::eByPolygonVertex: mappingIndex = polygonIndex * 3	; break;
		default: assert( false ); break;
	}

	FbxSurfaceMaterial* findMaterial = NULL;
	if ( refMode == FbxLayerElement::eDirect )
	{
		if ( mappingIndex < node->GetMaterialCount() )
			findMaterial = node->GetMaterial( mappingIndex );
	}
	else if ( refMode == FbxLayerElement::eIndexToDirect )
	{
		FbxLayerElementArrayTemplate<int>& indexArr = material->GetIndexArray();

		if ( mappingIndex < indexArr.GetCount() )
		{
			int tempIndex = indexArr.GetAt( mappingIndex );

			if ( tempIndex < node->GetMaterialCount() )
				findMaterial = node->GetMaterial( tempIndex );
		}//if(mappingIndex)
	}//if(refMode)

	if ( findMaterial == NULL )
		return "";

	return findMaterial->GetName();
}

Vector2 Fbx::Utility::GetUv( FbxMesh * mesh, int cpIndex, int uvIndex )
{
	Vector2 result = Vector2( 0.0f, 0.0f );

	FbxLayerElementUV* uv = mesh->GetLayer( 0 )->GetUVs();
	if ( uv == NULL ) return result;


	FbxLayerElement::EMappingMode mappingMode = uv->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = uv->GetReferenceMode();

	switch ( mappingMode )
	{
		case FbxLayerElement::eByControlPoint:
		{
			if ( refMode == FbxLayerElement::eDirect )
			{
				result.x = ( float )uv->GetDirectArray().GetAt( cpIndex ).mData[ 0 ];
				result.y = ( float )uv->GetDirectArray().GetAt( cpIndex ).mData[ 1 ];
			}
			else if ( refMode == FbxLayerElement::eIndexToDirect )
			{
				int index = uv->GetIndexArray().GetAt( cpIndex );

				result.x = ( float )uv->GetDirectArray().GetAt( index ).mData[ 0 ];
				result.y = ( float )uv->GetDirectArray().GetAt( index ).mData[ 1 ];
			}
		}
		break;

		case FbxLayerElement::eByPolygonVertex:
		{
			result.x = ( float )uv->GetDirectArray().GetAt( uvIndex ).mData[ 0 ];
			result.y = ( float )uv->GetDirectArray().GetAt( uvIndex ).mData[ 1 ];
		}
		break;
	}
	result.y = 1.0f - result.y;

	return result;
}
