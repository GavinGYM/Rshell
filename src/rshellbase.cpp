#include "rshellbase.hpp"

bool Rshellbase::Disintegrate(vector<ExeArgu*>& exeargu, vector<Connector*>& connector, vector<Command*>& command)
{
	string subinput;
	subinput = this->input;
	while (subinput.find("&&") != string::npos || subinput.find("||") != string::npos ||
		subinput.find(";") != string::npos) {
		int pos = INT_MAX;
		char con;
		string cmd;
		if (subinput.find("&&") != string::npos) {
			pos = subinput.find("&&");
			con = '&';
		}
		if (subinput.find("||") != string::npos && subinput.find("||") < pos) {
			pos = subinput.find("||");
			con = '|';
		}
		if (subinput.find(";") != string::npos && subinput.find(";") < pos) {
			pos = subinput.find(";");
			con = ';';
		}
		
		//This if for the case we have a quotation mark.
		if (subinput.find('"') != string::npos && subinput.find('"') < pos) {
			int quotationEnd = subinput.find('"', subinput.find('"') + 1);
			pos = INT_MAX;
			if (subinput.find("&&", quotationEnd + 1) != string::npos) {
				pos = subinput.find("&&");
				con = '&';
			}
			if (subinput.find("||", quotationEnd + 1) != string::npos && subinput.find("||") < pos) {
				pos = subinput.find("||");
				con = '|';
			}
			if (subinput.find(";", quotationEnd + 1) != string::npos && subinput.find(";") < pos) {
				pos = subinput.find(";");
				con = ';';
			}
			if (pos == INT_MAX) {
				break;
			}
		}

		if (con == '&') {
			cmd = subinput.substr(0, pos - 1);
			subinput = subinput.substr(pos + 3, subinput.size() - pos - 1);
		}
		else if (con == '|') {
			cmd = subinput.substr(0, pos - 1);
			subinput = subinput.substr(pos + 3, subinput.size() - pos - 1);
		}
		else if (con == ';') {
			cmd = subinput.substr(0, pos);
			subinput = subinput.substr(pos + 2, subinput.size() - pos - 1);
		}
		string argu = cmd.substr(cmd.find(" ") + 1, cmd.size() - 1);
		
		//This is for the case we have a comment
		if (argu.find("#") != string::npos) {
			argu = argu.substr(0, argu.find("#"));
		}

		ExeArgu *newea = new ExeArgu(cmd.substr(0, cmd.find(" ")), argu);
		exeargu.push_back(newea);
		//exeargu[i]->exe = cmd.substr(0,cmd.find(" "));
		//exeargu[i]->argu = cmd.substr(cmd.find(" ")+1,cmd.size()-1);

		Connector *newcon;
		if (con == '&') {
			newcon = new And();
		}
		else if (con == '|') {
			newcon = new Or();
		}
		else if (con == ';') {
			newcon = new Semicolon();
		}
		connector.push_back(newcon);

		Command *newcom = new Command(newea, newcon);
		command.push_back(newcom);
		//command[i]->exeArgu = exeargu[i];
		//command[i]->connector = connector[i];

		//i++;
	}
	//this is for the last command which don't have a connector following it
	string cmd;
	cmd = subinput;
	string argu = cmd.substr(cmd.find(" ") + 1, cmd.size() - 1);
	if (argu.find("#") != string::npos) {
		argu = argu.substr(0, argu.find("#"));
	}
	ExeArgu *newea = new ExeArgu(cmd.substr(0, cmd.find(" ")), argu);
	exeargu.push_back(newea);
	Connector *newcon = new End();
	connector.push_back(newcon);

	Command *newcom = new Command(newea, newcon);
	command.push_back(newcom);

	//exeargu[i]->exe = cmd.substr(0, cmd.find(" "));
	//exeargu[i]->argu = cmd.substr(cmd.find(" ") + 1, cmd.size()-1);
	//command[i]->exeArgu = exeargu[i];
	/*
	The input string looks like this:

	$ executable [argumentList] [connector]

	This function is used to disintegrate the input string.
	It passes the "executable" and "[argumentList]" part
	to the ExeArgu[](which is an array of objects),
	and passes the "[connector]" part to the Connector[]
	(which is also an array of objects).
	These two arrays will be paired by using their subscripts.
	*/
	return true;
}
