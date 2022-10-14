#pragma once
#include "Engine.h"

class MyEngine : public Engine
{
private:
	MyEngine();
public:
	virtual ~MyEngine();

	// UEngine을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Terminalize() override;

	static inline MyEngine* GetEngine()
	{
		if (Instance == nullptr)
		{
			new MyEngine();
		}
		return Instance;
	}

protected:
	static MyEngine* Instance;
};

#define GEngine MyEngine::GetEngine()

