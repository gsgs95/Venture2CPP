#pragma once
#include "Actor.h"
#include "SDL_ttf.h"
#include "MyEngine.h"
#include <string>
#include <Windows.h> // 다국어 지원 wstring

class AText :
    public AActor
{
public:
    AText();
    AText(int X, int Y, string NewContent, int NewFontSize);
    ~AText();

    virtual void  Render() override;

    string Content;
    int FontSize;
    TTF_Font* Font;
};

