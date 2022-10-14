#pragma once

#ifndef __AACTOR_H__
#define __AACTOR_H__

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
	AActor(int X = 1, int Y = 1, char Shape = ' ', int ZOrder = 0, ECollisionType CollisionType = ECollisionType::NoCollision);
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

	bool bIsCollide;
	bool bIsOverlap;

	int X;
	int Y;
	char Shape;
	int ZOrder;
};

#endif