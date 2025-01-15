#include "PreCompile.h"
#include "TestLevel.h"
#include <EngineCore/CameraActor.h>
//#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCamera.h>
#include <EnginePlatform/EngineInput.h>

TestLevel::TestLevel()
{
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{
	AActor::BeginPlay();
}

void TestLevel::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('P'))
	{
		GetWorld()->GetMainCamera()->FreeCameraSwitch();
	}
}