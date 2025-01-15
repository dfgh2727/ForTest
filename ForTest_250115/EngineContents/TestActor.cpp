#include "PreCompile.h"
#include "TestActor.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "MyCustomRenderer.h"

TestActor::TestActor()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<MyCustomRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 50.0f, 50.0f });
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