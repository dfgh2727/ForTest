#pragma once
#include <EngineCore/GameMode.h>

// ���� :
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
	// �̷��� ��� ������ ���� �׿��ٰ� �����ϴµ�. ��������� �ִ�.
	// ATitleLogo* Logo; => ���۸� ������ ��Ȱ.
	std::shared_ptr<class TestActor> TActor;
};

