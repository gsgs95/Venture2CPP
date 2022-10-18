#include "Goal.h"
#include <iostream>
#include "Player.h"
#include "Text.h"
#include "MyEngine.h"

using namespace std;

AGoal::AGoal(int X, int Y)
	:AActor(X, Y, 'G', 20, ECollisionType::QueryOnly, { 255,255,0,0 }), bIsVisited{ false }, ElapsedTime{ 0 }, ExcuteTime{ 3000 }
{
	LoadBMP("data/coin.bmp");
}

AGoal::~AGoal()
{
	cout << "~AGoal()" << endl;
}

void AGoal::Tick()
{
	if (bIsVisited)
	{
		ElapsedTime += GEngine->GetWorldDeltaSeconds();
		if (ExcuteTime <= ElapsedTime)
		{
			GEngine->LoadLevel("Level2.txt");
			//GEngine->QuitGame();
		}
	}
	else
	{
		for (AActor* Actor : GEngine->GetAllActors())
		{
			if (X == Actor->X && Y == Actor->Y
				&& dynamic_cast<APlayer*>(Actor) != nullptr)
			{
				GEngine->SpawnActor(new AText(200, 200, "스테이지 클리어!!!", 30));
				cout << "Complete" << endl;
				bIsVisited = true;
				break;
				//GEngine->QuitGame();
			}
		}
	}


	SDL_Log("ActorCount = %d", GEngine->GetAllActors().size());
}

