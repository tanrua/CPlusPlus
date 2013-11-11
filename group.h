#ifndef GROUP
#define GROUP

#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <class T> class Group {
	T d_label;
	int d_size;
public:
	T getDummy(){
		return 0;
	}
};
#endif
