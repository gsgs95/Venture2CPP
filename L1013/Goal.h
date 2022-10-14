#pragma once
#include "Actor.h"
#include "MyEngine.h"

class AGoal : public AActor
{
public:
	AGoal(int X = 1, int Y = 1);
	~AGoal();

	virtual void Tick() override;
};

