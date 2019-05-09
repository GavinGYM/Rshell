
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
public:
	ExeArgu(string e, string a) : exe(e), argu(a) {}
	~ExeArgu() {
		delete &this->exe;
		delete &this->argu;
	}
	bool Operate();
	string getExe();
	string getArgu();
};

class Connector : public Rshellbase {
public:
	Connector() {}
	~Connector() {
	}
	bool Operate(bool result);
};

class Semicolon : public Connector {
public:
	Semicolon() {}
	~Semicolon() {
	}
	bool Operate(bool result);
};

class End : public Connector {
public:
	End() {}
	~End() {
	}
	bool Operate(bool result);
};

class Or : public Connector {
public:
	Or() {}
	~Or() {
	}
	bool Operate(bool result);
};

class And : public Connector {
public:
	And() {}
	~And() {
	}
	bool Operate(bool result);
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
};
