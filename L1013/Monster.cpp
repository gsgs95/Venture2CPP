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
	Uint64 RandomPatrolTime = rand() % 1000 + 1000; // �����ϰ� 1~2�� ������ �ð��� �帣�� ������
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
	for (AActor* Actor : GEngine->GetAllActors()) // ������ ��� ���Ϳ� ����
	{
		if (X == Actor->X && Y == Actor->Y &&// �ڽŰ� ��ġ�� ��ġ�̰�,
			dynamic_cast<AMonster*>(Actor) != this) // �ڽ��� �ƴ� ���� ã��
		{
			if (CheckHit(Actor)) // �浹�������� ����
			{
				return false;
			}
		}
	}
	return true;
}
