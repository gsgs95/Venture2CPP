#include "Player.h"
#include <iostream>
#include "MyEngine.h"

using namespace std;

APlayer::APlayer(int X, int Y)
	:AActor(X, Y, 'P', 40, ECollisionType::CollisionEnable)
{
}

APlayer::~APlayer()
{
	cout << "~APlayer()" << endl;
}

void APlayer::Tick()
{

	switch (MyEngine::GetKeyCode())
	{
	case 'w':
	case 'W':
		Y--;
		if (!PredictCanMove())
		{
			Y++;
		}
		break;
	case 'd':
	case 'D':
		X++;
		if (!PredictCanMove())
		{
			X--;
		}
		break;
	case 's':
	case 'S':
		Y++;
		if (!PredictCanMove())
		{
			Y--;
		}
		break;
	case'a':
	case 'A':
		X--;
		if (!PredictCanMove())
		{
			X++;
		}
		break;
	case 'q':
	case 'Q':
		GEngine->QuitGame();
		break;
	}
}

bool APlayer::PredictCanMove()
{
	for (AActor* Actor : GEngine->GetAllActors()) // ������ ��� ���Ϳ� ����
	{
		if (X == Actor->X && Y == Actor->Y &&// �÷��̾�� ��ġ�� ��ġ�̰�,
			dynamic_cast<APlayer*>(Actor) == nullptr) // �÷��̾ �ƴ� ���� ã��
		{
			if (CheckHit(Actor)) // �浹�������� ����
			{
				return false;
			}
		}
	}
	return true;
}

bool APlayer::Promising(MyEngine& E)
{
	// �ʿ��� �ش� X,Y ��ġ�� Wall�� �����ϴ��� Ȯ��
	// �����ϸ� false
	// �������� ������ true
	const FWorld* MyWorld = &GetWorld(E);
	return false;
}


const FWorld& APlayer::GetWorld(MyEngine& E) const
{
	// ���� �����ϴ� ���带 �����;���.
	// ����� ���� ������� �����ӿ� ����.
	// ��Ÿ�� �߿� �̱��� ������ �����ؾ���
	return E.GetWorld();
	// TODO: ���⿡ return ���� �����մϴ�.
}

