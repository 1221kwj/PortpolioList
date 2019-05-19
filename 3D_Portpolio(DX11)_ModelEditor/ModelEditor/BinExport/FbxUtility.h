#pragma once

class FbxUtility
{
public:
	static D3DXVECTOR2 ToVector2(const class FbxVector2& vec);
	static D3DXVECTOR3 ToVector3(const class FbxVector4& vec);
	static D3DXVECTOR4 ToVector4(const class FbxVector4& vec);
	static D3DXVECTOR2 ToUV(const class FbxVector2& vec);
	static D3DXCOLOR ToColor4F(const class FbxVector4& vec);
	static D3DXMATRIX ToMatrix(const class FbxMatrix&  mat);

	static int   GetMappingIndex(enum FbxLayerElement::EMappingMode mode, int polygonIndex, int polygonVertexIndex, int vertexIndex);
	static D3DXVECTOR3 GetPosition(const class FbxVector4& position);
	static D3DXVECTOR3 GetNormal(class FbxMesh* mesh, int polygonIndex, int vertexIndex);
	static D3DXVECTOR2 GetUV(class FbxMesh* mesh, int layerIndex, int polygonIndex, int polygonVertexIndex, int vertexIndex);
	static D3DXMATRIX GetGeometricOffset(class FbxNode* node);
	static D3DXCOLOR GetMaterialProperty(class FbxSurfaceMaterial* material, const char* name, const char* factorName, string* textureName);

	static D3DXMATRIX GetAbsoluteTransformFromCurrentTake(class FbxNode* node, class FbxTime time);
	static D3DXMATRIX GetLocalTransformFromCurrentTake(class FbxNode* node, class FbxTime time);
};