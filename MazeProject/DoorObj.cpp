#include "DoorObj.h"

DoorObj::DoorObj(RoomObj* room, string dir) {
	roomOne = room;
	directionA = dir;
	secret = false;
}

/**
adds a connecting room and sets the second direction
*/
void DoorObj::setRoomTwo(RoomObj* room){
	roomTwo = room;
	if (directionA == "North") {
		directionB = "South";
	}
	else if (directionA == "South") {
		directionB = "North";
	}
	else if (directionA=="East") {
		directionB = "West";
	}
	else if(directionA=="West"){
		directionB = "East";
	}
	else if(directionA == "Floor"){
		directionB = "Ladder";
	}
	else if(directionA =="Ladder"){
		directionB = "Floor";
	}
}
/**
returns the next room
*/
RoomObj* DoorObj::ShowNextRoom(RoomObj* current) {
	if (current->getName() == roomOne->getName()) {
		return roomTwo;
	}
	else {
		return roomOne;
	}
}

/**
returns the rooms direction
*/
string DoorObj::getDirection(RoomObj* room) {
	
	string direction;
	if (room->getName() == roomOne->getName()) {
		direction = directionA;
	}
	else {
		direction = directionB;
	}
	return direction;

}

/**
checks if the door is secret
*/
bool DoorObj::isSecret() {
	return secret;
}

SecretDoorObj::SecretDoorObj(RoomObj* room, string dir) : DoorObj(room,  dir) {
	roomOne = room;
	directionA = dir;
	secret = true;
}
