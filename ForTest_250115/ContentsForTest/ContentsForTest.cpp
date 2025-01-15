#include "PreCompile.h"
#include "ContentsForTest.h"

#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>

CreateContentsCoreDefine(ContentsForTest);

ContentsForTest::ContentsForTest()
{
}

ContentsForTest::~ContentsForTest()
{
}


void ContentsForTest::EngineStart(UEngineInitData& _Data)
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyMaterial");
		Mat->SetVertexShader("ShaderForTest.fx");
		Mat->SetPixelShader("ShaderForTest.fx");
	}
}

void ContentsForTest::EngineTick(float _DeltaTime)
{

}

void ContentsForTest::EngineEnd()
{

}
