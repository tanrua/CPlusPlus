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

	playAt(char x,int y){
		//get the adjacent tiles
		vector<T> adjacents = d_b.getAdjacent(x, y);
		//
		d_b.placeTile(x, y, T);
	};
};
#endif
