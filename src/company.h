#ifndef COMPANY
#define COMPANY


#include <iostream>
#include <list>
#include <set>
#include <utility>
#include "board.h"
#include "group.h"
using namespace std;

template <class T> class Company : public Group<T> {
public:
	Company(const T& _label, const int& _age=0, const int& _size=0): Group(_label, _age, _size){};

	bool mergeRequest(){
		if(d_size > 10){
			return false;
		} else {
			return true;
		}
	};

	int getValue(){
		if (d_size <= 6){
			return d_size * 100;
		} else if (d_size <= 10){
			return 600;
		} else if (d_size <= 20){
			return 700;
		} else if (d_size <= 30){
			return 800;
		} else if (d_size <= 40){
			return 900;
		} else {
			return 1000;
		}
	}
	//Add the given tile to the group AND CHECKS MERGEREQUEST NOW
    bool add(const pair<char, int>& tile){
        
		//We do the parent add function which
		if(Group::add(tile) && mergeRequest()){
			return true;
		}
		return false;
    };
};

#endif
