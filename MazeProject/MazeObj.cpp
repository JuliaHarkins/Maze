#include "MazeObj.h"

/**
adds a room to the maze
*/
void MazeObj::addRoom(RoomObj* room) {
	rooms.push_back(room);
}
/**
returns the first room in the maze
*/
RoomObj* MazeObj::getStart() const{
	return rooms.front();
}
/**
returns the last room in the maze
*/
RoomObj* MazeObj::getEnd() const {
	return rooms.back();
}