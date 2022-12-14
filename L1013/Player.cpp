#include "Player.h"
#include <iostream>
#include "MyEngine.h"
#include "SoundActor.h"

using namespace std;

int APlayer::Frames = 5;

APlayer::APlayer(int X, int Y, vector<int> FrameTable)
	:AActor(X, Y, 'P', 40, ECollisionType::CollisionEnable, { 0x00,0xff,0x00,0x00 })
	, Direction{ 3 }, ElapsedTime{ 0 }, Speed{ 2 }, Frame{ 0 }
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
	if (ElapsedTime >= (1000/(Speed*Frames)))
	{
		ElapsedTime -= (1000 / (Speed * Frames));
		// 프레임 흐름			0 1 2 3 4 3 2 1 0 1 2 3 4 3  ....
		// 프레임테이블 흐름	1 2 0 3 4 3 0 2 1 2 0 3 4 3 ....
		if (!bIsReverse) // 정방향인경우
		{
			if (Frame != Frames-1) Frame++; // 정방향 흐름
			else // 마지막 프레임인 경우
			{
				Frame--;
				bIsReverse = true; // 역방향으로 방향전환
			}
		}
		else // 역방향인경우
		{
			if (Frame != 0) Frame--; // 역방향 흐름
			else // 첫번째 프레임인 경우
			{
				Frame++;
				bIsReverse = false; // 정방향으로 방향전환
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
		GEngine->SpawnActor(new ASoundActor("./data/move.wav", false));
		break;
	case SDLK_d:
		++X;
		X = PredictCanMove() ? X : --X;
		Direction = 1;
		GEngine->SpawnActor(new ASoundActor("./data/move.wav", false));
		break;
	case SDLK_s:
		++Y;
		Y = PredictCanMove() ? Y : --Y;
		Direction = 3;
		GEngine->SpawnActor(new ASoundActor("./data/move.wav", false));
		break;
	case SDLK_a:
		--X;
		X = PredictCanMove() ? X : ++X;
		Direction = 0;
		GEngine->SpawnActor(new ASoundActor("./data/move.wav", false));
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
		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, &SourceRect, &MyRect);// 텍스쳐(Source)를 사각형(Dest)에 맵핑, nullptr은 원본전체다 맵핑하겠다는 뜻
	}
}