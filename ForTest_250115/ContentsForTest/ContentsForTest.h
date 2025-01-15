#pragma once
#include <EngineCore/IContentsCore.h>

// ��Ģ�� ����� ���ۿ� ����.

// ���� :
class ContentsForTest : public IContentsCore
{
public:
	// constrcuter destructer
	ContentsForTest();
	~ContentsForTest();

	// delete Function
	ContentsForTest(const ContentsForTest& _Other) = delete;
	ContentsForTest(ContentsForTest&& _Other) noexcept = delete;
	ContentsForTest& operator=(const ContentsForTest& _Other) = delete;
	ContentsForTest& operator=(ContentsForTest&& _Other) noexcept = delete;

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();

private:

};

