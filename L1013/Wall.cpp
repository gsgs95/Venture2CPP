#include "Wall.h"
#include <iostream>

using namespace std;

AWall::AWall(int X, int Y)
	:AActor(X, Y, '*', 30, ECollisionType::CollisionEnable)
{
}

AWall::~AWall()
{
	cout << "~AWall()" << endl;
}

