#ifndef BOARDGAME
#define BOARDGAME

#include "board.h"
#include "group.h"
#include "player.h"

#include <iostream>
#include <list>
#include <algorithm> 
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <time.h>

using namespace std;

template <class T> class BoardGame {
	int d_rows;
	int d_cols;
	int d_turn;
	bool d_endGame;
	T d_dum;
	Board <T> d_b;
	map <T, Group<T>* > d_groups;
	set<Position> d_usedTiles;
	//new valid groups will ALWAYS be increasing. even when they are unused.
	vector<T> d_validGroups;
	stack<Position> d_positions;
// WAT	Player<T>[] d_players;
	void groupInitialization(){
		Group<T> tmp(0,0,0);
		//There must be a better way to define Group::d_dummy exterally?
		d_dum = tmp.getDummy();

		d_groups.clear();
		d_validGroups.clear();

		d_groups.insert(make_pair(d_dum, new Group<T>(d_dum, 99999, 0)));
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
		d_endGame = false;
		groupInitialization();
		generatePositions();
	};

	~BoardGame(){
		d_b.~Board();
		d_groups.~map();
		d_usedTiles.~set();
		d_validGroups.~vector();
	}

	Group<T> getGroup(T label){
		return d_groups.at(label);
	}

	void playAt(Position& pos){
		//is it a valid play
		//if (validPlay(pos)) {
			//get the adjacent tiles
			vector<pair<T,char> > adjacents = d_b.getAdjacent(pos.getX(), pos.getY());
			bool gameInPlay = false;
			//NONE? This is an independent
			if(adjacents.size() == 0){
				//add tile to dummy group
				d_groups[d_dum]->add(pos.getX(), pos.getY());
				// place tile
				d_b.placeTile(pos.getX(), pos.getY(), d_dum);
				//d_usedTiles.insert(pos);
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
						//d_usedTiles.insert(pos);
						//add adjacent tile to new group *THE HARD PART*
						Position adjPos = getAdjPosition(pos, adjLabel.second);
						d_b.placeTile(adjPos.getX(), adjPos.getY(), groupLabel);
						d_groups.at(d_dum)->remove(adjPos.getX(), adjPos.getY());

						//add both tiles to this group
						gameInPlay = d_groups.at(groupLabel)->add(pos.getX(), pos.getY());
						gameInPlay = d_groups.at(groupLabel)->add(adjPos.getX(), adjPos.getY());
					} else {
						cout << "Error: No valid groups left to choose from" << endl;
					}
				} else { //YES
					// assign tile to group
					gameInPlay = d_groups.at(adjLabel.first)->add(pos.getX(), pos.getY());
					// place tile
					d_b.placeTile(pos.getX(), pos.getY(), adjLabel.first);
					//d_usedTiles.insert(pos);
				}
			
			}  else {
				//A SORTED GROUP OF THE ADJACENT GROUPS. NEEDED TO REPLACE TILES
				vector <Group<T>* > adjGroups = getAdjGroups(adjacents);
				//is there more than one group in the adj. list?
				if (adjGroups.size() == 1){
					//in the middle of some dummy tiles... a complex case
					if (adjGroups[0]->getLabel() == d_dum){
						if ( canAddNewGroup() ) {
							//Get our new group
							T groupLabel = addNewGroup();
							//for all the adjacent tiles, remove them from the dummy group and 
							Position adjTile = pos;
							for (int i=0; i<adjacents.size(); i++){
								//get position of adjacent tile;
								adjTile = getAdjPosition(pos, adjacents[i].second);
								//remove from dummy group
								d_groups.at(d_dum)->remove(adjTile.getX(), adjTile.getY());
								//add to new group
								 d_b.placeTile(adjTile.getX(), adjTile.getY(), groupLabel);
								 gameInPlay = d_groups.at(groupLabel)->add(adjTile.getX(), adjTile.getY());
							}
							// place tile
							d_b.placeTile(pos.getX(), pos.getY(), groupLabel);
							//d_usedTiles.insert(pos);
							gameInPlay = d_groups.at(groupLabel)->add(pos.getX(), pos.getY());
						}
					} else {
						// assign tile to group
						adjGroups[0]->add(pos.getX(), pos.getY());
						// place tile
						d_b.placeTile(pos.getX(), pos.getY(), adjGroups[0]->getLabel());
						//d_usedTiles.insert(pos);
					}

				
				} else {
					//merge the following sorted groups
					for (int i=1; i<adjGroups.size(); i++){
						if (adjGroups[i]->getLabel() == d_dum){
							cout << "AUUUUGH" << endl;

							Position adjTile = pos;
							for (int i=0; i<adjacents.size(); i++){
								//get position of adjacent tile;
								adjTile = getAdjPosition(pos, adjacents[i].second);
								if(d_b.getTileAt(adjTile.getX(), adjTile.getY()) == d_dum){
									//remove from dummy group
									d_groups.at(d_dum)->remove(adjTile.getX(), adjTile.getY());
									//add to new group
									d_b.placeTile(adjTile.getX(), adjTile.getY(), adjGroups[0]->getLabel());
									gameInPlay = adjGroups[0]->add(adjTile.getX(), adjTile.getY());
								}
							}
						} else {
							//setTiles
							d_b = adjGroups[i]->setTiles(d_b, adjGroups[0]->getLabel());
							//largest is always first
							gameInPlay = adjGroups[0]->addAll(adjGroups[i]);
					
							d_groups.erase(adjGroups[i]->getLabel());
						}
					}
					d_b.placeTile(pos.getX(), pos.getY(), adjGroups[0]->getLabel());
				}
			}
		
			//a turn has taken place
			d_turn++;
			if (gameInPlay){
				d_endGame = true;
			}
		//}
	};

	bool validPlay(Position& pos){
		set<Position>::iterator it = d_usedTiles.find(pos);
		if(it != d_usedTiles.end()){
			//tile already played
			cout << "--TILE HAS BEEN PLAYED--" << endl;
			return false;
		} else {
			return true;
		}
	};



	bool canAddNewGroup() {
		//can only do this if there are still valid groups left to add
		if (d_validGroups.size() == 0){
			return false;
		} else {
			return true;
		}
	};

	bool gameOver(){
		return d_endGame;
	};

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
			if( find(tmpGrps.begin(), tmpGrps.end(), d_groups.at( adj[i].first )) == tmpGrps.end()) {
				tmpGrps.push_back(d_groups.at( adj[i].first ));
				current = d_groups.at( adj[i].first )->getSize();
				// biggest group wins and the dummy group can never really be the "biggest group"
				if (adj[i].first != d_dum){
					if( current > max){
						maxElem = i;
						max = current;
					} else if ( current == max) {
						int age_i = d_groups.at( adj[i].first )->getAge();
						int age_max = d_groups.at( adj[maxElem].first )->getAge();
						// in case of tie, oldest (lowest turn) wins
						// only swap if the ith element is younger than the max element
						if (age_i < age_max){
							maxElem = i;
						}
					}
				}
			} 
		}

		//due to the lack of a working sort, we just place the largest group first, it will absorb all other groups.
		vector<Group<T>* > adjGroups;
		Group<T>* maxGrp = tmpGrps[maxElem];

		adjGroups.push_back(maxGrp);
		for(int i=0; i < tmpGrps.size(); i++){
			//Don't add the max group twice.
			if(i != maxElem){
				adjGroups.push_back(tmpGrps[i]);
			}
		}

		return adjGroups;
	};

	bool goodPos(const unsigned char& x, const int& y){
		return d_b.goodPos(x, y);
	};

	bool outOfMoves(){
		return d_positions.empty();
	}

	//KILL ME!! KILL ME!!! I BREAK THE GAME AND AM ONLY FOR TESTING?!
	Position popValidMove(){
		Position p = Position('a',0);

		if(!outOfMoves()){
			p = d_positions.top();
			d_positions.pop();
		} 

		return p;
	}
	void clearBoard(){
		d_b.clear();
		groupInitialization();
		generatePositions();
	};

	/**************************************************** ADVANCED  GAMEPLAY ***********************************************************/
	void generatePositions(){
		vector<Position> pos;
		for(unsigned char c = 'a'; c < ('a'+d_cols); c++){
			for(int r = 0; r < d_rows; r++){
				pos.push_back(Position(c, r));
			}
		}
		srand(time(NULL));
		random_shuffle(pos.begin(), pos.end());
		for each(Position pn in pos){
			d_positions.push(pn);
		}
	};


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

	
	friend ostream& operator<<( ostream& _os, const BoardGame<T>& _b){
		for(map<T, Group<T>* >::const_iterator it = _b.d_groups.begin(); it != _b.d_groups.end(); ++it)
			{
			   _os << it->second->getLabel() << ":" << it->second->getSize() << endl;
			}
		_os << endl << "------------BOARD Turn: " << _b.d_turn << "------------" << endl;
		_os << _b.d_b << "-------------------------------------" << endl;
		return _os;
	};
};

#endif
