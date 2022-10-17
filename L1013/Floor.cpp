#include "Floor.h"
#include <iostream>
using namespace std;

AFloor::AFloor(int X, int Y)
	:AActor(X, Y, ' ', 10, ECollisionType::NoCollision, { 150,0,0,0 })
{
	LoadBMP("data/floor.bmp");
}

AFloor::~AFloor()
{
	cout << "~AFloor()" << endl;
}
