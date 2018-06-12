#include "RoomObj.h"
#include "DoorObj.h"

/**
creates a room
*/
RoomObj::RoomObj(string name) {
	roomName = name;
}

/** 
adds a door to the room
*/
void RoomObj::addDoor(DoorObj* door)
{
	doors.push_back(door);
}
/**
returns the name of the room
*/
string RoomObj::getName()
{
	return roomName;
}
/**
returns the doors of the room
*/
vector<DoorObj*> RoomObj:: getDoors() {
	return doors;
}