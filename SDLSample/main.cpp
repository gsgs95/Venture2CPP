#include "SDL.h"
#include <iostream>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")


int SDL_main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL �ʱ�ȭ. SDL_INITEVERYTHING: ������ �ʱ�ȭ �÷���
	{
		SDL_Log("SDL_Init_Error");
		exit(-1);
	}

	SDL_Window* MyWindow = SDL_CreateWindow("MyGame", 100, 100, 600, 600, SDL_WINDOW_VULKAN); // �Ķ����: ������ ȭ�� �̸�, ��ǥ ������ x,y , ������ �ʺ� ���� w,h, ������ ���� �÷���(SDL_WINDOW_VULKAN); ���ϰ�: ������ ������

	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); // Ÿ�� �����쿡 ����� x��° ������ �����Ͽ� ����, �Ӽ��÷��� ����(���� �ϵ���� ���� & Ÿ���ؽ���)

	// DrawCall

	int X = 0;
	SDL_Color BackgroundColor = { 0xff, 0, 0, 0 };

	while (1)
	{
		SDL_SetRenderDrawColor(MyRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a); // ������ ���� ���� (Ÿ�귣����, r, g, b, a)
		SDL_RenderClear(MyRenderer); // �ش� ���������� ȭ�� ����� ��Ŵ

		// �簢�� �׸���
		if (X > 500)
		{
			X = 0;
		}
		SDL_SetRenderDrawColor(MyRenderer, 0x00, 0, 0xff, 0);
		SDL_Rect MyRect = { X++,100,100,100 };
		SDL_RenderDrawRect(MyRenderer, &MyRect);

		
		// �޽��� ����: �޽����� �������� ó���ϴ� ����

		SDL_Event MyEvent; // �̺�Ʈ �ν��Ͻ� ����
		SDL_PollEvent(&MyEvent); //  �޽���ť���� �̺�Ʈ�� ������ MyEvent�� ���� (Polling : ������Ʈ �Ȱ� �ִ��� ��� Ȯ���ϴ� ���.)

		if (MyEvent.type == SDL_QUIT) // ������ �ݱ� ��ư ������ �̺�Ʈ
		{
			break;
		}
		else if (MyEvent.type == SDL_KEYDOWN) // Ű������ �ƹ�Ű�� ������ ����
		{
			BackgroundColor = { 0xff, 0xff, 0, 0 };
		}
		else if (MyEvent.type == SDL_KEYUP)
		{
			BackgroundColor = { 0xff, 0, 0, 0 };
		}

		// ȭ�鿡 �׸���
		SDL_RenderPresent(MyRenderer);


	}


	SDL_DestroyRenderer(MyRenderer); // ������ ����
	SDL_DestroyWindow(MyWindow); // ������ ����


	SDL_Quit(); // SDL Quit �Ͽ� �޸� ���� 

	return 0;
}