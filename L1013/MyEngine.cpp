#include "MyEngine.h"

MyEngine* MyEngine::Instance = nullptr;

MyEngine::MyEngine()
{
	Instance = this;
}

MyEngine::~MyEngine()
{
	Instance = nullptr;
}

void MyEngine::Initialize()
{

	LoadLevel("Level1.txt");
}

void MyEngine::Terminalize()
{
	Gotoxy(0, 20);
}
