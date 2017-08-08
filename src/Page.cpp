#include "../inc/objects.h"
#include <string>

string Page::getObjectString() {
	object = name + '\n';
	object += "<<\n\t/Type /Page\n\t/Parent " + parent_object_name.substr(0,parent_object_name.find(" ")) + " 0 R" + "\n\t/Resources <<\n\t\t/Font <<\n\t\t\t/F1 " + font_object_name.substr(0,font_object_name.find(" ")) + " 0 R" + "\n\t\t>>\n\t>>\n\t/Contents " + page_content_object_name.substr(0,page_content_object_name.find(" ")) + " 0 R" + "\n>>\nendobj\n\n";
	return object;
}

