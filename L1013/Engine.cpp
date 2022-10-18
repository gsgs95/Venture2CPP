//#include <conio.h> // _getch()
#include <fstream>
#include <algorithm>

#include "Engine.h"
#include "World.h"
#include "Floor.h"
#include "Goal.h"
#include "Player.h"
#include "Wall.h"
#include "Monster.h"
#include "Text.h"

using namespace std;

int Engine::KeyCode = 0;

Engine::Engine()
	: MyWorld{ new FWorld{} }, bIsRunning{ true }
{
	srand(static_cast<unsigned int>(time(NULL))); // ����� �����õ� �ʱ�ȭ
	SDLInit();
	TTF_Init();

}

Engine::~Engine()
{
	if(MyWorld)	delete MyWorld;
	SDLTerm();
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
	int Y = 0;
	while (MapFile.getline(Data, 100))
	{
		for (int X = 0; X < strlen(Data); ++X)
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
			else if (Data[X] == 'M')
			{
				MyWorld->SpawnActor(new AMonster(X, Y));
			}
		}
		++Y;
	}
	MapFile.close();

	MyWorld->SpawnActor(new AText(100, 100, "Hello World", 30));
	
	// MyWorld�� ActorList�� ZOrder�� ������������ Sort
	sort(MyWorld->ActorList.begin(), MyWorld->ActorList.end(), AActor::ActorCmp);
}

void Engine::Run()
{
	BeginPlay();
	while (bIsRunning)
	{
		DeltaSeconds = SDL_GetTicks64() - LastTick;
		Input();
		Tick(); // ����, ��ġ �� ó��
		LastTick = SDL_GetTicks64();
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
	//KeyCode = _getch();
	SDL_PollEvent(&MyEvent); //  �޽���ť���� �̺�Ʈ�� ������ MyEvent�� ���� (Polling : ������Ʈ �Ȱ� �ִ��� ��� Ȯ���ϴ� ���.)
}

void Engine::Tick()
{
	if (MyEvent.type == SDL_QUIT)
	{
		bIsRunning = false;
	}

	MyWorld->Tick();

	SDL_Log("%d", DeltaSeconds);
}

void Engine::Render()
{
	//system("cls");
	SDL_Color BackgroundColor = { 0, 0, 0, 0 };
	SDL_SetRenderDrawColor(MyRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a); // ������ ���� ���� (Ÿ�귣����, r, g, b, a)
	SDL_RenderClear(MyRenderer); // �ش� ���������� ȭ�� ����� ��Ŵ

	

	MyWorld->Render();
	// ȭ�鿡 �׸���
	SDL_RenderPresent(MyRenderer);
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

void Engine::SDLInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL �ʱ�ȭ. SDL_INITEVERYTHING: ������ �ʱ�ȭ �÷���
	{
		SDL_Log("SDL_Init_Error");
		exit(-1);
	}

	MyWindow = SDL_CreateWindow("MyGame", 100, 100, 600, 600, SDL_WINDOW_VULKAN); // �Ķ����: ������ ȭ�� �̸�, ��ǥ ������ x,y , ������ �ʺ� ���� w,h, ������ ���� �÷���(SDL_WINDOW_VULKAN); ���ϰ�: ������ ������
	//MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); // Ÿ�� �����쿡 ����� x��° ������ �����Ͽ� ����, �Ӽ��÷��� ����(���� �ϵ���� ���� & Ÿ���ؽ���)
	BackgroundColor = { 0xff,0xff,0xff,0 };
}

void Engine::SDLTerm()
{
	TTF_Quit(); // TTF �޸� ����

	SDL_DestroyRenderer(MyRenderer); // ������ ����
	SDL_DestroyWindow(MyWindow); // ������ ����


	SDL_Quit(); // SDL Quit �Ͽ� �޸� ���� 
}

