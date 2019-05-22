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
		int cnt = 0;
		int pl = 0;
		int pr = 0;
		int j = 0;
		while (com.at(j)->GetConnector()->GetSign() != '.') {
			while(ea.at(j)->getExe().at(0) == '(') {
				ea.at(j)->setExe();
				ea.at(j)->setLeftP(cnt);
				cnt++;
				pl++;
			}
			while(ea.at(j)->getExe().at(ea.at(j)->getExe().size() - 1) == ')') {
				ea.at(j)->setArgu();
				cnt--;
				ea.at(j)->setRightP(cnt);
				pr++;
			}
			if(ea.at(j)->getArgu()!=""){
				while(ea.at(j)->getArgu().at(ea.at(j)->getArgu().size() - 1) == ')') {
					ea.at(j)->setArgu();
					cnt--;
					ea.at(j)->setRightP(cnt);
					pr++;
				}
			}
			j++;
		}
		while(ea.at(j)->getExe().at(0) == '(') {
			ea.at(j)->setExe();
			ea.at(j)->setLeftP(cnt);
			cnt++;
			pl++;
		}
		while(ea.at(j)->getExe().at(ea.at(j)->getExe().size() - 1) == ')') {
			ea.at(j)->setArgu();
			cnt--;
			ea.at(j)->setRightP(cnt);
			pr++;
		}
		if(ea.at(j)->getArgu()!=""){
			while(ea.at(j)->getArgu().at(ea.at(j)->getArgu().size() - 1) == ')') {
				ea.at(j)->setArgu();
				cnt--;
				ea.at(j)->setRightP(cnt);
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
						break;
						//cout << "get here in while" << endl;
						//return 0;
					}
					else{
						next = com.at(i)->Operate();
						i++;
					}
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
					//cout << "get to the outside" << endl;
					//return 0;
				}
				else{
					next = com.at(i)->Operate();
					i++;
				}
			}
		}
	}
	exit(0);
	cout << " the end"<<endl;
	return 0;
}
