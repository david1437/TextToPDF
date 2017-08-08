#include "../inc/xref.h"
#include <string>

using namespace std;

string xref::getXrefObjectString() {
	string xref_string("xref\n0 " + to_string(count_of_objects) + "\n");
	for(int i = 0; i < count_of_objects; i++) {
		string to_find = to_string(i) + " 0 obj";
		int byte_length = findByteLength(to_find);
		int length = to_string(byte_length).length();
		if(i > 0) {
			for(int j = 0; j < 10-length; j++) {
			xref_string += "0";
			}
		}
		if(i == 0)
			xref_string += "0000000000 65535 f\n";
		else
			xref_string += to_string(byte_length) + " 00000 n\n";
	}
	xref_string += "trailer\n<<\n\t/Size " + to_string(count_of_objects) + "\n\t/Root 1 0 R\n>>\nstartxref\n";
	string temp(getObjectString() + xref_string);
	int xref_byte_offset = temp.find("xref", 0);
	xref_string += to_string(xref_byte_offset) + "\n%%EOF";
	return xref_string;
}

int xref::findByteLength(string s) {
	int count = (getObjectString()).find(s, 0);
	return count;
}
