#pragma once

namespace Fbx
{
	class Utility
	{
	public:
		static XMFLOAT4X4	Negative();
		
		static Vector2		ToVector2( FbxVector2& vec );
		
		static Vector3		ToVector3( FbxVector4& vec );
		static Vector3		ToVector3( FbxDouble3& vec );

		static Vector4		ToColor( FbxVector4& vec );
		static Vector4		ToColor( FbxPropertyT<FbxDouble3>& vec, FbxPropertyT<FbxDouble>& factor );
		
		static XMFLOAT4X4	ToMatrix( FbxAMatrix& matrix );

		static string		GetTextureFile( FbxProperty& prop );

		static string		GetMaterialName( FbxMesh* mesh, int polygonIndex, int cpIndex );
		static Vector2		GetUv( FbxMesh* mesh, int cpIndex, int uvIndex );
	};
}