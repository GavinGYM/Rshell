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
		
		bool next = true;
		int i = 0;
		while (com.at(i)->GetConnector()->GetSign()!='.') {
			if (ea.at(i)->getExe() == "exit") {
				status = false;
				break;
			}
			next = com.at(i)->Operate();
			i++;
			if(next == false){
				i++;
			}
		}
		
		/*
		Run the execv, and continue when all work are done
		status = ???;
		*/
		
		//cout << con.at(0)->Operate(true);
		//cout << true;
	}
	return 0;
}
