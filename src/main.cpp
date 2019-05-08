#include "rshellbase.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	bool status=true;
	while(status){
		vector<Connector*> con;
		vector<Command*> com;
		vector<ExeArgu*> ea;
		string input;
		cout << "$ ";
		getline(cin, input);
		Rshellbase *base = new Rshellbase(input);
		base->Disintegrate(ea, con, com);
		/*
		Run the execv, and continue when all work are done
		status = ???;
		*/
	}
	return 0;
}
