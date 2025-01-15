#include "PreCompile.h"

#include "TestLevelMode.h"
#include "TestActor.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/TileMapRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include <EnginePlatform/EngineInput.h>

TestLevelMode::TestLevelMode()
{
	Object = GetWorld()->SpawnActor<TestActor>();

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);


}

TestLevelMode::~TestLevelMode()
{
}

void TestLevelMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	if (UEngineInput::IsDown('P'))
	{
		GetWorld()->GetMainCamera()->FreeCameraSwitch();
	}

	Object->AddActorRotation({ 0.0f, 0.0f ,500.0f * _DeltaTime });
}
