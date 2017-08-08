#include "../inc/objects.h"
#include <string>

using namespace std;

string PageContent::getObjectString() {
	object = name + '\n';
	object += "<<\n\t/length ";
	string stream(">>\nstream\nBT\n0 12 TD\n/F1 12 Tf\n");
	for(auto v_iter = lines.rbegin(); v_iter != lines.rend(); ++v_iter) {
		if(v_iter == lines.rbegin())
			stream += "(" + *v_iter + ") Tj\n";
		else
			stream += "(" + *v_iter + ") '\n";
	}
	stream += "ET\n";
	length = stream.length() - 7; //7 is too get rid of length of stream\n
	stream += "endstream\nendobj\n\n";
	object += to_string(length) + "\n" + stream;
	return object;
}
