#pragma once

#ifndef __ENGINE_H__
#define __ENGINE_H__
#include <Windows.h>
#include <string>
#include <vector>
#include "SDL.h"

using namespace std;

class FWorld;
//class AActor;

class Engine
{
protected:
	Engine();

public:
	virtual ~Engine();
	
	void Gotoxy(int X, int Y);

	virtual void Initialize() = 0;
	virtual void Terminalize() = 0;

	FWorld& GetWorld() const;
	void CursorView(bool view);

	void Run();
	void QuitGame();


	/*__forceinline 강제 인라인*/
	static inline int GetKeyCode()
	{
		return KeyCode;
	}

	vector<class AActor*>& GetAllActors();


	void SDLInit();
	void SDLTerm();

	SDL_Window* MyWindow;
	SDL_Renderer* MyRenderer;
	SDL_Event MyEvent; // 이벤트 인스턴스 생성


protected:
	virtual void Input();
	virtual void Tick();
	virtual void Render();
	virtual void BeginPlay();
	virtual void EndPlay();

	void Load(string MapFileName);
	
	FWorld* MyWorld;
	static int KeyCode;
	bool bIsRunning = true;
};


//int Engine::KeyCode = 0;
#endif
