#include <iostream>
#include <vector>
#include <fstream>

#include "MyEngine.h"

#include "World.h"

#include "SDL.h"
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

using namespace std;


int SDL_main(int argc, char* argv[])
{
	// Engine
	// Load
	GEngine->Initialize();
	GEngine->Run();
	GEngine->Terminalize();

	// Quit
	delete GEngine;


	/*
#ifdef _DEBUG
	vector<AWall*> MyWalls;
	vector<APlayer*> MyPlayers;
	vector<AFloor*> MyFloors;
	vector<AGoal*> MyGoals;

	MyPlayers.push_back(new APlayer(1, 1));

	MyWalls.push_back(new AWall(0, 0));
	MyWalls.push_back(new AWall(0, 1));
	MyWalls.push_back(new AWall(0, 2));
	MyWalls.push_back(new AWall(0, 3));
	MyWalls.push_back(new AWall(1, 3));
	MyWalls.push_back(new AWall(2, 3));
	MyWalls.push_back(new AWall(3, 3));
	MyWalls.push_back(new AWall(4, 3));

	for (auto Value : MyWalls)
	{
		Value->Draw();
	}

	for (auto Value : MyPlayers)
	{
		Value->Draw();
	}

	cout << endl << endl;

	for (auto Value : MyWalls)
	{
		delete Value;
	}
	MyWalls.clear();
#endif
*/

	return 0;
}