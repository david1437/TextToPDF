#include <iostream>
#include <fstream>
#include "../inc/objects.h"
#include "../inc/xref.h"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

const int LINES_PER_PAGE = 65;

int main(int argc, char* argv[]) {

	if(argc != 2)
		return 1;

	string file_to_open = argv[1];

	int object_count = 1;
	string line;
	long line_counter = 0;
	ifstream inf(file_to_open);
	inf.unsetf(ios_base::skipws);
	long line_total = (count(istream_iterator<char>(inf), istream_iterator<char>(), '\n'));
	vector< vector < string > > lines(line_total);
	
	inf.clear();
	inf.seekg(0, ios::beg);

	if(inf.is_open()) {
		while(getline(inf, line)) {
			lines[line_counter / LINES_PER_PAGE].push_back(line);
			line_counter++;
		}
		inf.close();
	}
	else
		return 1;

	string whole_file("%PDF-1.7\n\n");
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

	ofstream of("bin/result.pdf");
	of << whole_file;

}

