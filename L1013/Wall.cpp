#include "Wall.h"
#include <iostream>

using namespace std;

AWall::AWall(int X, int Y)
	:AActor(X, Y, '*', 30, ECollisionType::CollisionEnable, { 100,100,100,0 })
{
	LoadBMP("data/wall.bmp");
}

AWall::~AWall()
{
	cout << "~AWall()" << endl;
}

