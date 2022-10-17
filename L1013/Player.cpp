#include "Player.h"
#include <iostream>
#include "MyEngine.h"

using namespace std;

int APlayer::Frames = 5;

APlayer::APlayer(int X, int Y, vector<int> FrameTable)
	:AActor(X, Y, 'P', 40, ECollisionType::CollisionEnable, { 0x00,0xff,0x00,0x00 })
	, Direction{ 3 }, ElapsedTime{ 0 }, Speed{ 1000 }, Frame{ 0 }
	, bIsReverse{ false }, FrameTable{ FrameTable }
{
	MyColorKey = { 0xff,0x00,0xff,0 };
	LoadBMP("data/player.bmp");
}

APlayer::~APlayer()
{
	cout << "~APlayer()" << endl;
}

void APlayer::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ElapsedTime >= (Speed/Frames))
	{
		ElapsedTime -= (Speed/Frames);
		// ������ �帧			0 1 2 3 4 3 2 1 0 1 2 3 4 3  ....
		// ���������̺� �帧	1 2 0 3 4 3 0 2 1 2 0 3 4 3 ....
		if (!bIsReverse) // �������ΰ��
		{
			if (Frame != Frames-1) Frame++;
			else // ������ �������� ���
			{
				Frame--;
				bIsReverse = true; // ���������� ������ȯ
			}
		}
		else // �������ΰ��
		{
			if (Frame != 0) Frame--;
			else // ù��° �������� ���
			{
				Frame++;
				bIsReverse = false; // ���������� ������ȯ
			}
		}
	}
	if (GEngine->MyEvent.type != SDL_KEYDOWN)
	{
		return;
	}

	switch (GEngine->MyEvent.key.keysym.sym)
	{
	case SDLK_w:
		--Y;
		Y = PredictCanMove() ? Y : ++Y;
		Direction = 2;
		break;
	case SDLK_d:
		++X;
		X = PredictCanMove() ? X : --X;
		Direction = 1;
		break;
	case SDLK_s:
		++Y;
		Y = PredictCanMove() ? Y : --Y;
		Direction = 3;
		break;
	case SDLK_a:
		--X;
		X = PredictCanMove() ? X : ++X;
		Direction = 0;
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

void APlayer::Render()
{
	// 2D
	SDL_Rect MyRect = SDL_Rect({ X * TileSize,Y * TileSize,TileSize, TileSize });
	if (MyTexture == nullptr)
	{
		SDL_SetRenderDrawColor(GEngine->MyRenderer, MyColor.r, MyColor.g, MyColor.b, MyColor.a);
		SDL_RenderFillRect(GEngine->MyRenderer, &MyRect);
		//SDL_RenderDrawPoint(GEngine->MyRenderer, X, Y);
	}
	else
	{
		SDL_Rect SourceRect = { MySurface->w / 5 * FrameTable[Frame] , MySurface->h / 5 * Direction,MySurface->w / 5, MySurface->h / 5 };
		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, &SourceRect, &MyRect);// �ؽ���(Source)�� �簢��(Dest)�� ����, nullptr�� ������ü�� �����ϰڴٴ� ��
	}
}