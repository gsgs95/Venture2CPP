#pragma once
#include <vector>
#include "Actor.h"
#include "MyEngine.h"

class APlayer : public AActor
{
public:
	APlayer(int X = 1, int Y = 1
		, vector<int> FrameTable = { 1,2,0,3,4 });

	~APlayer();

	virtual void Tick() override;
	bool PredictCanMove();
	bool Promising(MyEngine& E);
	const FWorld& GetWorld(MyEngine& E) const;
	void Render();
	static int Frames;
private:
	int Direction; // a:0, d:1, w:2, s:3
	Uint64 ElapsedTime;
	Uint64 Speed;
	int Frame;
	bool bIsReverse;
	vector<int> FrameTable = { 1,2,0,3,4 };
};

