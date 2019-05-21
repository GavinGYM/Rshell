#include "rshellbase.hpp"
#include <sys/wait.h>
#include<sys/types.h>
#include<cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

bool ExeArgu::Operate()
{
	pid_t pid,pr;
	pid = fork();
	bool status = false;

	if (pid < 0) {
		perror("fork creates child process error!");
		exit(0);
	}
	else if (pid == 0) {
		if(this->argu == ""){
			char *argv[] = { const_cast<char*>(this->exe.c_str()),NULL };
			char* path = const_cast<char*>(this->exe.c_str());
			int a = execvp(path, argv);
			if (a == -1) {
				perror("execution fails!");
				exit(1);				
			}
			else {
				status = true;
				exit(0);
			}	
		}
		else{
			char *argv[] = { const_cast<char*>(this->exe.c_str()), const_cast<char*>(this->argu.c_str()),NULL };
			char* path = const_cast<char*>(this->exe.c_str());
			int a = execvp(path, argv);
			if (a == -1) {
				perror("execution fails!");
				exit(1);	
			}
			else {
				status = true;
				exit(0);
			}
		}
	}
	else {
		pr = waitpid(pid, NULL, 0);
		if(pr == pid){
			if(status == true){	
				cout << "get here and return true" << endl;
				cout << WEXITSTATUS(status);
				return true;
			}
			else{
				cout << "get here and return true" << endl;
				return true;
			}
		}
		else{
			cout << "someerror occured" << endl;
			return false;
		}
	}
}

string ExeArgu::getExe()
{
	return this->exe;
}

string ExeArgu::getArgu()
{
	return this->argu;
}

int ExeArgu::getLeftP()
{
	return this->leftP;
}

int ExeArgu::getRightP()
{
	return this->rightP;
}

void ExeArgu::setLeftP(int i)
{
	this->leftP = i;
}

void ExeArgu::setRightP(int i)
{
	this->rightP = i;
}

void ExeArgu::setExe()
{
	if(exe.at(0) == '('){
		exe = exe.substr(1 , exe.size()-1);
	}
}

void ExeArgu::setArgu()
{
	if (argu.at(argu.size() - 1) == ')') {
		argu = argu.substr(0, argu.size() - 1);
	}
}
