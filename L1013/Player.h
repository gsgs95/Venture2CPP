#pragma once
#include "Actor.h"
#include "MyEngine.h"

class APlayer : public AActor
{
public:
	APlayer(int X = 1, int Y = 1);
	~APlayer();

	virtual void Tick() override;
	bool PredictCanMove();
	bool Promising(MyEngine& E);
	const FWorld& GetWorld(MyEngine& E) const;
};

