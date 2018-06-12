#pragma once
#include "Roomobj.h"
class MazeObj
{
private:
	vector<RoomObj*> rooms;
public:
	RoomObj* getStart() const;
	RoomObj* getEnd() const;
	void addRoom(RoomObj *room);
};