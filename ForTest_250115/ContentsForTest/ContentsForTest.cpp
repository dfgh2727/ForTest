#include "PreCompile.h"
#include "ContentsForTest.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>

#include "TestLevel.h"

CreateContentsCoreDefine(ContentsForTest);

ContentsForTest::ContentsForTest()
{
}

ContentsForTest::~ContentsForTest()
{
}


void ContentsForTest::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 540, 200 };
	_Data.WindowSize = { 760, 570 };

	UEngineCore::CreateLevel<TestLevel, APawn>("Test");
	UEngineCore::OpenLevel("Test");

	/*{
		UEngineDirectory CurDir;
		CurDir.MoveParentToDirectory("ContentsShader");

		std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

		for (size_t i = 0; i < ShaderFiles.size(); i++)
		{
			UEngineShader::ReflectionCompile(ShaderFiles[i]);
		}
	}*/
	//{
	//	std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyMaterial");
	//	Mat->SetVertexShader("ShaderForTest.fx");
	//	Mat->SetPixelShader("ShaderForTest.fx");
	//}
}

void ContentsForTest::EngineTick(float _DeltaTime)
{

}

void ContentsForTest::EngineEnd()
{

}
