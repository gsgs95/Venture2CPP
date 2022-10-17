#include "Player.h"
#include <iostream>
#include "MyEngine.h"

using namespace std;

APlayer::APlayer(int X, int Y)
	:AActor(X, Y, 'P', 40, ECollisionType::CollisionEnable, { 0x00,0xff,0x00,0x00 })
{
	LoadBMP("data/player.bmp");
}

APlayer::~APlayer()
{
	cout << "~APlayer()" << endl;
}

void APlayer::Tick()
{
	if (GEngine->MyEvent.type != SDL_KEYDOWN)
	{
		return;
	}

	switch (GEngine->MyEvent.key.keysym.sym)
	{
	case SDLK_w:
		--Y;
		Y = PredictCanMove() ? Y : ++Y;
		break;
	case SDLK_d:
		++X;
		X = PredictCanMove() ? X : --X;
		break;
	case SDLK_s:
		++Y;
		Y = PredictCanMove() ? Y : --Y;

		break;
	case SDLK_a:
		--X;
		X = PredictCanMove() ? X : ++X;
		break;
	case SDLK_ESCAPE:
		GEngine->QuitGame();
		break;
	}
}

bool APlayer::PredictCanMove()
{
	for (AActor* Actor : GEngine->GetAllActors()) // 월드의 모든 액터에 대해
	{
		if (X == Actor->X && Y == Actor->Y &&// 플레이어와 겹치는 위치이고,
			dynamic_cast<APlayer*>(Actor) == nullptr) // 플레이어가 아닌 액터 찾기
		{
			if (CheckHit(Actor)) // 충돌가능한지 검증
			{
				return false;
			}
		}
	}
	return true;
}

bool APlayer::Promising(MyEngine& E)
{
	// 맵에서 해당 X,Y 위치에 Wall이 존재하는지 확인
	// 존재하면 false
	// 존재하지 않으면 true
	const FWorld* MyWorld = &GetWorld(E);
	return false;
}


const FWorld& APlayer::GetWorld(MyEngine& E) const
{
	// 현재 존재하는 월드를 가져와야함.
	// 월드는 현재 만들어진 엔진속에 있음.
	// 런타임 중에 싱글턴 엔진에 접근해야함
	return E.GetWorld();
	// TODO: 여기에 return 문을 삽입합니다.
}

