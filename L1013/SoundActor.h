#pragma once
#include "Actor.h"
#include "SDL_mixer.h"

class ASoundActor :
    public AActor
{
public:
    ASoundActor();
    ASoundActor(string InFileName, bool InIsLoop);
    ~ASoundActor();

    void Play();
    void Stop();

    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void Render() override;

    string FileName;
    bool bIsLoop;
    int Volume;
    
    Uint64 ElapsedTime;
    Uint64 ExcuteTime;

    Mix_Music* Music;
    Mix_Chunk* Sound;
};

