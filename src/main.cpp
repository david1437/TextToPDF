#include <iostream>
#include <fstream>
#include "../inc/objects.h"
#include "../inc/xref.h"
#include <vector>
#include <algorithm> //for count
#include <iterator> //for istream iterators

using namespace std;

const int LINES_PER_PAGE = 65;

int main(int argc, char* argv[]) {

	if(argc != 2) { //makes sure they enter a path
		cout << "Proper format is \"TextToPDF [path of file to convert]\"" << endl;
		return 1;
	}

	string file_to_open = argv[1];

	int object_count = 1; //keeps track of obj count for xref
	string line; //holds the lines from the txt file
	long line_counter = 0; //counts lines as the file is reado

	ifstream inf;

	try {
		inf.open(file_to_open); //opens files
	}
	catch (ifstream::failure e){
		cerr << "Exception opeining file at dir path " << file_to_open << endl;
		return 1;
	}

	inf.unsetf(ios_base::skipws); //allows new line characters to be read
	long line_total = (count(istream_iterator<char>(inf), istream_iterator<char>(), '\n')); //counts all lines all at once
	vector< vector < string > > lines(line_total);
	
	inf.clear();
	inf.seekg(0, ios::beg);

	if(inf.is_open()) { //loops through file adding all the lines to the lines vector
		while(getline(inf, line)) {
			lines[line_counter / LINES_PER_PAGE].push_back(line);
			line_counter++;
		}
		inf.close();
	}
	else {
		cerr << "FIle not opened make sure path is correct!" << endl;
		return 1;
	}

	string whole_file("%PDF-1.7\n\n"); //creates PDF objects
	string n("1 0 obj");
	EntryPoint ep(n);
	object_count++;
	n = "2 0 obj";
	long page_count = (line_counter / LINES_PER_PAGE) + 1;
	Layout lo(n, page_count);
	object_count++;
	n = to_string(3+page_count) + " 0 obj";
	Font fo(n);
	object_count++;
	vector<PageContent> pconlist;
	for(int i = 0; i < page_count; i++) {
		string new_name(to_string(i+page_count+4) + " 0 obj");
		vector<string> vs = lines[i];
		PageContent pc(new_name, vs);
		pconlist.push_back(pc);
		object_count++;
	}

	vector<Page> pages;
	for(int i = 0; i < page_count; i++) {
		string new_name(to_string(i+3) + " 0 obj");
		Page pg(new_name, lo.getName(), fo.getName(), pconlist[i].getName());
		pages.push_back(pg);
		object_count++;
	}

	whole_file += (ep.getObjectString() + lo.getObjectString());
	for(auto v_iter = pages.begin(); v_iter != pages.end(); ++v_iter) {
		whole_file += (v_iter->getObjectString());
	}
	whole_file += fo.getObjectString();
	for(auto v_iter = pconlist.begin(); v_iter != pconlist.end(); ++v_iter) {
		whole_file += (v_iter->getObjectString());
	}

	xref x(object_count, whole_file);
	whole_file += x.getXrefObjectString();

	ofstream of("bin/result.pdf"); //writes pdf structure to the output file
	of << whole_file;

	cout << "FIle written to bin/result.pdf succesfully!" << endl;

}

