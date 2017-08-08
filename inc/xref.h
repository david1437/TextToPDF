#ifndef XREF_H
#define XREF_H

#include <string>

using namespace std;

class xref {
	private:
		int count_of_objects;
		string objects_string;
	public:
		xref(int coo, string os) : count_of_objects(coo), objects_string(os) {};
		string getXrefObjectString();
		string getObjectString() { return objects_string; };
		int findByteLength(string s);
};

#endif
