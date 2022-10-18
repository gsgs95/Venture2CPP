#include "Text.h"

AText::AText()
{
	Content = "";
}

AText::AText(int X, int Y, string NewContent, int NewFontSize)
{
	this->X = X;
	this->Y = Y;
	Content = NewContent;
	FontSize = NewFontSize;
	MyColor = { 255,255,255,0 };
	ZOrder = 100;

	Font = TTF_OpenFont("./Data/NGULIM.TTF", FontSize);
	MySurface = TTF_RenderText_Solid(Font, Content.c_str(), MyColor);
	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);
}


AText::~AText()
{
	TTF_CloseFont(Font);
}

void AText::Render()
{
	SDL_Rect RenderRect = { X, Y, MySurface->w, MySurface->h }; // �ؽ��� ������ ���
	SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &RenderRect); // �ش� �������� �ش� �ؽ��ĸ� ���ۺ��� ������ �ش� ��翡 �����ض�
}


