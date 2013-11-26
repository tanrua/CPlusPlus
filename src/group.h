#ifndef GROUP
#define GROUP

#include <iostream>
#include <list>
#include <set>
#include <utility>

using namespace std;

template <class T> class Group {
        int d_size;
		T d_label;
		int d_age;
        set< pair<char, int > > d_tiles;
public:
		Group(T _label, int _age=0, int _size=0): d_label(_label), d_age(_age), d_size(_size){};

        //Not sure WTF this is supposed to do...
        T getDummy(){
			if (typeid(T) == typeid(int)) {
                return 0;
			} else if (typeid(T) == typeid(long)) {
                return 0;
			} else if (typeid(T) == typeid(unsigned char)) {
                return '+';
			} else if (typeid(T) == typeid(char)) {
				return '+';
			} else {
				return 0;
			}
        }

        //add the given tile to the group
		void add(const unsigned char& col, const int& row){
                add(make_pair(col, row));
        }

        //Add the given tile to the group
        void add(const pair<char, int>& tile){
                d_tiles.insert(tile) ;
                d_size++ ;
        }
		              
        //Copy over the contents of the other group
        void addAll(const Group<T>& other) {
			if (other.d_size > 0) {
                   //iterate through other and add to this
                   for (set<pair<char, int> >::iterator it=other.d_tiles.begin(); it!=other.d_tiles.end(); it++){
                           add(*it) ;
                   }
           }
        }

        //Check if this group contains the given tile
        bool contains(const char& col, const int& row) {
                return contains(make_pair(col, row)) ;
        }

        //Check if this group contains the given tile
        bool contains(const pair<char, int>& tile) {
                return d_tiles.count(tile) ;
        }

		//remove the given tile from group
		void remove(const unsigned char& col, const int& row){
			remove(make_pair(col, row));
        }

        //remove the given tile from groupp
        void remove(const pair<char, int>& tile){
			if (contains(tile)){
				set<pair<char, int> >::iterator it = d_tiles.find(tile);
				d_tiles.erase(tile);
                d_size-- ;
			}
        }

		/************************************ Getters and Setters *****************************************************/
		//return the size of this group
        int& getSize() {
                return d_size ;
        }

		//return what turn the group was created on
        int& getAge() {
			return d_age ;
        }

        //Return the label of this group
        T& getLabel() {
                return d_label ;
        }

		//return the size of this group
        void setSize(const int& _size) {
                d_size=_size;
        }

		//return what turn the group was created on
        void setAge(const int& _age) {
			d_age=_age;
        }

        //Return the label of this group
        void setLabel(const T& _label) {
                d_label=_label;
        }

		void print(){
			cout << "Group '" << d_label << "' is of size: " << d_size << endl;
		}

};

class Position {
	unsigned char d_x;
	int d_y;
public:
	Position(unsigned char _x = 'a', int _y = 0): d_x(_x), d_y(_y){};
	unsigned char getX(){ return d_x;};
	int getY() { return d_y;};
};

#endif
