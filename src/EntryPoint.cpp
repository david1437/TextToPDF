#include "../inc/objects.h"
#include <string>

using namespace std;

string EntryPoint::getObjectString() {
	object = name + '\n';
	object += "<<\n\t/Type /Catalog\n\t/Pages 2 0 R\n>>\nendobj\n\n";
	return object;
}

