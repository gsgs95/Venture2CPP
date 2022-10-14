#include <conio.h>
#include <fstream>
#include <algorithm>
#include "Engine.h"
#include "World.h"
#include "Floor.h"
#include "Goal.h"
#include "Player.h"
#include "Wall.h"

using namespace std;

int Engine::KeyCode = 0;

Engine::Engine()
	: MyWorld{ new FWorld{} }, bIsRunning{ true }
{
}

Engine::~Engine()
{
	if(MyWorld)	delete MyWorld;
}

void Engine::Gotoxy(int X, int Y)
{
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


void Engine::Load(string MapFileName)
{
	ifstream MapFile(MapFileName);

	char Data[100];
	size_t Y = 0;
	while (MapFile.getline(Data, 100))
	{
		for (size_t X = 0; X < strlen(Data); ++X)
		{
			MyWorld->SpawnActor(new AFloor(X, Y));
			if (Data[X] == '*')
			{
				MyWorld->SpawnActor(new AWall(X, Y));
			}
			else if (Data[X] == 'P')
			{
				MyWorld->SpawnActor(new APlayer(X, Y));
			}
			else if (Data[X] == 'G')
			{
				MyWorld->SpawnActor(new AGoal(X, Y));
			}
		}
		++Y;
	}
	MapFile.close();
	
	// MyWorld의 ActorList를 ZOrder의 오름차순으로 Sort
	sort(MyWorld->ActorList.begin(), MyWorld->ActorList.end(), AActor::ActorCmp);
}

void Engine::Run()
{
	BeginPlay();
	while (bIsRunning)
	{
		Input();
		Tick(); // 물리, 위치 등 처리
		Render();
	}
	EndPlay();
}

void Engine::QuitGame()
{
	bIsRunning = false;
}


vector<AActor*>& Engine::GetAllActors()
{
	return MyWorld->ActorList;
}

void Engine::Input()
{
	KeyCode = _getch();
}

void Engine::Tick()
{
	MyWorld->Tick();
}

void Engine::Render()
{
	system("cls");
	MyWorld->Render();
}

void Engine::BeginPlay()
{
	MyWorld->BeginPlay();
}

void Engine::EndPlay()
{
	MyWorld->EndPlay();
}

FWorld& Engine::GetWorld() const
{
	return *MyWorld;
}

