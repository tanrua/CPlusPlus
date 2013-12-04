#ifndef PLAYER
#define PLAYER

#include "company.h"
#include <utility>
#include <string>
#include <map>
#include <array>

using namespace std;

template <class T> class Player {
	string d_name;
	int d_money;
	map<T, int> d_shares;
public:
	//Default to a square board of 26 characters
	Player(const string& _name) : d_name(_name){
		d_money = 800;
	};

	void buy (const int& shares, Company<T> c ){
		T label = c.getLabel();
		if (d_shares.find(label) == d_shares.end()){
			d_shares.insert(make_pair(label, shares));
		} else {
			int shares2 =  shares + d_shares.at(label);
			//d_shares.erase(d_shares.find(c.getLabel()));
			d_shares.insert(make_pair(label, shares2));
		}
	}
	// Sell all shares of a company
	void sell(Company<T> _c ){
		T label = _c.getLabel();
		int cValue = _c.getValue();
		d_money = d_money + (d_shares.at(label) * cValue);
	};

	friend ostream& operator<<( ostream& _os, const Player<T>& _p) {
		_os << "Player '" << _p.d_name << "' has $" << _p.d_money << endl;
		map<T, int>::const_iterator it = _p.d_shares.begin();
		for (it; it !=_p.d_shares.end(); it++){
			_os << it->second << " shares in company:"<< it->first << endl;
		}
		return _os;
	};
};

#endif
