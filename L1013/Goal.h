#pragma once
#include "Actor.h"
#include "MyEngine.h"

class AGoal : public AActor
{
public:
	AGoal(int X = 1, int Y = 1);
	~AGoal();

	virtual void Tick() override;
private:
	bool bIsVisited = false;
	Uint64 ElapsedTime;
	Uint64 ExcuteTime;
};

