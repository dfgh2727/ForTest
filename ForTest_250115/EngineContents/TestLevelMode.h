#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class TestLevelMode : public AGameMode
{
public:
	// constrcuter destructer
	TestLevelMode();
	~TestLevelMode();

	// delete Function
	TestLevelMode(const TestLevelMode& _Other) = delete;
	TestLevelMode(TestLevelMode&& _Other) noexcept = delete;
	TestLevelMode& operator=(const TestLevelMode& _Other) = delete;
	TestLevelMode& operator=(TestLevelMode&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime);

private:
	std::shared_ptr<class TestActor> Object;

};

