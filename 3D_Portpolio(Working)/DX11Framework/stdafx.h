#pragma once
// ======================================================================
//								System Header
// ======================================================================
#include <Windows.h>
#include <assert.h>
#include <string>
#include <io.h>

// ======================================================================
//								STL Header
// ======================================================================
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <functional>
#include <iterator>

// ======================================================================
//								DirectX Header
// ======================================================================
#include <d2d1_1.h>
#include <dwrite.h>
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dx11tex.h>
#include <d3dx11effect.h>
#include <DirectXPackedVector.h>

// ======================================================================
//							DirectX Library
// ======================================================================
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Effects11d.lib")

// ======================================================================
//								ImGui
// ======================================================================
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "ImGui.lib")

// ======================================================================
//								Fbx SDK
// ======================================================================
#define FBXSDK_SHARED
#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk.lib")

// ======================================================================
//								Json Cpp
// ======================================================================
#include <json/json.h>
#pragma comment(lib, "json_vc71_libmtd.lib")
#pragma warning(disable : 4996)

// ======================================================================
//							DirectX Tex
// ======================================================================
#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

// ======================================================================
//						BulletPhysics
// ======================================================================
#include <BulletPhysics/btBulletDynamicsCommon.h>
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "LinearMath.lib")

#define SAFE_RELEASE(p)		{ if(p) { (p)->Release()	; (p) = nullptr; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p)		; (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete [] (p)		; (p) = nullptr; } }

using namespace std;
using namespace DirectX;
using namespace fbxsdk;

const wstring Shaders			= L"../001_Shaders/";
const wstring Assets			= L"../002_Assets/";
const wstring Textures			= L"../002_Assets/000_Textures/";

const wstring FbxFilePath		= L"../002_Assets/001_FbxFile/";
const wstring FbxFigurePath		= L"../002_Assets/001_FbxFile/000_Figure/";
const wstring FbxCharPath		= L"../002_Assets/001_FbxFile/001_Character/";

const wstring BinaryFile		= L"../002_Assets/002_BinaryFile/";
const wstring BinaryFigure		= L"../002_Assets/002_BinaryFile/000_Figure/";
const wstring BinaryCharacter	= L"../002_Assets/002_BinaryFile/001_Character/";

#include "./000_Systems/D3D.h"
#include "./000_Systems/CoreClass.h"
#include "./000_Systems/DirectXWrite.h"
#include "./000_Systems/Keyboard.h"
#include "./000_Systems/Mouse.h"
#include "./000_Systems/Time.h"

#include "./001_Utilities/Math.h"
#include "./001_Utilities/String.h"
#include "./001_Utilities/Path.h"
#include "./001_Utilities/Xml.h"
#include "./001_Utilities/BinaryFile.h"

#include "./002_Renders/VertexLayouts.h"
#include "./002_Renders/CBuffer.h"
#include "./002_Renders/Shader.h"
#include "./002_Renders/Texture.h"
#include "./002_Renders/Context.h"
#include "./002_Renders/Material.h"
#include "./002_Renders/CsResource.h"
#include "./002_Renders/Render2D.h"

#include "./003_Viewer/Viewport.h"
#include "./003_Viewer/Perspective.h"
#include "./003_Viewer/RenderTargetView.h"
#include "./003_Viewer/DepthStencilView.h"

#include "./004_Execute/Execute.h"

#include "./007_Draw/000_Figures/MeshSphere.h"