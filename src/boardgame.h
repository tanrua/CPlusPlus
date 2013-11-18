#ifndef BOARDGAME
#define BOARDGAME

#include "board.h"
#include "group.h"
#include <iostream>
#include <list>
#include <map>

using namespace std;

template <class T> class BoardGame {
	int d_rows;
	int d_cols;
	T d_dum;
	Board <T> d_b;
	map <T, Group<T>* > d_groups;
public:
	BoardGame(int rows=0, int cols=0): d_rows(rows), d_cols(cols) {
		//add empty dummy group
		d_b = Board<T>(d_rows, d_cols);
		Group<T> tmp(0,0,0);
		d_dum = tmp.getDummy();
		Group<T> dummy(d_dum,0,0);
		//cout << "dummy: " << d_dum << endl;
		pair<T, Group<T>*> dummyPair;
		dummyPair = make_pair(d_dum, dummy);
		//d_groups.insert(map<T, Group<T>*>::value_type(d_dum, dummy));
	};

	void playAt(Position& pos){
		//is it a valid play
		//TODO

		// place tile
		d_b.placeTile(pos.getX(), pos.getY(), T);

		//get the adjacent tiles
		vector<T> adjacents = d_b.getAdjacent(pos.getX(), pos.getY());
		
		//NONE? This is an independent
		if(adjacents.size() == 0){
			//add tile to dummy group
			Group<T>* grp = d_groups[d_dum];
			grp->add(pos.getX(), pos.getY());
		} else if(adjacents.size() == 1) {
		//ONE: creating or increasing size	
			//is adj already a group?
				//NO - aka dummy
				//Create a new group
				//Remove group from valid groups list
				//Remove tile from dummy group 
				//YES
				// increase group size by 1 (unless same group again)
				// assign tile to group
		} else {
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
						//add all tiles from smaller group to larger group (placeTile for all elements with new group key)
					//add the (now empty) smaller group back into the valid groups list
		}
		
		

	};
};

#endif
