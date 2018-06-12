#include "GamePlay.h"

int main() {
	GamePlay* gp = new GamePlay();
	//loads the menu and plays
	gp->menu();
	system("PAUSE");
	//quites the program
	return 1;

}