#include "SoundActor.h"
#include "MyEngine.h"
#include "World.h"

ASoundActor::ASoundActor()
	: FileName{ "" }, bIsLoop{ false }, Music{ nullptr }, Sound{ nullptr }, Volume{ 30 }, ElapsedTime{ 0 }, ExcuteTime{ 100 }
{
}

ASoundActor::ASoundActor(string InFileName, bool InIsLoop)
	: ASoundActor()
{
	FileName = InFileName;
	bIsLoop = InIsLoop;
	if (bIsLoop)
	{
		Music = Mix_LoadMUS(FileName.c_str());
		Mix_PlayMusic(Music, bIsLoop);
	}
	else
	{
		Sound = Mix_LoadWAV(FileName.c_str());
		Mix_PlayChannel(-1, Sound, bIsLoop);
		ExcuteTime = 100;
	}
}

ASoundActor::~ASoundActor()
{
	if (Music)
	{
		Mix_FreeMusic(Music);
	}
	if (Sound)
	{
		Mix_FreeChunk(Sound);
	}
}

void ASoundActor::Play()
{
	if (Music)
	{
		Mix_PlayMusic(Music, bIsLoop);
	}
	if (Sound)
	{
		Mix_PlayChannel(-1, Sound, false);
	}
}

void ASoundActor::Stop()
{
	if (Music)
	{
		Mix_HaltMusic();
	}
	if (Sound)
	{
		Mix_HaltChannel(-1);
	}
}

void ASoundActor::BeginPlay()
{
	if (Music)
	{
		Play();
	}

}


void ASoundActor::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ExcuteTime <= ElapsedTime && !bIsLoop)
	{
		GEngine->GetWorld()->DestroyActor(this);
		//GEngine->QuitGame();
	}
}

void ASoundActor::Render()
{
}
