#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	string line;
	ifstream rf("data/test.txt");
	if(rf.is_open()) {
		while(getline(rf, line))
		{
			cout << line << '\n';
		}
		rf.close();
	}
	else {
		cout << "Error accured!" << '\n';
	}
}

