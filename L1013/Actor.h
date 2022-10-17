#pragma once

#ifndef __AACTOR_H__
#define __AACTOR_H__

#include "SDL.h"
#include <string>

using namespace std;

enum class ECollisionType
{
	NoCollision		=		0,							// 0000 0000
	QueryOnly		=		1,							// 0000 0001
	PhysicsOnly		=		2,							// 0000 0010
	CollisionEnable	=		(QueryOnly | PhysicsOnly),	// 0000 0011
};

class AActor
{
public:
	AActor(int X = 1, int Y = 1, char Shape = ' ', int ZOrder = 0, ECollisionType CollisionType = ECollisionType::NoCollision, SDL_Color Color = { 0xff,0xff,0xff,0x00 }, int TileSize = 60);
	virtual ~AActor();

	virtual void Tick();
	virtual void Render();
	virtual void BeginPlay();
	virtual void EndPlay();
	
	bool CheckHit(AActor* Other);

	static inline bool ActorCmp(AActor* a, AActor* b)
	{
			return a->ZOrder < b->ZOrder;
	}

	
	ECollisionType CollisionType = ECollisionType::NoCollision;

	bool bIsCollide=0;
	bool bIsOverlap=0;

	int X;
	int Y;
	char Shape;
	int ZOrder;

	SDL_Color MyColor;
	int TileSize;

	// SDL 기준 -> RAM에 이미지저장 후 GPU의 VRAM으로 복사하여 빠르게 사용
	SDL_Surface* MySurface; // RAM
	SDL_Texture* MyTexture; // VRAM
	void LoadBMP(string Filename);
};

#endif