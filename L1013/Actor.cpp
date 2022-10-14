#include "Actor.h"
#include <iostream>
#include <Windows.h>

using namespace std;

AActor::AActor(int X, int Y, char Shape, int ZOrder, ECollisionType CollisionType)
	:X{ X }, Y{ Y }, Shape{ Shape }, ZOrder{ ZOrder }, CollisionType{ CollisionType }  // 초기화 리스트
{
}

AActor::~AActor()
{
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
