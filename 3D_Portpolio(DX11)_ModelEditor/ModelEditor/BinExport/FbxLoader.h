#pragma once

class FbxLoader
{
public:
	static void Convert( wstring fbxFile, const wstring saveFile );
	static void LoadBinaryOnlyMesh( wstring binFile, class Model** model );
	static void LoadBinary( wstring binFile, class Model** model );
	static void WriteBinary( wstring binFile, class Model* model );

	// =============================================================================== //
	static ModelData* LoadFbxAnimation( wstring fbxFile, wstring animName );
	
	// =============================================================================== //

private:
	FbxLoader();
	virtual ~FbxLoader();

	class ModelData* Load( const string& file );

	void ProcessMaterial();
	void ProcessNode( class FbxNode* node, enum FbxNodeAttribute::EType type );
	void ProcessMesh( class FbxNode* node );

	void ProcessAnimations();
	void ProcessAnimation( class FbxNode* node, const string& animationName, float frameRate, float start, float stop );
	void ProcessSkeleton( class FbxNode* node );

	void ProcessBoneWeights( class FbxMesh* mesh );
	void ProcessBoneWeights( class FbxSkin* skin );

private:
	class ModelData* modelData;

	class FbxManager* manager;
	class FbxScene* scene;
	class FbxImporter* importer;
	class FbxGeometryConverter* converter;

	vector<class FbxSurfaceMaterial*> materials;
};