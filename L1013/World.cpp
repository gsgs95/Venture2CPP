#include <iostream>
#include "World.h"
#include "Actor.h"

using namespace std;

FWorld::FWorld()
{
}

FWorld::~FWorld()
{
	for (auto Value : ActorList)
	{
		if (Value)
		{
			delete Value;
		}
	}

	ActorList.clear();
}

void FWorld::SpawnActor(AActor* NewActor)
{
	if (NewActor)
	{
		ActorList.push_back(NewActor);
	}
}

void FWorld::DestroyActor(AActor* DeleteActor)
{
	if(DeleteActor)
	{
		ActorList.erase(find(ActorList.begin(), ActorList.end(), DeleteActor));
		delete DeleteActor;
	}

	/*
	for (auto iter = ActorList.begin(); iter != ActorList.end(); ++iter)
	{
		if (*iter == DeleteActor)
		{
			ActorList.erase(iter);
			break;
		}
	}
	*/
}

void FWorld::Terminate()
{
	for (auto Value : ActorList)
	{
		if (Value)
		{
			delete Value;
		}
	}

	ActorList.clear();
}

void FWorld::Tick()
{
	for (int i=0; i<ActorList.size(); i++)
	{
		ActorList[i]->Tick();
	}
}

void FWorld::Render()
{
	for (int i = 0; i < ActorList.size(); i++)
	{
		ActorList[i]->Render();
	}
}

void FWorld::BeginPlay()
{
	// World BeginPlay

	// ActorList BeginPlay
	for (int i = 0; i < ActorList.size(); i++)
	{
		ActorList[i]->BeginPlay();
	}
}

void FWorld::EndPlay()
{
	// ActorList EndPlay
	for (int i = 0; i < ActorList.size(); i++)
	{
		ActorList[i]->EndPlay();
	}

	// World EndPlay

}
