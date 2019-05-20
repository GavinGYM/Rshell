
//#include "connector.h"
//#include "exeargu.h"
//#include "command.h"
#include <string>
#include <vector>
#include <climits>
using namespace std;

class ExeArgu;
class Connector;
class Command;

class Rshellbase {
private:
	string input;
public:
	Rshellbase(string s) : input(s) {}
	Rshellbase() {};
	~Rshellbase() {
		delete &this->input;
	}

	void Operate() {};

	bool Disintegrate(vector<ExeArgu*> &exeargu, vector<Connector*> &connector,vector<Command*> &command);
};


class ExeArgu : public Rshellbase {
private:
	string exe;
	string argu;
	int leftP = -1;
	int rightP = -1;
public:
	ExeArgu(string e, string a) : exe(e), argu(a) {}
	~ExeArgu() {
		delete &this->exe;
		delete &this->argu;
	}
	bool Operate();
	string getExe();
	string getArgu();
	int getLeftP();
	int getRightP();
	void setLeftP();
	void setRightP();
};

class Connector : public Rshellbase {
private:
	char sign;
public:
	Connector() {}
	Connector(char c) : sign(c) {}
	~Connector() {
	}
	bool Operate(bool result);
	char GetSign();
};

class Command : public Rshellbase {
private:
	ExeArgu *exeArgu;
	Connector *connector;
public:
	Command(ExeArgu *e, Connector *c) : exeArgu(e), connector(c) {}
	~Command() {
		delete &this->exeArgu;
		delete &this->connector;
	}
	bool Operate();
	Connector * GetConnector(){
		return this->connector;
	}
};
