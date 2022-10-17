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

