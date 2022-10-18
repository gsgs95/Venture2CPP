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
	SDL_Rect RenderRect = { X, Y, MySurface->w, MySurface->h }; // 텍스쳐 맵핑할 모양
	SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &RenderRect); // 해당 랜더러로 해당 텍스쳐를 시작부터 끝까지 해당 모양에 맵핑해라
}


