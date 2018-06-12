#pragma once
#include "MazeObj.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
class GamePlay {

private:
	MazeObj* maze;
	RoomObj* room;
	bool complete;
	bool showMenu;
	int counter;
	void ui();
	void play();
	RoomObj* move(char dir);
	bool moveResult(string dir, DoorObj* door);
public:
	void menu();
};