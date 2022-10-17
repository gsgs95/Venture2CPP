#include "Actor.h"
#include <iostream>
#include <Windows.h>
#include "MyEngine.h"

using namespace std;

AActor::AActor(int X, int Y, char Shape, int ZOrder, ECollisionType CollisionType,
	SDL_Color Color, int TileSize)
	:X{ X }, Y{ Y }, Shape{ Shape }, ZOrder{ ZOrder }, CollisionType{ CollisionType }
	, MyColor{ Color }, TileSize{ TileSize }, MySurface{ nullptr }, MyTexture{ nullptr }  // 초기화 리스트
{
}

AActor::~AActor()
{
	SDL_FreeSurface(MySurface);
	SDL_DestroyTexture(MyTexture);
	cout << "~AAcotor()" << endl;
}

void AActor::Tick()
{
}

void AActor::Render()
{
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	cout << Shape;

	// 2D
	SDL_SetRenderDrawColor(GEngine->MyRenderer, MyColor.r, MyColor.g, MyColor.b, MyColor.a);
	//SDL_RenderDrawPoint(GEngine->MyRenderer, X, Y);

	SDL_Rect MyRect = SDL_Rect({ X * TileSize,Y * TileSize,TileSize, TileSize });
	if (MyTexture == nullptr)
	{
		SDL_RenderFillRect(GEngine->MyRenderer, &MyRect);
	}
	else
	{
		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &MyRect);// 텍스쳐(Source)를 사각형(Dest)에 맵핑, nullptr은 원본전체다 맵핑하겠다는 뜻
	}
}

void AActor::BeginPlay()
{
}

void AActor::EndPlay()
{
}

bool AActor::CheckHit(AActor* Other)
{
	if (((int)Other->CollisionType & (int)ECollisionType::PhysicsOnly) 
		&& ((int)this->CollisionType & (int)ECollisionType::PhysicsOnly))
	{
		return true;
	}
	return false;
}

void AActor::LoadBMP(string Filename)
{
	MySurface = SDL_LoadBMP(Filename.c_str());

	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);
}
