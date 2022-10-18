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

	wstring UniCode(Content.length(), 0);
	MultiByteToWideChar(CP_ACP, 0, Content.c_str(), (int)Content.length()
	,(LPWSTR)UniCode.c_str(), (int)Content.length() + 1);

	Font = TTF_OpenFont("./Data/NGULIM.TTF", FontSize);
	//MySurface = TTF_RenderText_Solid(Font, Content.c_str(), MyColor);
	SDL_Color BackgroundColor = { 0xff,0,0,0 };
	MySurface = TTF_RenderUNICODE_Shaded(Font, (Uint16*)UniCode.c_str(), MyColor, BackgroundColor);
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


