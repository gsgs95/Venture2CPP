#pragma once
#include <vector>

using namespace std;

class AActor;

class FWorld
{
public:
	FWorld();
	~FWorld();

	vector<AActor*> ActorList;
	void SpawnActor(AActor* NewActor);
	void DestroyActor(AActor* DeleteActor);

	void Tick();
	void Render();
	void BeginPlay();
	void EndPlay();
};


