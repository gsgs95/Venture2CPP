//#include <conio.h> // _getch()
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
	SDLInit();
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
	//KeyCode = _getch();
	SDL_PollEvent(&MyEvent); //  메시지큐에서 이벤트를 꺼내서 MyEvent에 보관 (Polling : 업데이트 된게 있는지 계속 확인하는 방법.)
}

void Engine::Tick()
{
	if (MyEvent.type == SDL_QUIT)
	{
		bIsRunning = false;
	}

	MyWorld->Tick();
}

void Engine::Render()
{
	//system("cls");
	SDL_Color BackgroundColor = { 0, 0, 0, 0 };
	SDL_SetRenderDrawColor(MyRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a); // 랜더러 색상 설정 (타깃랜더러, r, g, b, a)
	SDL_RenderClear(MyRenderer); // 해당 렌더러에게 화면 지우게 시킴

	// 화면에 그리기
	SDL_RenderPresent(MyRenderer);

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

void Engine::SDLInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL 초기화. SDL_INITEVERYTHING: 몽땅다 초기화 플래그
	{
		SDL_Log("SDL_Init_Error");
		exit(-1);
	}

	MyWindow = SDL_CreateWindow("MyGame", 100, 100, 600, 600, SDL_WINDOW_VULKAN); // 파라미터: 윈도우 화면 이름, 좌표 시작점 x,y , 윈도우 너비 높이 w,h, 윈도우 설정 플래그(SDL_WINDOW_VULKAN); 리턴값: 윈도우 포인터

	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); // 타깃 윈도우에 연결된 x번째 랜더러 생성하여 리턴, 속성플래그 가짐(현재 하드웨어 가속 & 타깃텍스쳐)

}

void Engine::SDLTerm()
{
	SDL_DestroyRenderer(MyRenderer); // 랜더러 삭제
	SDL_DestroyWindow(MyWindow); // 윈도우 삭제


	SDL_Quit(); // SDL Quit 하여 메모리 해제 
}

