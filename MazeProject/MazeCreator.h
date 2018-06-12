#pragma once
#include "MazeObj.h"

class MazeCreator {
private:
	bool checkIfExists(string dir, RoomObj* room);
	string secondDir(string dir);
public:
	MazeObj* staticMaze();
	MazeObj* randomMaze();
	MazeObj* loadMaze();
	

};