#ifndef BOARDGAME
#define BOARDGAME

#include "board.h"
#include "group.h"
#include <iostream>
#include <list>
#include <map>
#include <vector>

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

	void groupInitialization(){
		Group<T> tmp(0,0,0);
		//There must be a better way to define Group::d_dummy exterally?
		d_dum = tmp.getDummy();

		d_groups.clear();
		d_validGroups.clear();

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
	}

public:
	BoardGame(const int& rows=0, const int& cols=0): d_rows(rows), d_cols(cols), d_turn(0) {
		//add empty dummy group
		d_b = Board<T>(d_rows, d_cols);		
		groupInitialization();
	};

	void playAt(Position& pos){
		//is it a valid play
		//TODO

		//get the adjacent tiles
		vector<pair<T,char> > adjacents = d_b.getAdjacent(pos.getX(), pos.getY());
		//NONE? This is an independent
		if(adjacents.size() == 0){
			//add tile to dummy group
			//Group<T>* grp = d_groups[d_dum];
			d_groups[d_dum]->add(pos.getX(), pos.getY());
			// place tile
			d_b.placeTile(pos.getX(), pos.getY(), d_dum);
		} else if(adjacents.size() == 1) {
			//is adj part of the dummy group
			//the element adjacent
			pair<T,char> adjLabel = adjacents[0];

			if(adjLabel.first == d_dum){
				//Create a new group if possible
				if ( canAddNewGroup() ) {
					//Get our new group
					T groupLabel = addNewGroup();
					//Remove tile from dummy group 
					d_groups.at(d_dum)->remove(pos.getX(), pos.getY());
					// place tile
					d_b.placeTile(pos.getX(), pos.getY(), groupLabel);
					//add adjacent tile to new group *THE HARD PART*
					Position adjPos = getAdjPosition(pos, adjLabel.second);
					d_b.placeTile(adjPos.getX(), adjPos.getY(), groupLabel);
					d_groups.at(d_dum)->remove(adjPos.getX(), adjPos.getY());

					//add both tiles to this group
					d_groups.at(groupLabel)->add(pos.getX(), pos.getY());
					d_groups.at(groupLabel)->add(adjPos.getX(), adjPos.getY());
				} else {
					cout << "Error: No valid groups left to choose from" << endl;
				}
			} else { //YES
				// assign tile to group
				d_groups.at(adjLabel.first)->add(pos.getX(), pos.getY());
				// place tile
				d_b.placeTile(pos.getX(), pos.getY(), adjLabel.first);
			}
			
		}  else {
			//A SORTED GROUP OF THE ADJACENT GROUPS. NEEDED TO REPLACE TILES
			vector <Group<T>* > adjGroups = getAdjGroups(adjacents);
			//is there more than one group in the adj. list?
			if (adjGroups.size() == 1){
				// assign tile to group
				adjGroups[0]->add(pos.getX(), pos.getY());

				// place tile
				d_b.placeTile(pos.getX(), pos.getY(), adjGroups[0]->getLabel());
			} else {
				//merge the following sorted groups
				for (int i=1; i<adjGroups.size(); i++){
					//setTiles
					d_b = adjGroups[i]->setTiles(d_b, adjGroups[0]->getLabel());
					//largest is always first
					adjGroups[0]->addAll(adjGroups[i]);
					
					d_groups.erase(adjGroups[i]->getLabel());
				}
				cout << "good" << endl;
				d_b.placeTile(pos.getX(), pos.getY(), adjGroups[0]->getLabel());
			}
		}
		
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

	//In the case where we remove some element from the dummy group and make a new real group.
	Position getAdjPosition(Position pos, char orientation){
		if (orientation == 'u'){
			return Position(pos.getX(), (pos.getY()-1));
		} else if (orientation == 'd'){
			return Position(pos.getX(), (pos.getY()+1));
		} else if (orientation == 'l'){
			return Position((pos.getX()-1), pos.getY());
		} else if (orientation == 'r'){
			return Position((pos.getX()+1), pos.getY());
		}
	};

	//Give us a sorted list of unique groups adjacent to the tile in play
	vector<Group<T>* > getAdjGroups(const vector<pair<T,char> >& adj){
		vector<Group<T>* > tmpGrps;
		int current = 0;
		int max = 0;
		int maxElem = 0;
		for(int i=0; i<adj.size(); i++){
			//check for uniqueness
			if(find(tmpGrps.begin(), tmpGrps.end(), d_groups.at( adj[i].first )) == tmpGrps.end()) {
				tmpGrps.push_back(d_groups.at( adj[i].first ));
				current = d_groups.at( adj[i].first )->getSize();
				if( current > max){
					maxElem = i;
					max = current;
				}
			} 
		}

		//due to the lack of a working sort, we just place the largest group first, it will absorb all other groups.
		vector<Group<T>* > adjGroups;
		Group<T>* maxGrp = tmpGrps[maxElem];

		adjGroups.push_back(maxGrp);
		for(int i=0; i<tmpGrps.size(); i++){
			//Don't add the max group twice.
			if(i != maxElem){
				adjGroups.push_back(tmpGrps[i]);
			}
		}

		return adjGroups;
	}

	void clearBoard(){
		d_b.clear();
		groupInitialization();
	}

	/**************************************************** PRINTING FUNCTIONS ***********************************************************/
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
