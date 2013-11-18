int main()
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

	b.print();
	cout << "value of b,1 should be e: " << b.getTileAt('a',3) << endl;
	cout << "value of a: " << b.charMap('a') << endl;
	cout << "***************************" << endl << "adjacency lists are ordered clockwise starting from \"up\"" << endl;

	vector<unsigned char> adjacent = b.getAdjacent('b',1);
	cout << "adjacency list for 'e' should be {b,f,h,d}" << endl;
	cout <<"{"<< adjacent[0]<<","<< adjacent[1]<<","<< adjacent[2]<<","<< adjacent[3]<<"}" << endl; 
	cout << endl;
	
	//new 3x4 board
	//     a b c 
	//
	// 0   a 0 c 
	// 1   0 e 0 
	// 2   g h i
	// 3   j k l 
	b.placeTile('b', 0, 0);
	b.placeTile('a', 1, 0);
	b.placeTile('c', 1, 0);
	b.print();

	vector<unsigned char> adjacent3 = b.getAdjacent('b',1);
	cout << "adjacency list for 'e' should be {h}" << endl;
	cout <<"{"<< adjacent3[0]<<"}" << endl; 
	cout << endl;

	/***********************************************************GROUP******************************************************************/
	Group<unsigned char> grp('V',3,0);
	cout <<"this group is labeled: "<<grp.getLabel() << endl;
	cout <<"this group was created on turn: "<<grp.getAge() << endl;
	// tiel:e			tile:j			tile:h
	grp.add('b',1); grp.add('a',3); grp.add('b',2);

	cout <<"this group has "<<grp.getSize() << " elements" << endl;
	cout <<"This group should contain h -> ('b',2) : "<< grp.contains('b',2) << endl;
	cout <<"but not contain a -> ('a',0) : "<< grp.contains('a',0) << endl;

	/***********************************************************BOARDGAME******************************************************************/
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
}
