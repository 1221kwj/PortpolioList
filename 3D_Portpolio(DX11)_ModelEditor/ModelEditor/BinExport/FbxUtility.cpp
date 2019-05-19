#include "stdafx.h"
#include "FbxUtility.h"

D3DXVECTOR2 FbxUtility::ToVector2(const FbxVector2 & vec)
{
	return D3DXVECTOR2((float)vec.mData[0], (float)vec.mData[1]);
}

D3DXVECTOR3 FbxUtility::ToVector3(const FbxVector4 & vec)
{
	return D3DXVECTOR3((float)vec.mData[0], (float)vec.mData[1], (float)vec.mData[2]);
}

D3DXVECTOR4 FbxUtility::ToVector4(const FbxVector4 & vec)
{
	return D3DXVECTOR4
	(
		(float)vec.mData[0], (float)vec.mData[1], (float)vec.mData[2], (float)vec.mData[3]
	);
}

D3DXVECTOR2 FbxUtility::ToUV(const FbxVector2 & vec)
{
	D3DXVECTOR2 temp = ToVector2(vec);

	return D3DXVECTOR2(temp.x, 1.0f - temp.y);
}

D3DXCOLOR FbxUtility::ToColor4F(const FbxVector4 & vec)
{
	return D3DXCOLOR
	(
		(float)vec.mData[0], (float)vec.mData[1], (float)vec.mData[2], (float)vec.mData[3]
	);
}

D3DXMATRIX FbxUtility::ToMatrix(const FbxMatrix & mat)
{
	FbxVector4 r1 = mat.GetRow(0);
	FbxVector4 r2 = mat.GetRow(1);
	FbxVector4 r3 = mat.GetRow(2);
	FbxVector4 r4 = mat.GetRow(3);

	return D3DXMATRIX
	(
		(float)r1.mData[0], (float)r1.mData[1], (float)r1.mData[2], (float)r1.mData[3],
		(float)r2.mData[0], (float)r2.mData[1], (float)r2.mData[2], (float)r2.mData[3],
		(float)r3.mData[0], (float)r3.mData[1], (float)r3.mData[2], (float)r3.mData[3],
		(float)r4.mData[0], (float)r4.mData[1], (float)r4.mData[2], (float)r4.mData[3]
	);
}

int FbxUtility::GetMappingIndex(FbxLayerElement::EMappingMode mode, int polygonIndex, int polygonVertexIndex, int vertexIndex)
{
	switch (mode)
	{
	case FbxLayerElement::eAllSame:
		return 0;
	case FbxLayerElement::eByControlPoint:
		return vertexIndex;
	case FbxLayerElement::eByPolygonVertex:
		return polygonIndex * 3 + polygonVertexIndex;
	case FbxLayerElement::eByPolygon:
		return polygonIndex;
	default:
		return -1;
	}
}

D3DXVECTOR3 FbxUtility::GetPosition(const FbxVector4 & position)
{
	return ToVector3(position);
}

D3DXVECTOR3 FbxUtility::GetNormal(FbxMesh * mesh, int polygonIndex, int vertexIndex)
{
	FbxVector4 fbxNormal(0, 0, 0, 0);
	mesh->GetPolygonVertexNormal(polygonIndex, vertexIndex, fbxNormal);
	fbxNormal.Normalize();

	return ToVector3(fbxNormal);
}

D3DXVECTOR2 FbxUtility::GetUV(FbxMesh * mesh, int layerIndex, int polygonIndex, int polygonVertexIndex, int vertexIndex)
{
	int layerCount = mesh->GetLayerCount();
	if (layerIndex >= layerCount) return D3DXVECTOR2();

	FbxLayer* layer = mesh->GetLayer(layerIndex);
	if (layer == NULL) return D3DXVECTOR2();

	FbxLayerElementUV* uv = layer->GetUVs(FbxLayerElement::eTextureDiffuse);
	if (uv == NULL) return D3DXVECTOR2();


	FbxLayerElement::EMappingMode mappingMode = uv->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = uv->GetReferenceMode();

	const FbxLayerElementArrayTemplate<FbxVector2>& uvArray = uv->GetDirectArray();
	const FbxLayerElementArrayTemplate<int>& uvIndexArray = uv->GetIndexArray();

	int mappingIndex = 0;
	if (mappingMode == FbxLayerElement::eByControlPoint)
	{
		mappingIndex = vertexIndex;

		if (refMode == FbxLayerElement::eDirect)
		{
			if (mappingIndex < uvArray.GetCount())
				return ToUV(uvArray.GetAt(mappingIndex));
		}
		else if (refMode == FbxLayerElement::eIndexToDirect)
		{
			if (mappingIndex < uvArray.GetCount())
			{
				int tempIndex = uvIndexArray.GetAt(mappingIndex);

				if (tempIndex < uvArray.GetCount())
					return ToUV(uvArray.GetAt(tempIndex));
			}
		}//if(refMode)
	}
	else if (mappingMode == FbxLayerElement::eByPolygonVertex)
	{
		mappingIndex = mesh->GetTextureUVIndex
		(
			polygonIndex
			, polygonVertexIndex
			, FbxLayerElement::eTextureDiffuse
		);

		switch (refMode)
		{
		case FbxLayerElement::eDirect:
		case FbxLayerElement::eIndexToDirect:
			if (mappingIndex < uvArray.GetCount())
				return ToUV(uvArray.GetAt(mappingIndex));
		}//switch(refMode)
	}//if(mappingMode)

	return D3DXVECTOR2();
}

D3DXMATRIX FbxUtility::GetGeometricOffset(FbxNode * node)
{
	if (node == NULL)
	{
		D3DXMATRIX matrix;
		D3DXMatrixIdentity(&matrix);

		return matrix;
	}

	FbxVector4 T = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = node->GetGeometricScaling(FbxNode::eSourcePivot);

	FbxMatrix offset;
	offset.SetIdentity();
	offset.SetTRS(T, R, S);

	return ToMatrix(offset);
}

D3DXCOLOR FbxUtility::GetMaterialProperty(FbxSurfaceMaterial * material, const char * name, const char * factorName, string * textureName)
{
	D3DXCOLOR color(0, 0, 0, 1);

	FbxProperty prop = material->FindProperty(name);
	FbxProperty factorProp = material->FindProperty(factorName);
	if (prop.IsValid() == true && factorProp.IsValid() == true)
	{
		FbxDouble3 temp = prop.Get<FbxDouble3>();
		double factor = factorProp.Get<FbxDouble>();

		color.r = (float)(temp[0] * factor);
		color.g = (float)(temp[1] * factor);
		color.b = (float)(temp[2] * factor);
	}

	if (prop.IsValid() == true)
	{
		UINT count = prop.GetSrcObjectCount<FbxFileTexture>();
		if (count > 0)
		{
			FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>();
			if (texture != NULL)
				*textureName = (const char *)texture->GetFileName();
		}
		else
		{
			*textureName = "";
		}
	}

	return color;
}

D3DXMATRIX FbxUtility::GetAbsoluteTransformFromCurrentTake(FbxNode * node, FbxTime time)
{
	if (node == NULL)
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);

		return mat;
	}

	FbxAMatrix matrix = node->EvaluateGlobalTransform(time);

	return FbxUtility::ToMatrix(matrix);
}

D3DXMATRIX FbxUtility::GetLocalTransformFromCurrentTake(FbxNode * node, FbxTime time)
{
	if (node == NULL)
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);

		return mat;
	}

	FbxAMatrix matrix = node->EvaluateLocalTransform(time);

	return FbxUtility::ToMatrix(matrix);
}
