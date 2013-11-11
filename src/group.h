#ifndef GROUP
#define GROUP

#include <iostream>
#include <list>
#include <set>
#include <utility>

using namespace std;

template <class T> class Group {
	T d_label;
	int d_size;
	std::set<std::pair<char, int>> tiles;

	public:
		//Not sure WTF this is supposed to do...
		T getDummy(){
			return 0;
		}

		//add the given tile to the group
		void add(const char& col, const int& row){
			add(std::make_pair(col, row));
		}

		//Add the given tile to the group
		void add(std::pair<char, int>& tile){
			tiles.insert(tile) ;
			d_size++ ;
		}

		//Check is this group contains the given tile
		bool contains(const char& col, const int& row) {
			return contains(std::make_pair(col, row_)) ;
		}

		//Check is this group contains the given tile
		bool contains(std::pair<char, int>& tile) {
			return tiles.count(tile) ;
		}

		//return the size of this group
		int& size() {
			return d_size ;
		}

		//Return the label of this group
		T label() {
			return d_label ;
		}

		//Copy over the contents of the other group
		void addAll(const Group& other) {
			if (other.size() > 0) {
				//iterate through other and add to this
				for (std::set<pair<char, int>::iterator it=other.tiles.begin(); it!=other.tiles.end(); ++it){
					add(*it) ;
				}
			}
		}


};
#endif
