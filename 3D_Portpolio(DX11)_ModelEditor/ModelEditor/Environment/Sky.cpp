#include "stdafx.h"
#include "Sky.h"
#include "../BinExport/FbxLoader.h"
#include "../Model/ModelPart.h"
#include "../Model/Elements/ModelMesh.h"
#include "../Model/Elements/ModelMaterial.h"

Sky::Sky()
	: modelFile(BinModels + L"Meshes/Sphere.model")
	, shaderFile(Shaders + L"Sky.hlsl")
	, shader(NULL)
{
	D3DXMatrixIdentity(&world);

	skyBuffer = new SkyBuffer();

	FbxLoader::LoadBinary(modelFile, &model);
	model->GetModelPart(0)->GetMaterial()->SetShader(shaderFile);
	
	
	D3D11_RASTERIZER_DESC rasterizerDesc;
	States::GetRasterizerDesc(&rasterizerDesc);
	rasterizerDesc.FrontCounterClockwise = false;
	States::CreateRasterizer(&rasterizerDesc, &clockState);

	States::GetRasterizerDesc(&rasterizerDesc);
	rasterizerDesc.FrontCounterClockwise = true;
	States::CreateRasterizer(&rasterizerDesc, &countClockState);

	D3D11_DEPTH_STENCIL_DESC depthDesc;
	States::GetDepthStencilDesc(&depthDesc);
	depthDesc.DepthEnable = true;
	States::CreateDepthStencil(&depthDesc, &depthOnState);

	States::GetDepthStencilDesc(&depthDesc);
	depthDesc.DepthEnable = false;
	States::CreateDepthStencil(&depthDesc, &depthOffState);
}

Sky::~Sky()
{
	SAFE_DELETE(model);

	SAFE_RELEASE(depthOnState);
	SAFE_RELEASE(depthOffState);
	SAFE_RELEASE(clockState);
	SAFE_RELEASE(countClockState);

	SAFE_DELETE(skyBuffer);
	SAFE_DELETE(shader);
}

void Sky::Update(Camera* camera)
{
	D3DXVECTOR3 position;
	camera->GetPosition(&position);

	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
	
	model->GetModelPart(0)->GetMesh()->SetGeometricOffset(world);
	model->GetModelPart(0)->Update();
}

void Sky::Render()
{
	States::SetDepthStencil(depthOffState);
	States::SetRasterizer(countClockState);
	{
		skyBuffer->SetPSBuffer(2);

		model->GetModelPart(0)->Render();
	}
	States::SetRasterizer(clockState);;
	States::SetDepthStencil(depthOnState);
}

void Sky::PostRender(GuiSettings* settings)
{
	if (settings->bShowEnvironmentWindow == true)
	{
		ImGui::Begin("Environment", &settings->bShowEnvironmentWindow);
		ImGui::Dummy(ImVec2(0, 10));
		ImGui::Text("Sky");
		ImGui::Separator();
		{
			ImGui::SliderFloat("Height", &skyBuffer->Data.Height, 0.0f, 4.0f);
			ImGui::ColorEdit3("Center", (float *)&skyBuffer->Data.Center);
			ImGui::ColorEdit3("Apex", (float *)&skyBuffer->Data.Apex);
		}
		ImGui::Columns(1);

		ImGui::End();
	}
}
