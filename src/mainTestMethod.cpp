// C++GroupProjectGame.cpp : Defines the entry point for the console application.
//

#include "board.h"
#include "boardgame.h"
#include "company.h"
#include <iostream>
#include <map>

//This is the basis for our game. 
int main(){
	int maxX = 10;
	int maxY = 10;
	int playOn = 666;
	unsigned char x = 63;
	int y = maxY+10;

	Position pos('a',0);
	cout << "10x10 board, first group to 12 wins." << endl;

	BoardGame<unsigned char> bGame(maxX,maxY);
	//    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
	//0   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
	//1   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
	//2   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
	//    ...................................................
	//24  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
	//25  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 


	while (playOn > 0){
		cout << bGame << endl;

		/** 
		while (! bGame.goodPos(x, y)){
			cout << "choose (char) X position ['A','" << (char)(maxX+64) << "']" << endl << "X: ";
			cin >> x;
			cout << "choose (int) Y position [0," << maxY-1 << "]" << endl << "Y: ";
			cin >> y;

			if (! bGame.goodPos(x, y)){
				cout << "Out of bounds, please choose again." << endl;
			}
		}**/
		
		/** auto game.. it plays itself, but almost always fills column a first due to how mod-random tends to work **/
		if (! bGame.outOfMoves()){
			pos = bGame.popValidMove();
			bGame.playAt(pos);
		} else {
			cout << "Out of Moves" << endl;
			playOn = -1;	
		}/**/

		//we need new x and y next turn
		x = 63;
		y = maxY+10;
		
	
		if(bGame.gameOver()){
			cout << "A Group just became at least size 12! Game over" << endl;
			playOn = -1;
			cout << bGame << endl;
		}
		
	}

	cin >> x;
	return playOn;
}
/*********************************************WIP Testing method***************************************************/
int wip_main(){ 
	unsigned char label = 'V';
	Company<unsigned char> cmpy(label,3,0);
	cmpy.setSize(15);
	cmpy.print();
	Company<unsigned char> cmpy2(label-3,4,0);
	cmpy2.setSize(30);
	cmpy2.print();

	cout << "Mergeable: " << cmpy.mergeRequest() << endl;

	int maxX = 15;
	int maxY = 15;
	int playOn = 666;
	unsigned char x = 63;
	int y = maxY+10;

	Position pos('a',0);
	cout << "15x15 board, first group to 12 wins." << endl;

	BoardGame<unsigned char> bGame(maxX,maxY);

	pos = bGame.popValidMove();
	cout << "Valid move from stack: (" << pos.getX() << "," << pos.getY() << ")" << endl;
	Player<unsigned char> sim("Simeon");
	sim.buy(12, cmpy);
	sim.buy(4, cmpy2);
	cout << sim << endl;

	sim.sell(cmpy2);
	cout << sim;
	/***************************/
	cin>> label;
	return 100;
}

/*********************************************This is a messy print-all log type main method used for testing***************************************************/
int log_main()
{
	
	/***********************************************************BOARD******************************************************************/
	// 3x4 board
	//     a b c 
	//
	// 0   a b c 
	// 1   d e f 
	// 2   g h i
	// 3   j k l 
	Board<unsigned char> b(3,4);
	unsigned char letter = 'a';
	//fill b
	for(int j = 0; j <4; j++){
		for(char i = 'a'; i <'a'+3; i++){
			b.placeTile(i, j, letter);
			letter ++;
		}		
	}

	cout << b;
	cout << "value of b,1 should be e: " << b.getTileAt('b',1) << endl;
	cout << "value of a: " << b.charMap('a') << endl;
	cout << "***************************" << endl << "adjacency lists are ordered clockwise starting from \"up\"" << endl;

	vector<pair<unsigned char, char> > adjacent = b.getAdjacent('a',1);
	cout << "adjacency list for ('a',1) should be {a,e,g}" << endl;
	cout <<"{"<< adjacent[0].first <<","<< adjacent[1].first <<","<< adjacent[2].first <<"}" << endl; 
	cout << endl;
	
	//new 3x4 board
	//     a b c 
	//
	// 0   a 0 c 
	// 1   0 e 0 
	// 2   g h i
	// 3   j k l 
	b.placeTile('a', 3, '+');
	b.placeTile('b', 2, '+');
	b.placeTile('b', 3, 0);
	b.placeTile('c', 3, '+');
	cout << b;

	vector<pair<unsigned char, char> > adjacent3 = b.getAdjacent('b',3);
	cout << "adjacency list for 'k' should be {+, +, +}" << endl;
	cout <<"{"<< adjacent3[0].first <<","<< adjacent3[1].first <<","<< adjacent3[2].first <<"}" << endl; 
	cout << endl;

	/***********************************************************GROUP******************************************************************/
	Group<unsigned char> grp('V',3,0);
	Group<int> g2(666,1,0);

	cout << "dummy values for: unsigned char - " << grp.getDummy();
	cout << ", int - " << g2.getDummy() << endl;

	cout <<"this group is labeled: "<<grp.getLabel() << endl;
	cout <<"this group was created on turn: "<<grp.getAge() << endl;
	// tile:e			tile:j			tile:h
	grp.add('b',1); grp.add('a',3); grp.add('b',2);

	cout <<"this group has "<<grp.getSize() << " elements" << endl;
	cout <<"This group should contain h -> ('b',2) : "<< grp.contains('b',2) << endl;
	cout <<"but not contain a -> ('a',0) : "<< grp.contains('a',0) << endl << endl;

	Group<unsigned char> grp2('W',4,0);
	// tile:k			tile:l		
	grp2.add('b',3); grp2.add('c',3);
	cout <<"new group is labeled: '"<<grp2.getLabel() << "' and is of size(" << grp2.getSize() << ")" << endl;
	cout <<"Adding all of group 'W'" << endl;
	grp2.addAll(&grp);
	cout <<grp.getLabel() << " is of size(" << grp2.getSize() << ")" << endl;
	cout <<"Removing 'j' from group 'W'" << endl;
	grp2.remove('a',3);
	cout << grp2.getLabel() << " is now of size(" << grp2.getSize() << ")" << endl;

	for (int i = 0; i < 44; i++){
		cout << ":" << grp2.getSize();
		if (grp2.add(i, i)){
			i = 55;
			cout << " -- Game over!!!!!!!!!" << endl;
		}
	}
	
	/***********************************************************BOARDGAME******************************************************************/
	BoardGame<unsigned char> bGame(3,4);
	// 0 0 0
	// 0 0 0
	// 0 0 0
	// 0 0 0

	bGame.printValids();

	cout << "Add 6 new groups...." << endl;
	bGame.addNewGroup();
	bGame.addNewGroup();
	bGame.addNewGroup();
	bGame.addNewGroup();
	bGame.addNewGroup();
	bGame.addNewGroup();

	bGame.printValids();
	bGame.printGroups();

	bGame.removeUnusedGroup('A');
	bGame.removeUnusedGroup('W');
	bGame.removeUnusedGroup('E');

	bGame.printValids();
	bGame.printGroups();

	BoardGame<unsigned char> cGame(3,4);
	cout << cGame << endl; 
	//     a b c 
	//
	// 0   + 0 0 
	// 1   0 0 0 
	// 2   0 0 0
	// 3   + 0 0 
	Position newPos('a',0);
	cGame.playAt(newPos);
	newPos.set('a',3);
	cGame.playAt(newPos);
	cout << cGame << endl;
	cout << "NEW PLAY THAT MAKES A NEW GROUP" << endl;
	newPos.set('b',3);
	cGame.playAt(newPos);
	cout << cGame << endl;
	newPos.set('c',3);
	cGame.playAt(newPos);
	cout << cGame << endl;
	newPos.set('a',1);
	cGame.playAt(newPos);
	newPos.set('b',0);
	cGame.playAt(newPos);
	newPos.set('c',0);
	cGame.playAt(newPos);
	newPos.set('b',1);
	cGame.playAt(newPos);
	cout << cGame << endl;
	cout << "MERGE INCOMING!!!!" << endl;
	newPos.set('a',2);
	cGame.playAt(newPos);
	cout << cGame << endl;
	cout << "Corner Play! Only one group, multiple adjacents" << endl;
	newPos.set('b',2);
	cGame.playAt(newPos);
	cout << cGame << endl;

	cout << "CLEAR THE BOARDGAME!!!!" << endl;
	cGame.clearBoard();
	cout << cGame << endl;
	cGame.printValids();
	cGame.printGroups();

	//     a b c 
	//
	// 0   A 0 B 
	// 1   A 0 B 
	// 2   0 C 0
	// 3   C C C 
	newPos.set('a',0);
	cGame.playAt(newPos);
	newPos.set('a',1);
	cGame.playAt(newPos);
	newPos.set('c',0);
	cGame.playAt(newPos);
	newPos.set('c',1);
	cGame.playAt(newPos);
	newPos.set('a',3);
	cGame.playAt(newPos);
	newPos.set('b',3);
	cGame.playAt(newPos);
	newPos.set('c',3);
	cGame.playAt(newPos);
	newPos.set('b',2);
	cGame.playAt(newPos);
	cout << cGame << endl;

	cout << "3-way merge!! C should win" << endl;
	newPos.set('b',1);
	cGame.playAt(newPos);
	cout << cGame << endl;
	/**
	Board board(9,12);
	stack<Position> position = generatePositions();
	Array players = createPlayers();
	int turn = 0;
	list<Position> availablePositions;
	//get the initial positions
	for (int i=0; i<8; i++){
		availablePositions.push_back(positions.pop());
	}

	do {
		// print board and current player
		cout << board;

		Player& currentPlayer = players[turn%players.
	}
	**/

	cout << endl;
	int c;
	cin >> c;

	return c;
}

