#pragma once

class ModelQuaternionKeyFrame
{
	friend class ModelKeyFrame;

public:
	virtual ~ModelQuaternionKeyFrame() {}

	const D3DXQUATERNION& GetQuaternion	() const { return q; }
	const D3DXVECTOR3& GetTranslation() const { return translation; }

private:
	ModelQuaternionKeyFrame(const D3DXMATRIX& transform);

private:
	D3DXQUATERNION q;
	D3DXVECTOR3	translation;
};

class ModelKeyFrame
{
	friend class ModelData;
	friend struct KeyFrameData;

	typedef vector<pair<D3DXMATRIX, class ModelQuaternionKeyFrame>> QuaternionArray;

public:
	virtual ~ModelKeyFrame();

	const string& GetAnimationName() const { return name; }
	const D3DXMATRIX& GetKeyFrameTransform(const int& keyFrame) const;
	const ModelQuaternionKeyFrame& GetQuaternionKeyFrame(const int& keyFrame) const;

private:
	ModelKeyFrame(const KeyFrameData& data);

private:
	string name;
	QuaternionArray quaternionKeyFrames;
};