#pragma once
#include "DoorObj.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class DoorObj;
class RoomObj{

private:
	vector<DoorObj*> doors;
	string roomName;
public:
	RoomObj(string name);
	void addDoor(DoorObj* door);
	string getName();
	vector<DoorObj*> getDoors();



};