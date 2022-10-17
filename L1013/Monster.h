#pragma once
#include "Actor.h"
#include "MyEngine.h"

class AMonster : public AActor
{
public:
	AMonster(int X = 1, int Y = 1);
	virtual ~AMonster();

	virtual void Tick();
	virtual void Render();
	virtual void BeginPlay();
	virtual void EndPlay();

	void RandomPatrol();
	bool PredictCanMove();
private:
	Uint64 ElapsedTime;
};


