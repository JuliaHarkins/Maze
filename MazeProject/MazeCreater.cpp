#include "MazeCreator.h"
#include "MazeObj.h"
#include "DoorObj.h"
#include <fstream>
#include <vector>
#include <random>
#include<map>

/**
loads defalt static maze
*/
MazeObj* MazeCreator::staticMaze() {

	//creating the maze
	MazeObj* maze = new MazeObj;

	//creating Rooms 
	RoomObj* a = new RoomObj("A");
	RoomObj* b = new RoomObj("B");
	RoomObj* c = new RoomObj("C");
	RoomObj* d = new RoomObj("D");
	RoomObj* e = new RoomObj("E");
	RoomObj* f = new RoomObj("F");
	RoomObj* g = new RoomObj("G");
	RoomObj* h = new RoomObj("H");
	RoomObj* i = new RoomObj("I");
	RoomObj* j = new RoomObj("J");
	RoomObj* k = new RoomObj("K");
	RoomObj* l = new RoomObj("L");
	RoomObj* m = new RoomObj("M");
	RoomObj* n = new RoomObj("N");

	//Linking room's Doors
	DoorObj* ac = new DoorObj(a, "East");
	DoorObj* af = new DoorObj(a, "West");
	DoorObj* bc = new DoorObj(b, "South");
	DoorObj* cd = new DoorObj(c, "East");
	SecretDoorObj* cg = new SecretDoorObj(c, "Floor");
	DoorObj* ch = new DoorObj(c, "South");
	DoorObj* de = new DoorObj(d, "East");
	DoorObj* fj = new DoorObj(f, "North");
	DoorObj* fk = new DoorObj(f, "West");
	DoorObj* hi = new DoorObj(h, "East");
	DoorObj* hl = new DoorObj(h, "West");
	DoorObj* hm = new DoorObj(h, "South");
	DoorObj* kl = new DoorObj(k, "South");
	DoorObj* mn = new DoorObj(m, "South");

	//setting the second room of the doors
	ac->setRoomTwo(c);
	af->setRoomTwo(f);
	bc->setRoomTwo(c);
	cd->setRoomTwo(d);
	cg->setRoomTwo(g);
	ch->setRoomTwo(h);
	de->setRoomTwo(e);
	fj->setRoomTwo(j);
	fk->setRoomTwo(k);
	hi->setRoomTwo(i);
	hl->setRoomTwo(l);
	hm->setRoomTwo(m);
	kl->setRoomTwo(l);
	mn->setRoomTwo(n);

	//adding the doors to rooms
	a->addDoor(ac);
	c->addDoor(ac);
	a->addDoor(af);
	f->addDoor(af);
	c->addDoor(bc);
	b->addDoor(bc);
	c->addDoor(cd);
	d->addDoor(cd);
	c->addDoor(cg);
	g->addDoor(cg);
	c->addDoor(ch);
	h->addDoor(ch);
	d->addDoor(de);
	e->addDoor(de);
	f->addDoor(fj);
	j->addDoor(fj);
	f->addDoor(fk);
	k->addDoor(fk);
	h->addDoor(hi);
	i->addDoor(hi);
	h->addDoor(hl);
	l->addDoor(hl);
	h->addDoor(hm);
	m->addDoor(hm);
	k->addDoor(kl);
	l->addDoor(kl);
	m->addDoor(mn);
	n->addDoor(mn);

	//adding all the rooms to the maze
	maze->addRoom(a);
	maze->addRoom(b);
	maze->addRoom(c);
	maze->addRoom(d);
	maze->addRoom(e);
	maze->addRoom(f);
	maze->addRoom(g);
	maze->addRoom(h);
	maze->addRoom(i);
	maze->addRoom(j);
	maze->addRoom(k);
	maze->addRoom(l);
	maze->addRoom(m);
	maze->addRoom(n);

	return maze;
}

/**
loads a random maze
*/
MazeObj* MazeCreator::randomMaze() {

	vector<string> direction{ "North", "South", "East", "West", "Floor" };		//creating a vector for the directions
	vector<RoomObj*> rooms;														//creating a vector for the rooms prior to adding them to the maze
	MazeObj* maze = new MazeObj;

	random_device rd;	// seed
	mt19937 rng(rd());	// random-number engine

	uniform_int_distribution<int> randomRoom(10, 26);	// the range of potential rooms
	uniform_int_distribution<int> randomDir(1, 5);		//a random number to be taken from the direction vector
	uniform_int_distribution<int> maxDoor(1, 2);		// the  amount of default doors for a room

	int roomLimit = randomRoom(rng);	//creating the room limit
	int doorDir = randomDir(rng);		// creating the direction per door

	rooms.resize(roomLimit);			// setting the rooms array to the same as the room limit

	// creating and adding all the rooms
	for (int r = 0; r < roomLimit; r++) {
		rooms[r] = new RoomObj(to_string(r));
	}

	int roomTwo;				// the number of a room within the array to apply a second  to the door.
	bool same;					//booling to ensure information is valid
	bool inUse = false;			//used to check if the rooms direction is in use
	string dir;					// the direction the door is facing
	DoorObj* door = nullptr;
	int i =0;					//loop index/ current room number
	uniform_int_distribution<int> getRandomIndex(i, roomLimit - 1);		// gets an index greater then the current room

	for (i = 0; i < roomLimit; i++) {

		int doorCount = maxDoor(rng);

		for (int d = 0; d < doorCount; d++) {
			same = true;
			//checks if theres a door in that direction already and creates it if it does not
			if (door == nullptr || ((door->getDirection(rooms[i]) != direction[0]) || (door->getDirection(rooms[i]) != direction[1]) || (door->getDirection(rooms[i]) != direction[2]) || (door->getDirection(rooms[i]) != direction[3]) || (door->getDirection(rooms[i]) != direction[4]))) {

				while (same) {
					dir = direction[randomDir(rng)-1];
					inUse = checkIfExists(dir, rooms[i]);

					if (!inUse) {
						door = new DoorObj(rooms[i], dir);
						rooms[i]->addDoor(door);
						same = false;
					}
				}
			}

			same = true;
			//assines a randomly choosen second room that isn't itself and isn't already taken.
			while (same) {

				roomTwo = getRandomIndex(rng);
				inUse = checkIfExists(secondDir(dir), rooms[roomTwo]);

				if (roomTwo != i && !inUse) {

					rooms[roomTwo]->addDoor(door);
					door->setRoomTwo(rooms[roomTwo]);
					
					same = false;
				}
			}
		}
	}
	// adding the rooms to the maze
	for each(RoomObj* r in rooms) {
		maze->addRoom(r);
	}
	return maze;
}
/**
loads a maze from a file
*/
MazeObj* MazeCreator::loadMaze() {
	MazeObj* maze = new MazeObj;	
	ifstream mazeFile;				//the maze file
	string name1;					//name of the first room
	string dir;						//direction of door
	string name2;					//name of the second room
	RoomObj* room = nullptr;
	DoorObj* door = nullptr;
	map <string, RoomObj*> roomList;
	mazeFile.open("maze.txt");

	//creating an error if the file does not exist
	if (mazeFile.fail()) {
		cerr << "file could not load, file does not exist"<<endl;
		system("PAUSE");
		exit(1);
	}

	//checks if the files open
	if (mazeFile.is_open()) {

		//read until the end of the file
		while (!mazeFile.eof()) {

			//takes information from the file
			mazeFile >> name1 >> dir >> name2;

			//adding rooms to the map
			if (roomList.count(name1) == 0) {
				room = new RoomObj(name1);
				roomList[name1] = room;
			}

			// attaching the door to the first room
			room = roomList[name1];
			door = new DoorObj(room, dir);
			room->addDoor(door);

			//adding the second room to the map
			if (roomList.count(name2) == 0) {
				room = new RoomObj(name2);
				roomList[name2] = room;
			}

			//attachign the door to the second room
			room = roomList[name2];
			door->setRoomTwo(roomList[name2]);
			room->addDoor(door);
		}
		//closes the file
		mazeFile.close();

		//gets rooms from the map and adds them to the maze
		for (auto x: roomList) {
			maze->addRoom(x.second);
		}		
	}
	return maze;
}

/**
checks a door is already facing that direction
*/
bool MazeCreator::checkIfExists(string dir, RoomObj* room) {
	
	bool inUse = false;
	string floor = "Floor";
	string ladder = "Ladder";
	string roomDir;

	//checks each door in the room to find out if the direction is taken
	for each(DoorObj* d in room->getDoors()) {

		roomDir = d->getDirection(room);
		if (dir == floor || dir == ladder) {
			if (roomDir == floor) {
				return true;
			}
			else if (roomDir == ladder){
				return true;
			}
		}
		else if ( roomDir== dir) {
			return true;
		}
	}
	return false;
}

/**
sets the seccons direction of the door
*/
string MazeCreator::secondDir(string dir) {
	if (dir == "North") {
		return "South";
	}
	else if (dir == "South") {
		return "North";
	}
	else if (dir == "East") {
		return  "West";
	}
	else if (dir == "West") {
		return "East";
	}
	else if (dir == "Floor") {
		return  "Ladder";
	}
	else {
		return  "Floor";
	}
}