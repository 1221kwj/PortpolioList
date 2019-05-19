#include "stdafx.h"
#include "ModelKeyFrame.h"
#include "../../BinExport/FbxData.h"

ModelQuaternionKeyFrame::ModelQuaternionKeyFrame(const D3DXMATRIX & transform)
{
	D3DXQuaternionRotationMatrix(&q, &transform);
	translation = D3DXVECTOR3(transform._41, transform._42, transform._43);
}

ModelKeyFrame::ModelKeyFrame(const KeyFrameData & data)
{
	name = data.name;
	for (UINT i = 0; i < data.transforms.size(); i++)
	{
		D3DXMATRIX transform = data.transforms[i];
		quaternionKeyFrames.push_back(make_pair(transform, ModelQuaternionKeyFrame(transform)));
	}
}

ModelKeyFrame::~ModelKeyFrame()
{

}

const D3DXMATRIX & ModelKeyFrame::GetKeyFrameTransform(const int & keyFrame) const
{
	return quaternionKeyFrames[keyFrame].first;
}

const ModelQuaternionKeyFrame & ModelKeyFrame::GetQuaternionKeyFrame(const int & keyFrame) const
{
	return quaternionKeyFrames[keyFrame].second;
}
