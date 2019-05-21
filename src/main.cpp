#include "rshellbase.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	bool status = true;
	while (status) {
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
		int j = 0;
		while (com.at(j)->GetConnector()->GetSign() != '.') {
			if (ea.at(j)->getExe().at(0) == '(') {
				ea.at(j)->setExe();
				ea.at(j)->setLeftP(pl);
				pl++;
			}
			if(ea.at(j)->getArgu()!=""){
				if (ea.at(j)->getArgu().at(ea.at(j)->getArgu().size() - 1) == ')') {
					ea.at(j)->setArgu();
					ea.at(j)->setRightP(pl);
					pr++;
				}
			}
			j++;
		}
		if (ea.at(j)->getExe().at(0) == '(') {
			ea.at(j)->setExe();
			ea.at(j)->setLeftP(pl);
			pl++;
		}
		if(ea.at(j)->getArgu()!=""){
			if (ea.at(j)->getArgu().at(ea.at(j)->getArgu().size() - 1) == ')') {
				ea.at(j)->setArgu();
				ea.at(j)->setRightP(pl);
				pr++;
			}
		}

		bool parenStatus = true;
		if (pl != pr) {
			cout << "Your parentheses are wrong, please try to type again." << endl;
			parenStatus = false;
		}

		if (parenStatus) {
			//The execute part
			bool next = true;
			int i = 0;
			while (com.at(i)->GetConnector()->GetSign() != '.') {
				if(next){
					if (ea.at(i)->getExe() == "exit") {
						status = false;
						cout << "get here in while" << endl;
						return 0;
					}
					next = com.at(i)->Operate();
					i++;
				}
				else{
					if(com.at(i)->GetConnector()->GetSign() == '|' && com.at(i-1)->GetConnector()->GetSign() == '&'){
						next = true;	
					}
					if(com.at(i)->GetConnector()->GetSign() == '&' && com.at(i-1)->GetConnector()->GetSign() == '|'){
						next = true;	
					}
					i++;
				}
			}
			if(next){
				if (ea.at(i)->getExe() == "exit") {
					status = false;
					cout << "get here out while" << endl;
					return 0;
				}
				next = com.at(i)->Operate();
			}
		}
	}
	return 0;
}
