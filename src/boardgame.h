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
	BoardGame(const int& rows=0, const int& cols=0): d_rows(rows), d_cols(cols), d_turn(0) {
		//add empty dummy group
		d_b = Board<T>(d_rows, d_cols);
		Group<T> tmp(0,0,0);
		d_dum = tmp.getDummy();

		d_groups.insert(make_pair(d_dum, new Group<T>(d_dum, 0, 0)));

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
			//Group<T>* grp = d_groups[d_dum];
			d_groups[d_dum]->add(pos.getX(), pos.getY());
			// place tile
			d_b.placeTile(pos.getX(), pos.getY(), d_dum);
		} else if(adjacents.size() == 1) {
		//ONE: creating or increasing size
			//is adj part of the dummy group
			if(adjacents[0] == d_dum){
				//Create a new group if possible
				if ( canAddNewGroup() ) {
					//Remove tile from dummy group 
					//Group<T>* dummy = d_groups.at(d_dum);
					d_groups.at(d_dum)->remove(pos.getX(), pos.getY());
					// place tile
					d_b.placeTile(pos.getX(), pos.getY(), addNewGroup());
					//add adjacent tile to new group
				} else {
					cout << "Error: No valid groups left to choose from" << endl;
				}
			} else { //YES
				// assign tile to group
				d_groups.at(adjacents[0])->add(pos.getX(), pos.getY());
				// place tile
				d_b.placeTile(pos.getX(), pos.getY(), adjacents[0]);
			}
			
		} /** else {
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
			d_b.placeTile(pos.getX(), pos.getY(), adjacents[0]);
		}
		**/
		//a turn has taken place
		d_turn++;
	};


	bool canAddNewGroup() {
		//can only do this if there are still valid groups left to add
		if (d_validGroups.size() == 0){
			return false;
		} else {
			return true;
		}
	}

	T addNewGroup(){
			//take the first element label.
			T currentLabel = d_validGroups.at(0);

			//make a new group of size 0 at this turn and add it to the map of groups
			d_groups.insert(make_pair(currentLabel, new Group<T>(currentLabel, d_turn, 0)));

			//then remove the first element of valid groups so we don't use it again.
			d_validGroups.erase(d_validGroups.begin());

			return currentLabel;
	};

	bool removeUnusedGroup(T label) {
		if (d_groups.find(label) == d_groups.end()){
			return false;
		} else {
			d_groups.erase(label);
			d_validGroups.push_back(label);
			return true;
		}
	};

	void printValids(){
		cout << "Valid groups left to choose from are: ";
		for (int i=0; i<d_validGroups.size(); i++){
			cout << " '" << d_validGroups.at(i) << "' ";
		}
		cout << endl;
	};

	void printGroups(){
		cout << "Groups in play are: ";
		for(map<T, Group<T>* >::const_iterator it = d_groups.begin(); it != d_groups.end(); ++it)
			{
			    cout << " '" << it->first << "' ";
			}
		cout << endl;
	};

	friend ostream& operator<<( ostream& _os, const BoardGame& _b){
		_os << "------------BOARD Turn: " << _b.d_turn << "------------" << endl;
		_os << _b.d_b << "-------------------------------------" << endl;
		return _os;
	};
};

#endif
