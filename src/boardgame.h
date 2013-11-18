#ifndef BOARDGAME
#define BOARDGAME

#include "board.h"
#include "group.h"
#include <iostream>
#include <list>

using namespace std;

template <class T> class BoardGame {
	int d_rows;
	int d_cols;
	Board <T> d_b;
	map <T, Group*> d_groups;
public:
	BoardGame(int rows=0, int cols=0): d_rows(rows), d_cols(cols){};

	playAt(Position& pos){
		//is it a valid play
		//TODO

		// place tile
		d_b.placeTile(pos.getX(), pos.getY(), T);

		//get the adjacent tiles
		vector<T> adjacents = d_b.getAdjacent(pos.getX(), pos.getY());
		
		//NONE? This is an independent

		//ONE: creating or increasing size	
			//is adj already a group?
				//NO
				//Create a new group
				//Remove group from valid groups list
				//YES
				// increase group size by 1 (unless same group again)
				// assign tile to group
		//2+: increase size or merge
			//is there more than one group in the adj. list?
				//NO
				//increase group size by 1 (unless same group again)
				// assign tile to group
				//YES: MERGER 
				// get list of groups involved - groups only counted once, even if there is more than one tile in the list
				// sort by group size
				// For each (groups - 1)
					//Larger group eats smaller group
						//assign all tiles from one group to the next
						//increase the size of the larger group by that of the smaller
						//add all tiles from smaller group to larger group
					//add the (now empty) smaller group back into the valid groups list

	};
};

#endif
