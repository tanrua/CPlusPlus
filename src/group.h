#ifndef GROUP
#define GROUP


#include <iostream>
#include <list>
#include <set>
#include <utility>
#include "board.h"
using namespace std;

template <class T> class Group {
protected:
        int d_size;
		T d_label;
		int d_age;
		static const int d_endGame = 12; //the size of the group that ends the game
        set< pair<char, int > > d_tiles;
public:
		Group(const T& _label, const int& _age=0, const int& _size=0): d_label(_label), d_age(_age), d_size(_size){};
		/** causes problems? why? set destructor problems?
		~Group(){
			d_tiles.~set();
		}**/
        //Not sure WTF this is supposed to do...
        T getDummy(){
			if (typeid(T) == typeid(int)) {
                return 666;
			} else if (typeid(T) == typeid(long)) {
                return 666;
			} else if (typeid(T) == typeid(unsigned char)) {
                return '+';
			} else if (typeid(T) == typeid(char)) {
				return '+';
			} else {
				return 666;
			}
        };

        //add the given tile to the group
		bool add(const unsigned char& col, const int& row){
                return add(make_pair(col, row));
        };

        //Add the given tile to the group
        bool add(const pair<char, int>& tile){
                d_tiles.insert(tile) ;
				if (d_label != getDummy()){
					d_size++ ;
				}
				if(d_size >= d_endGame){
					return true;
				}
				return false;
        };
		              
        //Copy over the contents of the other group
        bool addAll(Group<T>* other) {
			bool endGameSize = true;
			if (other->d_size > 0) {
                   //iterate through other and add to this
                   for (set<pair<char, int> >::iterator it=other->d_tiles.begin(); it!=other->d_tiles.end(); it++){
                           endGameSize = add(*it) ;
                   }
           }
			other->clear();
			return endGameSize;
        };

		//Change the labels of all the tiles in the group
		Board<T> setTiles(Board<T> b, T label) {
			for (set<pair<char, int> >::iterator it=d_tiles.begin(); it!=d_tiles.end(); it++){
				b.placeTile(it->first, it->second, label);
            }
			return b;
		}

        //Check if this group contains the given tile
        bool contains(const char& col, const int& row) {
                return contains(make_pair(col, row)) ;
        };

        //Check if this group contains the given tile
        bool contains(const pair<char, int>& tile) {
                return d_tiles.count(tile) ;
        };

		//remove the given tile from group
		void remove(const unsigned char& col, const int& row){
			remove(make_pair(col, row));
        };

        //remove the given tile from groupp
        void remove(const pair<char, int>& tile){
			if (contains(tile)){
				set<pair<char, int> >::iterator it = d_tiles.find(tile);
				d_tiles.erase(tile);
                d_size-- ;
			}
        };

		void clear(){
			d_size = 0;
			d_tiles.clear();
			d_age = 0;
		};

		/************************************ Getters and Setters *****************************************************/
		//return the size of this group
        int& getSize() {
                return d_size ;
        };

		//return what turn the group was created on
        int& getAge() {
			return d_age ;
        };

        //Return the label of this group
        T& getLabel() {
            return d_label ;
        };

		 //Return the label of this group
        set< pair<char, int > > getTiles() {
            return d_tiles ;
        };

		//return the size of this group
        void setSize(const int& _size) {
             d_size=_size;
        };

		//return what turn the group was created on
        void setAge(const int& _age) {
			d_age=_age;
        };

        //Return the label of this group
        void setLabel(const T& _label) {
            d_label=_label;
        };

		friend ostream& operator<<( ostream& _os, const Group<T>& _b) {
			_os << "Group '" << d_label << "' is of size: " << d_size << endl;
			return _os;
		};
		void print(){
			cout << "Group '" << d_label << "' is of size: " << d_size << endl;
		};

};

#endif
