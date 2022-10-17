#include "Monster.h"

AMonster::AMonster(int X, int Y)
	: AActor(X, Y, 'M', 40, ECollisionType::CollisionEnable, { 0,0,0xff,0 })
{
	LoadBMP("data/slime.bmp");
	ElapsedTime = 0;
}

AMonster::~AMonster()
{
}

void AMonster::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	Uint64 RandomPatrolTime = rand() % 1000 + 1000; // 랜덤하게 1~2초 사이의 시간이 흐르면 움직임
	if (ElapsedTime >= RandomPatrolTime)
	{
		ElapsedTime -= RandomPatrolTime;
		RandomPatrol();
	}
	AActor::Tick();
}

void AMonster::Render()
{
	AActor::Render();
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::EndPlay()
{
	AActor::EndPlay();
}

void AMonster::RandomPatrol()
{
	switch (rand() % 4)
	{
	case 0:
		--Y;
		Y = PredictCanMove() ? Y : ++Y;
		break;
	case 1:
		++X;
		X = PredictCanMove() ? X : --X;
		break;
	case 2:
		++Y;
		Y = PredictCanMove() ? Y : --Y;
		break;
	case 3:
		--X;
		X = PredictCanMove() ? X : ++X;
		break;
	}
}

bool AMonster::PredictCanMove()
{
	for (AActor* Actor : GEngine->GetAllActors()) // 월드의 모든 액터에 대해
	{
		if (X == Actor->X && Y == Actor->Y &&// 자신과 겹치는 위치이고,
			dynamic_cast<AMonster*>(Actor) != this) // 자신이 아닌 액터 찾기
		{
			if (CheckHit(Actor)) // 충돌가능한지 검증
			{
				return false;
			}
		}
	}
	return true;
}
