#include "rshellbase.hpp"
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>

using namespace std;

bool ExeArgu::Operate()
{ 
	if(this->exe == "["){
		this->exe = "test";
		if(this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) == ' '){
			this->argu = this->argu.substr(0,this->argu.size() - 2);
		}
		else if( this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) != ' '){
			this->argu = this->argu.substr(0,this->argu.size() - 1);
		}
	}
	else if(this->exe.at(0) == '['){
		this->argu.insert(0," ");
		this->argu.insert(0,this->exe.substr(1,this->exe.size()-1));
		this->exe = "test";
		if(this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) == ' '){
			this->argu = this->argu.substr(0,this->argu.size() - 2);
		}
		else if( this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) != ' '){
			this->argu = this->argu.substr(0,this->argu.size() - 1);
		}
	}
	if(this->exe == "test"){
		string flag;
		if(this->argu.at(0)!='-'){
			flag = "-e";
		}
		else{
			flag = this->argu.substr(0,2);
			this->argu = this->argu.substr(3,this->argu.size()-3);
		}
		

		struct stat buf;
		if(flag=="-e")
		{
			int status = stat(const_cast<char*>(this->argu.c_str()),&buf);
			if(status==0)
			{
				cout<<"(True)"<<endl;
				return true;
			}
			else
			{
				cout<<"(False)"<<endl;
				return false;
			}  
		}
		else if(flag=="-f"){
			int status = stat(const_cast<char*>(this->argu.c_str()),&buf);
			if(status!=0) {
				cout<<"(False)"<<endl; 
				return false;
			}
			if(S_ISREG(buf.st_mode)) {
				cout<<"(True)"<<endl; 
				return true;
			}
			else {
				cout<<"(False)"<<endl; 
				return false;
			}	
		}
		else if(flag=="-d"){
			int status = stat(const_cast<char*>(this->argu.c_str()),&buf);
			if(status!=0) {
				cout<<"(False)"<<endl; 
				return false;
			}
			if(S_ISDIR(buf.st_mode)) {
				cout<<"(True)"<<endl;
				return true;
			}
			else {
				cout<<"(False)"<<endl; 
				return false;
			}
		}
		else {
			cout << "flag doesn't exist, please try again(-e, -f or -d)" << endl;
			return false;
		}
     	}
	else{
		pid_t pid,pr;
		pid = fork();

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
					exit(0);
				}
			}
		}
		else {
			int status;
			pr = waitpid(pid, &status, 0);
			if(pr == pid){
				status = WEXITSTATUS(status);
				if(status == 1){
					return false;
				}
				else if(status == 0) {
					return true;
				}
			}
			else{
				cout << "someerror occured" << endl;
				return false;
			}
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

vector<int> ExeArgu::getLeftP()
{
	return this->leftP;
}

vector<int> ExeArgu::getRightP()
{
	return this->rightP;
}

void ExeArgu::setLeftP(int i)
{
	leftP.push_back(i);
}

void ExeArgu::setRightP(int i)
{
	rightP.push_back(i);
}

void ExeArgu::setExeL()
{
	if(exe.at(0) == '('){
		exe = exe.substr(1 , exe.size()-1);
	}
}

void ExeArgu::setExeR()
{
	if (exe.at(exe.size() - 1) == ')') {
		exe = exe.substr(0, exe.size() - 1);
	}
}

void ExeArgu::setArgu()
{
	if (argu.at(argu.size() - 1) == ')') {
		argu = argu.substr(0, argu.size() - 1);
	}
}
