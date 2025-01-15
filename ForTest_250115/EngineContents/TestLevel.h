#pragma once
#include <EngineCore/GameMode.h>

// 설명 :
class TestLevel : public AGameMode
{
public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);


protected:
	void LevelChangeStart() override;

private:
	// 이렇게 들고 있으면 나는 죽였다고 생각하는데. 살아있을수 있다.
	// ATitleLogo* Logo; => 뎅글링 포인터 부활.
	std::shared_ptr<class TestActor> TActor;
};

