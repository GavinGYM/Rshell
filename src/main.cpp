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
		
		//The precedence part
		int pl = 0;
		int pr = 0;
		int i = 0;
		while (com.at(i)->GetConnector()->GetSign()!='.') {
			if (ea.at(i)->getExe().at(0) == '(') {
				ea.at(i)->setExe();
				ea.at(i)->setLeftP(pl);
				pl++;
			}
			if (ea.at(i)->getArgu().at(ea.at(i)->getArgu().size()-1) == ')') {
				ea.at(i)->setArgu();
				ea.at(i)->setRightP(pl);
				pr++;
			}
			i++;
		}
		if (ea.at(i)->getExe().at(0) == '(') {
			ea.at(i)->setExe();
			ea.at(i)->setLeftP(pl);
			pl++;
		}
		if (ea.at(i)->getArgu().at(ea.at(i)->getArgu().size()-1) == ')') {
			ea.at(i)->setArgu();
			ea.at(i)->setRightP(pl);
			pr++;
		}
		
		bool parenStatus = true;
		if(pl!=pr){
			cout << "Your parentheses are wrong, please try to type again.";
			parenStatus = false;
		}
		
		if(parenStatus){
			//The execute part
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
			if (ea.at(i)->getExe() == "exit") {
				status = false;
				break;
			}
			next = com.at(i)->Operate();
			i++;
			if(next == false){
				i++;
			}
			/*
			Run the execv, and continue when all work are done
			status = ???;
			*/

			//cout << con.at(0)->Operate(true);
			//cout << true;
		}
	}
	return 0;
}
