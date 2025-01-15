#include "PreCompile.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include "MyCustomRenderer.h"
#include "TestActor.h"

TestActor::TestActor()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<MyCustomRenderer>();
	Renderer->SetScale3D({ 200.0f, 200.0f, 200.0f });
	Renderer->SetupAttachment(RootComponent);

}

TestActor::~TestActor()
{
}

void TestActor::BeginPlay()
{
	AActor::BeginPlay();
}

void TestActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}