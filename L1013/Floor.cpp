#include "Floor.h"
#include <iostream>
using namespace std;

AFloor::AFloor(int X, int Y)
	:AActor(X, Y, ' ', 10, ECollisionType::NoCollision)
{
}

AFloor::~AFloor()
{
	cout << "~AFloor()" << endl;
}
