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
#include "SoundActor.h"

using namespace std;

int Engine::KeyCode = 0;

Engine::Engine()
	: MyWorld{ new FWorld{} }, bIsRunning{ true }
{
	srand(static_cast<unsigned int>(time(NULL))); // 엔진 생성시 랜덤시드 초기화
	SDLInit();
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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


void Engine::LoadLevel(string MapFileName)
{
	ifstream MapFile(MapFileName);
	UnloadLevel();

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

	
	// MyWorld의 ActorList를 ZOrder의 오름차순으로 Sort
	sort(MyWorld->ActorList.begin(), MyWorld->ActorList.end(), AActor::ActorCmp);

	SpawnActor(new ASoundActor("./Data/bgm.mp3",true));
}

void Engine::Run()
{
	BeginPlay();
	while (bIsRunning)
	{
		DeltaSeconds = SDL_GetTicks64() - LastTick;
		Input();
		Tick(); // 물리, 위치 등 처리
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
	SDL_PollEvent(&MyEvent); //  메시지큐에서 이벤트를 꺼내서 MyEvent에 보관 (Polling : 업데이트 된게 있는지 계속 확인하는 방법.)
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
	SDL_SetRenderDrawColor(MyRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a); // 랜더러 색상 설정 (타깃랜더러, r, g, b, a)
	SDL_RenderClear(MyRenderer); // 해당 렌더러에게 화면 지우게 시킴

	

	MyWorld->Render();
	// 화면에 그리기
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

void Engine::UnloadLevel()
{
	MyWorld->Terminate();
}


void Engine::SDLInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL 초기화. SDL_INITEVERYTHING: 몽땅다 초기화 플래그
	{
		SDL_Log("SDL_Init_Error");
		exit(-1);
	}

	MyWindow = SDL_CreateWindow("MyGame", 100, 100, 600, 600, SDL_WINDOW_VULKAN); // 파라미터: 윈도우 화면 이름, 좌표 시작점 x,y , 윈도우 너비 높이 w,h, 윈도우 설정 플래그(SDL_WINDOW_VULKAN); 리턴값: 윈도우 포인터
	//MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); // 타깃 윈도우에 연결된 x번째 랜더러 생성하여 리턴, 속성플래그 가짐(현재 하드웨어 가속 & 타깃텍스쳐)
	BackgroundColor = { 0xff,0xff,0xff,0 };
}

void Engine::SDLTerm()
{
	TTF_Quit(); // TTF 메모리 해제

	SDL_DestroyRenderer(MyRenderer); // 랜더러 삭제
	SDL_DestroyWindow(MyWindow); // 윈도우 삭제


	SDL_Quit(); // SDL Quit 하여 메모리 해제 
}

void Engine::SpawnActor(AActor* NewActor)
{
	if (NewActor)
	{
		MyWorld->ActorList.push_back(NewActor);
	}
}

