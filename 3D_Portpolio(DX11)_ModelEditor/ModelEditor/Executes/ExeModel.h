#pragma once
#include "Execute.h"

enum class RADIOBUTTONSTATE
{
	MATERIAL = 0,
	SKELETON,
	ANIMATION,
};

class ExeModel : public Execute
{
public:
	ExeModel( ExecuteValues* values );
	~ExeModel();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void ResizeScreen();

private:
	void OpenConvertDialog( wstring file = L"" );
	void Convert( wstring file );
	void ConvertToBinAnimation();
	void OpenMeshDialog( wstring file = L"" );
	void OpenAnimDialog( wstring file = L"" );
	void SaveModelDialog( wstring file = L"" );
	void OpenModelDialog( wstring file = L"" );
	
	void MenuBarImGui();
	void ModelEditorImGui();
	void ListBoxImGui();
	void ExploreFolder( bool bRefresh, string folderName, string extention, vector<string>& list );
	void ExploreFolder( bool bRefresh, wstring folderName, string extention, vector<string>& list );

private:
	vector<class Model*>	modelList;
	vector<class Gizmos*>	gizmosList;
	vector<string>			modelNameList;

	Model*			model;
	wstring			selectedFbxFile;
	ExecuteValues*	values;
	ModelData*		mData;

	bool materialsCheck;
	bool boneListCheck;
	bool animationCheck;

	int	modelProperty;
	int selectModelPartCount;

	string	ComboSelectModelName;
	int		ComboSelectModelCount;

	vector<string> shaderName;
	vector<string> textureName;
	vector<string> animName;
	int shaderIndex;
};