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
	//new valid groups will ALWAYS be increasing. even when they are unused.
	vector<T> d_validGroups;
	int d_turn;
public:
	BoardGame(int rows=0, int cols=0): d_rows(rows), d_cols(cols), d_turn(0) {
		//add empty dummy group
		d_b = Board<T>(d_rows, d_cols);
		Group<T> tmp(0,0,0);
		d_dum = tmp.getDummy();
		Group<T> dummy(d_dum,0,0);

		d_groups.insert(make_pair(d_dum, &dummy));

		//Initialize the valid groups. Default 10.
		int maxValids=10;
		if ((typeid(T) == typeid(char)) || (typeid(T) == typeid(unsigned char))) {
				T label = 'A';
				for (int i=0; i<maxValids; i++){
					d_validGroups.push_back(label);
					label++;
				}
		} else {
				T label = 1;
				for (int i=0; i<maxValids; i++){
					d_validGroups.push_back(label);
					label++;
				}
		}
	};

	void playAt(Position& pos){
		//is it a valid play
		//TODO

		//get the adjacent tiles
		vector<T> adjacents = d_b.getAdjacent(pos.getX(), pos.getY());
		
		//NONE? This is an independent
		if(adjacents.size() == 0){
			//add tile to dummy group
			Group<T>* grp = d_groups[d_dum];
			grp->add(pos.getX(), pos.getY());
			// place tile
			d_b.placeTile(pos.getX(), pos.getY(), d_dum);
		} else if(adjacents.size() == 1) {
		//ONE: creating or increasing size
			//is adj already a group?
			//NO - aka dummy
			if(adjacents[0] == d_dum){
				//Create a new group if possible boolean on success
				addNewGroup();
				//Remove tile from dummy group 
				Group<T>* dummy = d_groups.at(d_dum);
				dummy->remove(pos.getX(), pos.getY());
			}
				
				//YES
				// increase group size by 1 (unless same group again)
				// assign tile to group
			// place tile
			d_b.placeTile(pos.getX(), pos.getY(), T);
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
			// place tile
			d_b.placeTile(pos.getX(), pos.getY(), T);
		}

		//a turn has taken place
		d_turn++;
	};

	bool addNewGroup() {
		//can only do this if there are still valid groups left to add
		if (d_validGroups.size() == 0){
			return false;
		} else {
			//take the first element label.
			T currentLabel = d_validGroups.at(0);

			//make a new group of size 0 at this turn and add it to the map of groups
			Group<T> tmp(currentLabel, d_turn, 0);
			d_groups.insert(make_pair(currentLabel, &tmp));

			//then remove the first element of valid groups so we don't use it again.
			d_validGroups.erase(d_validGroups.begin());

			return true;
		}
	}

	bool removeUnusedGroup(T label) {
		if (d_groups.find(label) == d_groups.end()){
			return false;
		} else {
			d_groups.erase(label);
			d_validGroups.push_back(label);
			return true;
		}
	}

	void printValids(){
		cout << "Valid groups left to choose from are: ";
		for (int i=0; i<d_validGroups.size(); i++){
			cout << " '" << d_validGroups.at(i) << "' ";
		}
		cout << endl;
	}

	void printGroups(){
		cout << "Groups in play are: ";
		for(map<T, Group<T>* >::const_iterator it = d_groups.begin(); it != d_groups.end(); ++it)
			{
			    cout << " '" << it->first << "' ";
			}
		cout << endl;
	}
};

#endif
