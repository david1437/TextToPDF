#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <vector>

using namespace std;

class Object { //base class for objects
	protected:
		string name;
		string object;
	public:
		Object(string& n) : name(n) {};
		string& getName() { return name; };
		string getObjectName() { return object; };
		virtual string getObjectString() = 0;
};

class Font : public Object {
	private:
		string font_name; //font name if we need a different font
	public:
		Font(string& n, string& fn) : Object(n), font_name(fn) {};
		Font(string& n) : Object(n), font_name("Times-Roman") {};
		virtual string getObjectString();
};

class PageContent : public Object {
	private:
		int length; //length in bytes of the stream
		vector<string> lines;
	public:
		PageContent(string& n, vector<string>& vs) : Object(n), lines(vs) {};
		virtual string getObjectString();
};

class EntryPoint : public Object {
	public:
		EntryPoint(string& n) : Object(n) {};
		virtual string getObjectString();
};

class Layout : public Object {
	private:
		int count; //number of pages
	public:
		Layout(string& n, int c) : Object(n), count(c) {};
		int getCount();
		virtual string getObjectString();
};

class Page : public Object {
	private:
		string parent_object_name;
		string font_object_name;
		string page_content_object_name;
	public:
		Page(string& n, string& pon, string& fon, string& pcon) : Object(n), parent_object_name(pon), font_object_name(fon), page_content_object_name(pcon) {};
		virtual string getObjectString();
};

#endif
