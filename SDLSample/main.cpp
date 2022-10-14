#include "SDL.h"
#include <iostream>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")


int SDL_main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL 초기화. SDL_INITEVERYTHING: 몽땅다 초기화 플래그
	{
		SDL_Log("SDL_Init_Error");
		exit(-1);
	}

	SDL_Window* MyWindow = SDL_CreateWindow("MyGame", 100, 100, 600, 600, SDL_WINDOW_VULKAN); // 파라미터: 윈도우 화면 이름, 좌표 시작점 x,y , 윈도우 너비 높이 w,h, 윈도우 설정 플래그(SDL_WINDOW_VULKAN); 리턴값: 윈도우 포인터

	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); // 타깃 윈도우에 연결된 x번째 랜더러 생성하여 리턴, 속성플래그 가짐(현재 하드웨어 가속 & 타깃텍스쳐)

	// DrawCall

	int X = 0;

	while (1)
	{
		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0, 0, 0); // 랜더러 색상 설정 (타깃랜더러, r, g, b, a)
		SDL_RenderClear(MyRenderer); // 해당 렌더러에게 화면 지우게 시킴

		// 사각형 그리기
		if (X > 500)
		{
			X = 0;
		}
		SDL_SetRenderDrawColor(MyRenderer, 0x00, 0, 0xff, 0);
		SDL_Rect MyRect = { X++,100,100,100 };
		SDL_RenderDrawRect(MyRenderer, &MyRect);

		// 화면에 그리기
		SDL_RenderPresent(MyRenderer);
	}


	SDL_DestroyRenderer(MyRenderer); // 랜더러 삭제
	SDL_DestroyWindow(MyWindow); // 윈도우 삭제


	SDL_Quit(); // SDL Quit 하여 메모리 해제 

	return 0;
}