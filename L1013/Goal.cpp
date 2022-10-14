#include "Goal.h"
#include <iostream>
#include "Player.h"

using namespace std;

AGoal::AGoal(int X, int Y)
	:AActor(X, Y, 'G', 20, ECollisionType::QueryOnly)
{
}

AGoal::~AGoal()
{
	cout << "~AGoal()" << endl;
}

void AGoal::Tick()
{
	for (AActor* Actor : GEngine->GetAllActors())
	{
		if (X == Actor->X && Y == Actor->Y
			&& dynamic_cast<APlayer*>(Actor) != nullptr)
		{
			cout << "Complete" << endl;
			GEngine->QuitGame();
		}
	}
}

