#pragma once
#include "RoomObj.h"
#include <string>
#include <cstdlib>
class RoomObj;

using namespace std;
class DoorObj {
protected:
	RoomObj* roomOne;
	RoomObj* roomTwo;
	string directionA;
	string directionB;
	bool  secret;

public:
	DoorObj(RoomObj* room, string dir);
	void setRoomTwo(RoomObj* room);
	RoomObj* ShowNextRoom(RoomObj *current);
	string getDirection(RoomObj* room);
	bool isSecret();
};

class SecretDoorObj :public DoorObj {
public:
	SecretDoorObj(RoomObj* room, string dir);
};