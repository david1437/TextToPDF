#include "../inc/objects.h"
#include <string>

string Font::getObjectString() {
	object = name + '\n';
	object += "<<\n\t/Type /Font\n\t/Subtype /Type1\n\t/BaseFont /" + font_name + "\n>>\nendobj\n\n";
	return object;
}
