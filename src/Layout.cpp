#include "../inc/objects.h"
#include <string>

using namespace std;

string Layout::getObjectString() {
	object = name + '\n';
	object += "<<\n\t/Type /Pages\n\t/Mediabox [0 0 200 200]\n\t/Count " + to_string(count) + "\n\t/Kids [";
	for(int i = 0; i < count; i++) {
		if(i == 0)
			object +=  to_string(i+3) + " 0 R";
		else
			object += " " + to_string(i+3) + " 0 R";
	}
	object += "]\n>>\nendobj\n\n";
	return object;
}

int Layout::getCount() {
	return count;
}
