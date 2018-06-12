#include "GamePlay.h"
#include "MazeCreator.h"
#include "MazeObj.h"
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <ctype.h>

using namespace std;

/**
load up a user menu
*/
void GamePlay::menu() {
	MazeCreator* mc = new MazeCreator();
	showMenu = true;	//checking if the user has quit
	complete = false;	//checkign if the maze is complete
	char option;		//user input

	while (showMenu) {

		system("CLS");

		//shows the menu
		cout << endl << "Menu" << endl << endl << "1. Basic Maze" << endl << "2. Load Maze From File" << endl << "3. Load Random Maze" << endl << "q. quit" << endl;
		cin >> option;

		//clears input buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');


		//gets the correct menu option and loads the maze or quits
		if (option == '1') {
			maze = mc->staticMaze();
			room = maze->getStart();
		}
		else if (option == '2') {
			maze = mc->loadMaze();
			room = maze->getStart();
		}
		else if (option == '3') {
			maze = mc->randomMaze();
			room = maze->getStart();
		}
		else if (option == 'q') {
			cout << "Exiting Maze" << endl;
			system("PAUSE");
			exit(1);
		}
		else {
			cout << endl << "invalid entry"<<endl;
			system("PAUSE");
		}
		if (maze != nullptr) {
			complete = false;
			play();
		}
	}
}

/**
displays the ui  while the users hasn't completed the maze
*/
void GamePlay::play() {
	char direction = 'z';
	while ((!complete)) {
		ui();
		if (maze->getEnd()->getName() == room->getName()) {
			complete = true;
			break;
		}

		cin >> direction;
		direction = tolower(direction);
		//clears input buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//checks if the user wants to quit
		if (direction == 'q') {
			cout << "Exiting Maze"<<endl;
			system("PAUSE");
			complete = true;
			delete maze;
		}
		else {
			//moves user
			room = move(direction);
		}
	}
}

/**
displays the ui
*/
void GamePlay::ui() {
	system("CLS");

	//defalt doors as closed
	string north = "--";
	string south = "--";
	string east = "|";
	string west = "|";
	string floor = " ";


	//showing door
	for each(DoorObj* d in room->getDoors()) {
		if ((d->getDirection(room) == "North")) {
			if (!d->isSecret()) {
				north = " ";
			}
		}
		else if ((d->getDirection(room) == "South")) {
			if (!d->isSecret()) {
				south = " ";
			}
		}
		else if (d->getDirection(room) == "East") {
			if (!d->isSecret()) {
				east = " ";
			}
		}
		else if (d->getDirection(room) == "West") {
			if (!d->isSecret()) {
				west = " ";
			}
		}
		else if ((d->getDirection(room) == "Floor") || (d->getDirection(room) == "Ladder")) {
			if (! d->isSecret()) {
				floor = "+";
			}
		}
	}

	//showing ui
	cout << endl << "------------" << north << "------------" << endl;
	cout << "|	 	 	 |" << endl;
	cout << "|	 	 	 |" << endl;
	cout << "|	 	 	 |" << endl;
	cout << west << "           " << floor << "            " << east << endl;
	cout << "|	 	 	 |" << endl;
	cout << "|			 |" << endl;
	cout << "|			 |" << endl;
	cout << "------------" << south << "------------" << endl;

	//checking if the player won
	if (maze->getEnd()->getName() == room->getName()){ 
		cout << "Victory! " << endl << "You have made it to the end of the maze"<<endl;
		system("PAUSE");
	}
	//outputing move update
	else {
		cout << endl << "This is room " << room->getName() << endl << "Enter W, A, S or D to navigate and E to inspect the floor.";
	}
}

/** 
updatign room based off player move
*/
RoomObj* GamePlay::move(char direction) {

	RoomObj* nextRoom = room;
	bool validDoor = false;

	//checks if the move is valid
	for each(DoorObj* d in room->getDoors()) {

		if ((direction == 'w') && (!validDoor)) {
			validDoor = moveResult("North", d);
		}
		else if ((direction == 's') && (!validDoor)) {
			validDoor = moveResult("South", d);
		}
		else if ((direction == 'd') && (!validDoor))
		{
			validDoor = moveResult("East", d);
		}
		else if ((direction == 'a') && (!validDoor))
		{
			validDoor = moveResult("West", d);
		}
		else if ((direction == 'e') && (!validDoor))
		{
			if ((moveResult("Floor", d)) || (moveResult("Ladder", d))) {
				validDoor = true;
			}
		}

		//returning the room if it's valid
		if (validDoor) {
			return d->ShowNextRoom(room);;
		}
	}
	//feeds back invalid direction
	if ((direction != 'w') && (direction != 'a') && (direction != 's') && (direction != 'd') && (direction != 'e')) {
		cout << "Invalid entry please enter: " << endl << "W for North" << endl << "A for West" << endl << "S for South" << endl << "D for East" << endl;
	}
	//feeds back invalid moves
	if (!validDoor) {
		cout << "You hit you're head agest the wall, it seems there was nothing there" << endl;
	}
	system("PAUSE");
	//returns the current room
	return nextRoom;
}

//returns if the move is valid
bool GamePlay::moveResult(string direction, DoorObj* d) {
	//checks if theres a door there
	if (d->getDirection(room) == direction) {
		//informs the player if they found a secret room
		if (d->isSecret()) {
			cout << "You've found a secret Door " << endl;
		}
		//tells the player what room they are heading into
		cout << "you begin to head into room " << (d->ShowNextRoom(room))->getName() << endl;
		return true;
	}
	return false;
}